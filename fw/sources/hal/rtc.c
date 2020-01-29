/*
 * Copyright (C) 2019 Jakub Kaderka
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
 * @file    hal/rtc.c
 * @brief   Real Time clock
 *
 * @addtogroup hal
 * @{
 */

#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/pwr.h>
#include <libopencm3/stm32/rtc.h>
#include <libopencm3/cm3/nvic.h>

#include "hal/rtc.h"

void rtc_isr(void)
{
    rtc_clear_wakeup_flag();

}

/**
 * Enter config mode of the rtc peripheral
 */
static void RTCdi_EnterConfig(void)
{
    RTC_ISR |= RTC_ISR_INIT;
    while (!(RTC_ISR & RTC_ISR_INITF)) {
        ;
    }
}

/**
 * Leave config mode of the rtc peripheral
 */
static void RTCdi_LeaveConfig(void)
{
    RTC_ISR &= ~(RTC_ISR_INIT);
}

void RTCd_GetTime(struct tm *tm)
{
    uint32_t tr = RTC_TR;
    uint32_t dr = RTC_DR;

    tm->tm_sec = (tr & RTC_TR_ST_MASK) >> RTC_TR_ST_SHIFT;
    tm->tm_sec = tm->tm_sec*10 + ((tr & RTC_TR_SU_MASK) >> RTC_TR_SU_SHIFT);
    tm->tm_min = (tr & RTC_TR_MNT_MASK) >> RTC_TR_MNT_SHIFT;
    tm->tm_min = tm->tm_min*10 + ((tr & RTC_TR_MNU_MASK) >> RTC_TR_MNU_SHIFT);
    tm->tm_hour = (tr & RTC_TR_HT_MASK) >> RTC_TR_HT_SHIFT;
    tm->tm_hour = tm->tm_hour*10 + ((tr & RTC_TR_HU_MASK) >> RTC_TR_HU_SHIFT);
    if (tr & RTC_TR_PM) {
        tm->tm_hour += 12;
    }

    tm->tm_mday = (dr & RTC_DR_DT_MASK) >> RTC_DR_DT_SHIFT;
    tm->tm_mday = tm->tm_mday*10 + ((dr & RTC_DR_DU_MASK) >> RTC_DR_DU_SHIFT);
    tm->tm_mon = (dr & RTC_DR_MT_MASK) >> RTC_DR_MT_SHIFT;
    tm->tm_mon = tm->tm_mday*10 + ((dr & RTC_DR_MU_MASK) >> RTC_DR_MU_SHIFT);
    tm->tm_mon -= 1;
    tm->tm_year = (dr & RTC_DR_YT_MASK) >> RTC_DR_YT_SHIFT;
    tm->tm_year = tm->tm_year*10 + ((dr & RTC_DR_YU_MASK) >> RTC_DR_YU_SHIFT);
    tm->tm_year += 100;
    tm->tm_wday = (dr & RTC_DR_WDU_MASK) >> RTC_DR_WDU_SHIFT;
    tm->tm_wday %= 7;
}

void RTCd_SetTime(const struct tm *tm)
{
    uint32_t dr = 0;
    uint32_t tr = 0;

    tr |= (tm->tm_sec % 10) << RTC_TR_ST_SHIFT;
    tr |= (tm->tm_sec / 10) << RTC_TR_SU_SHIFT;
    tr |= (tm->tm_min % 10) << RTC_TR_MNT_SHIFT;
    tr |= (tm->tm_min / 10) << RTC_TR_MNU_SHIFT;
    tr |= (tm->tm_hour % 10) << RTC_TR_HT_SHIFT;
    tr |= (tm->tm_hour / 10) << RTC_TR_HU_SHIFT;

    dr |= (tm->tm_mday % 10) << RTC_DR_DT_SHIFT;
    dr |= (tm->tm_mday / 10) << RTC_DR_DU_SHIFT;
    dr |= ((tm->tm_mon + 1) % 10) << RTC_DR_MT_SHIFT;
    dr |= ((tm->tm_mon + 1) / 10) << RTC_DR_MU_SHIFT;
    dr |= ((tm->tm_year - 100) % 10) << RTC_DR_YT_SHIFT;
    dr |= ((tm->tm_year - 100) / 10) << RTC_DR_YU_SHIFT;

    if (tm->tm_wday == 0) {
        dr |= 7 << RTC_DR_YU_SHIFT;
    } else {
        dr |= (tm->tm_wday - 1) << RTC_DR_YU_SHIFT;
    }

    rtc_unlock();
    RTCdi_EnterConfig();
    RTC_DR = dr;
    RTC_TR = tr;
    RTCdi_LeaveConfig();
    rtc_lock();
}

void RTCd_SetWakeup(uint32_t time_s)
{
    rtc_unlock();
    rtc_set_wakeup_time(time_s, RTC_CR_WUCLKSEL_SPRE);
    rtc_lock();
}

void RTCd_Init(void)
{
    rcc_periph_clock_enable(RCC_PWR);
    rcc_periph_clock_enable(RCC_RTC);
    pwr_disable_backup_domain_write_protect();

    rcc_osc_on(RCC_LSI);
    rcc_set_rtc_clock_source(RCC_LSI);
    rcc_enable_rtc_clock();

    rtc_unlock();
    RTC_CR = 0; /* 24 hour format */
    RTC_ISR = 0;

    RTCdi_EnterConfig();
    rtc_set_prescaler(255, 127);
    RTCdi_LeaveConfig();
    rtc_lock();

    RCC_BDCR |= RCC_BDCR_RTCEN;
}

/** @} */
