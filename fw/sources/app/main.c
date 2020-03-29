/*
 * Copyright (C) 2020 Jakub Kaderka
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

/**
 * @file    app/main.c
 * @brief   Main file for deadbadger.cz picoballoon
 *
 * @addtogroup app
 *
 * @{
 */

#include <types.h>

#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/i2c.h>
#include <libopencm3/stm32/spi.h>

#include <hal/io.h>
#include <hal/adc.h>
#include <hal/i2c.h>
#include <hal/spi.h>
#include <hal/uart.h>
#include <hal/rtc.h>
#include <hal/power.h>
#include <hal/flash.h>
#include <utils/time.h>

#include <modules/log.h>
#include <modules/lora.h>
#include <drivers/gps.h>
#include <drivers/ms5607.h>
#include <drivers/si7020.h>
#include <drivers/rfm.h>

#include "config.h"

typedef struct {
    uint8_t gps_power: 1;       /**< GPS power was active during the period */
    uint8_t power_latch: 1;     /**< Power latch is turned off (solar only power */
    uint8_t gps_fix: 1;         /**< Have recent GPS fix */
    uint8_t ms5607_ok: 1;       /**< MS5607 sensor is ok */
    uint8_t si7020_ok: 1;       /**< MS5607 sensor is ok */
} telemetry_bf_t;

typedef struct {
    telemetry_bf_t state;   /** State of the probe outputs,... */
    uint16_t press_daPa;    /** Air pressure in deca Pascals (*10) */
    int16_t temp_dc;        /** Temperature in deci Celsius (/10) */
    int8_t core_temp_c;     /** MCU core temperature in degrees Celsius */
    uint8_t RH;             /** Relative humidity in pct */
    uint16_t alt_m;         /** Altitude in meters */
    float lat;              /** Latitude in decimal degrees */
    float lon;              /** Longitude in decimal degrees */
    uint16_t bat_mv;        /**< Voltage of the battery/supercap */
    uint16_t solar_mv;      /**< Voltage of the solar cell */
    uint8_t loop_time_s;    /**< Time since wake up until packet creation */
} __attribute__((packed)) telemetry_packet_t;

/** The Thing Network auth data */
static const uint8_t ttn_DevAddr[16] = TTN_DEV_ADDR;
static const uint8_t ttn_NwkSkey[16] = TTN_NWKSKEY;
static const uint8_t ttn_AppSkey[16] = TTN_APPSKEY;

/** Address to store Lora counter value, first address, align to page boundary */
#define LORA_TX_COUNTER_ADDR0 0xF000

/**
 * Address to store Lora counter value, second address (offseted by smallest
 * erasable area from previous one
 */
#define LORA_TX_COUNTER_ADDR1 (LORA_TX_COUNTER_ADDR0 + FLASHD_PAGE_SIZE)

/**
 * Control GPS power switch
 *
 * @param on    True to power on, false to power off
 */
static void App_GpsPower(bool on)
{
    IOd_SetLine(LINE_GPS_POWER_N, !on);
}

/**
 * Disable latch on power supply (if supercap voltage is low, power off)
 *
 * @param disable   True to disable
 */
static void App_LatchDisable(bool disable)
{
    IOd_SetLine(LINE_POWER_OFF_N, !disable);
}

/**
 * Set LoRa region based on recent known location
 *
 * @param gps_lat   Latitude
 * @param gps_lon   Longitude
 */
static void App_SetRegion(nmea_float_t gps_lat,
        nmea_float_t gps_lon)
{
    rfm_lora_region_t region = RFM_REGION_EU863;
    int16_t lat = gps_lat.num / gps_lat.scale;
    int16_t lon = gps_lon.num / gps_lon.scale;

    /* America */
    if (lon > -170 && lon < 50) {
        region = RFM_REGION_US902;
    /* Australia, New Zealand */
    } else if  (lat > -50 && lat < -7 && lon > 100 && lon < 170) {
        region = RFM_REGION_AU915;
    /* Japan, Malaysia, etc. */
    } else if (lon > 78 && lon < 160) {
        region = RFM_REGION_AS920;
    }

    RFM_SetLoraRegion(region);
}

/**
 * Save value of the LoRaWan tx counter to internal flash memory
 *
 * @param counter   Counter value
 */
static void App_SaveTxCounter(uint32_t counter)
{
    uint32_t cnt1 = *((uint32_t *) LORA_TX_COUNTER_ADDR0);
    uint32_t cnt2 = *((uint32_t *) LORA_TX_COUNTER_ADDR1);
    uint32_t addr;

    if (cnt1 == (uint32_t) -1) {
        addr = LORA_TX_COUNTER_ADDR0;
    } else if (cnt2 == (uint32_t) -1) {
        addr = LORA_TX_COUNTER_ADDR1;
    } else if (cnt1 > cnt2) {
        addr = LORA_TX_COUNTER_ADDR1;
    } else {
        addr = LORA_TX_COUNTER_ADDR0;
    }
    Flashd_WriteEnable();
    Flashd_ErasePage(addr);
    Flashd_Write(addr, (uint8_t *)&counter, sizeof(counter));
    Flashd_WriteDisable();
}

/**
 * Load saved value of the LoRaWan tx counter
 *
 * @return Saved counter value or 0
 */
static uint32_t App_LoadTxCounter(void)
{
    uint32_t cnt1 = *((uint32_t *) LORA_TX_COUNTER_ADDR0);
    uint32_t cnt2 = *((uint32_t *) LORA_TX_COUNTER_ADDR1);

    if (cnt1 == (uint32_t) -1) {
        if (cnt2 == (uint32_t) -1) {
            return 0;
        }
    }

    if (cnt2 == (uint32_t) -1) {
        return cnt1;
    }

    if (cnt1 > cnt2) {
        return cnt1;
    }
    return cnt2;
}

