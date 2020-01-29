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
 * @file    hal/rtc.h
 * @brief   Real Time clock
 *
 * @addtogroup hal
 * @{
 */

#ifndef __HAL_RTC_H
#define __HAL_RTC_H

#include <types.h>
#include <time.h>

/**
 * Get RTC module current time
 *
 * @param tm    Structure to store data to
 */
extern void RTCd_GetTime(struct tm *tm);

/**
 * Set RTC module current time
 *
 * @param tm    Time structure
 */
extern void RTCd_SetTime(const struct tm *tm);

/**
 * Setup RTC wakeup timer to fire in given time
 *
 * @param time_s    Timeout in seconds to set timer to
 */
extern void RTCd_SetWakeup(uint32_t time_s);

/**
 * Initialize RTC peripheral
 */
extern void RTCd_Init(void);

#endif

/** @} */
