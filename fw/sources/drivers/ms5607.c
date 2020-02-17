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
 * @file    drivers/ms5607.h
 * @brief   Driver for MS5607 barometric pressure sensor
 *
 * https://www.parallax.com/sites/default/files/downloads/29124-MS5607-02BA03-Datasheet.pdf
 *
 * @addtogroup drivers
 * @{
 */

#include <hal/i2c.h>
#include <utils/time.h>

#include "drivers/ms5607.h"

#define CMD_RESET 0x1e
#define CMD_CONVERT_D1 0x40
#define CMD_CONVERT_D2 0x50
#define CMD_READ_ADC 0x00
#define CMD_READ_PROM 0xa0

/* Conversion time for osr 256, each step doubles the time */
#define CONVERSION_TIME_MS 1

#define I2C_DEVICE 1

/** Sensor i2c address, last bit is CSB pin */
#define MS5607_ADDR 0x76

/** Sensor calibration data storage */
static uint16_t ms5607i_calib[6];

/**
 * Send command to MS5607
 *
 * @param cmd   Command to be sent
 * @return True if sensor acked the command
 */
static bool MS5607i_Cmd(uint8_t cmd)
{
    return I2Cd_Transceive(I2C_DEVICE, MS5607_ADDR, &cmd, 1, NULL, 0);
}

bool MS5607_Read(ms5607_osr_t osr, uint32_t *pressure_Pa, int32_t *temp_mdeg)
{
    bool ret;
    uint32_t d1, d2;
    int32_t dt, temp, p, t2;
    int64_t off, sens, off2, sens2;
    int64_t tmp;

    MS5607i_Cmd(CMD_CONVERT_D1 | osr);
    delay_ms(CONVERSION_TIME_MS << osr);
    MS5607i_Cmd(CMD_READ_ADC);
    ret = I2Cd_Transceive(I2C_DEVICE, MS5607_ADDR, NULL, 0, (uint8_t *) &d1, 2);
    if (!ret) {
        return false;
    }
    MS5607i_Cmd(CMD_CONVERT_D2 | osr);
    delay_ms(CONVERSION_TIME_MS << osr);
    MS5607i_Cmd(CMD_READ_ADC);
    ret = I2Cd_Transceive(I2C_DEVICE, MS5607_ADDR, NULL, 0, (uint8_t *) &d2, 2);
    if (!ret) {
        return false;
    }

    dt = d2 - (((uint32_t) ms5607i_calib[4]) << 8);
    temp = 2000 + (((int64_t) dt*ms5607i_calib[5]) << 23);

    off = ((uint64_t) ms5607i_calib[1] << 17) + (((int64_t)ms5607i_calib[3]*dt) >> 6);
    sens = ((uint64_t) ms5607i_calib[0] << 16) + (((int64_t)ms5607i_calib[2]*dt) >> 7);

    if (temp < 2000) {
        t2 = ((int64_t)dt*dt) >> 31;
        tmp = ((int64_t) temp - 2000)*(temp - 2000);
        off2 = (61*tmp) >> 4;
        sens2 = 2*tmp;
        if (temp < -1500) {
            tmp = ((int64_t) temp + 1500)*(temp + 1500);
            off2 += 15*tmp;
            sens2 += 8*tmp;
        }
    } else {
        t2 = 0;
        off2 = 0;
        sens2 = 0;
    }

    temp = temp - t2;
    off = off - off2;
    sens = sens - sens2;
    p = (((d1*sens) >> 21) - off) >> 15;

    *temp_mdeg = temp / 10;
    *pressure_Pa = p; /* result in mbar * 100, same as Pa */

    return true;
}

bool MS5607_Init(void)
{
    bool ret;
    ret = MS5607i_Cmd(CMD_RESET);
    if (!ret) {
        return false;
    }

    /* Read calibration data, cal data start at offset 2 in prom */
    for (uint8_t i = 1; i < 7; i++) {
        MS5607i_Cmd(CMD_READ_PROM | i);
        ret = I2Cd_Transceive(I2C_DEVICE, MS5607_ADDR, NULL, 0,
                (uint8_t *) &ms5607i_calib[i], 2);
        if (!ret) {
            return false;
        }
    }

    //TODO read crc from PROM and verify the data were readed correctly
    return true;
}

/** @} */