static void App_Loop(void)
{
    static uint8_t gps_skip = 0;
    telemetry_packet_t packet = {0};
    gps_info_t *gps;
    int32_t temp_mdeg = 0;
    uint32_t press_Pa = 0;
    uint32_t start_ts = millis();
    uint32_t tx_counter;

    Log_Info(NULL, "Measuring");

    packet.bat_mv = Adcd_ReadMv(CHN_BAT_VOLT);
    packet.solar_mv = Adcd_ReadMv(CHN_SOLAR_VOLT);
    packet.core_temp_c = Adcd_ReadTempDegC();
    Adcd_Sleep();

    //not fitted this year
    //packet.RH = SI7020_RH();
    //packet.state.si7020_ok = packet.RH != 0;

    packet.state.ms5607_ok = MS5607_Read(MS5607_OSR1024, &press_Pa, &temp_mdeg);
    packet.press_daPa = press_Pa / 10;
    packet.temp_dc = temp_mdeg / 100;
//    packet.state.gps_power = !IOd_GetLine(LINE_GPS_POWER_N);
//    packet.state.power_latch = !IOd_GetLine(LINE_POWER_OFF_N);

    /* wait for fix */
    while (Gps_Loop() == NULL && (millis() - start_ts) < GPS_FIX_TIMEOUT_S*1000) {
        ;
    }
    gps = Gps_Get();
    if (gps != NULL) {
        App_SetRegion(gps->lat, gps->lon);
        packet.alt_m = gps->altitude_dm/10;
        packet.lat = ((float) gps->lat.num) / gps->lat.scale;
        packet.lon = ((float) gps->lon.num) / gps->lon.scale;
        packet.state.gps_fix = true;
    } else {
        /* keep region from previous fix */
        packet.alt_m = 0;
        packet.lat = 0;
        packet.lon = 0;
        packet.state.gps_fix = false;
    }
    packet.loop_time_s = (millis() - start_ts) / 1000;

    Log_Info(NULL, "Sending data");
    /* Save lora tx counter + 1 (in case, power dies before saving */
    tx_counter = App_LoadTxCounter();
    Lora_SetCounters(0, tx_counter);
    App_SaveTxCounter(tx_counter+1);
    if (!Lora_Send((uint8_t *) &packet, sizeof(packet))) {
        Log_Error(NULL, "Failed to send data over LoRaWan!");
    }
    App_LatchDisable(true);
}

int main(void)
{
    struct tm tm;

    /* Initialize clock system, IO pins and systick */
    IOd_Init();
    Time_Init();

    /* Enable GPS now to get fix ASAP, for now, also rfm95 is wired here */
    App_GpsPower(true);

    /* early init - debug output */
    UARTd_Init(USART_DEBUG_TX, 115200);
    Log_Info(NULL, "PicoBalloon Challenge 2020");
    Log_Info(NULL, "Deadbadger.cz");

    I2Cd_Init(1, false);
    SPId_Init(1, SPID_PRESC_2, SPI_MODE_0);
    UARTd_Init(USART_GPS_TX, 9600);
    RTCd_Init(false);
    Adcd_Init();

    Gps_Init();
    if (!MS5607_Init()) {
        Log_Error(NULL, "MS5607 pressure sensor not responding");
    }
    /*
    if (!SI7020_Init()) {
        Log_Error(NULL, "SI7020 humidity sensor not responding");
    }
    */
    if (!RFM_LoraInit()) {
        Log_Error(NULL, "RFM module not responding!");
    }
    Lora_InitAbp(RFM_LoraSend, ttn_DevAddr, ttn_NwkSkey, ttn_AppSkey);
    RFM_SetLoraRegion(RFM_REGION_EU863);
    RFM_SetLoraParams(RFM_BW_125k, RFM_SF_10);
    RFM_SetPowerDBm(17);

    Log_Info(NULL, "System initialized, running main loop");
    Log_SetLevel(LOG_ERROR);

    /* ================ TODO ================ */
    /* debugging purposes only, remove for production */
    Log_SetLevel(LOG_DEBUG);
    /* ================ TODO ================ */
    while (1) {
        App_Loop();
        App_GpsPower(false);
        /* Don't have wakeup timer, use alarm, only hour, min, sec used */
        RTCd_GetTime(&tm);
        /*
        tm.tm_sec += 10;
        if (tm.tm_sec >= 60) {
            tm.tm_sec %= 60;
            tm.tm_min += 1;
        }
        if (tm.tm_min >= 60) {
            tm.tm_min = 0;
            tm.tm_hour += 1;
            tm.tm_hour %= 24;
        }
        */
        Log_Info(NULL, "Start at %d %d", tm.tm_hour, tm.tm_min);
        if (tm.tm_min + (TELEMETRY_PERIOD_MIN % 60) >= 60) {
            tm.tm_hour += 1;
        }
        tm.tm_hour = (tm.tm_hour + TELEMETRY_PERIOD_MIN / 60) % 24;
        tm.tm_min = (tm.tm_min + TELEMETRY_PERIOD_MIN) % 60;
        Log_Info(NULL, "Start at %d %d", tm.tm_hour, tm.tm_min);

        Log_Info(NULL, "Sleeping for %d minutes", TELEMETRY_PERIOD_MIN);
        RTCd_SetAlarm(&tm, NULL);
        Powerd_Off();
        Log_Error(NULL, "Failed to sleep");
        Powerd_Reboot();
    }
}

/** @} */
