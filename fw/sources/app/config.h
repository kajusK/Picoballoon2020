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
#define TTN_DEV_ADDR {0x00, 0x11, 0x22, 0x33}
#define TTN_NWKSKEY {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}
#define TTN_APPSKEY {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}

/** Send telemetry every n minutes */
#define TELEMETRY_PERIOD_MIN 30U
/** Measure GPS position every nth telemetry window (1-255) */
#define TELEMETRY_GPS_SKIP 4U
/** Power off gps if fix not obtained withing the given time frame */
#define GPS_FIX_TIMEOUT_S 50U

#endif

/** @} */
