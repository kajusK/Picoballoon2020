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
 * @file    app/config.h
 * @brief   System configuration
 *
 * @addtogroup app
 * @{
 */

#ifndef __CONFIG_H
#define __CONFIG_H

/* The Things Network connection parameters */
#define TTN_DEV_ADDR {0x26, 0x01, 0x1E, 0x7e}
#define TTN_NWKSKEY {0x91, 0x76, 0x0f, 0x5c, 0xee, 0x2b, 0xf2, 0xcc, 0x4f, 0xc8, 0x5c, 0x72, 0xad, 0xe9, 0x16, 0x0b}
#define TTN_APPSKEY {0x91, 0xa2, 0xfe, 0xd7, 0xd7, 0x8a, 0xc4, 0xa8, 0xc7, 0xb1, 0xdc, 0x44, 0x30, 0x51, 0xf4, 0x96}

/** Send telemetry every n minutes */
#define TELEMETRY_PERIOD_MIN 30U
/** Measure GPS position every nth telemetry window (1-255) */
#define TELEMETRY_GPS_SKIP 4U
/** Power off gps if fix not obtained withing the given time frame */
#define GPS_FIX_TIMEOUT_S 30U

#endif

/** @} */
