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
 * @file    utils/aes.h
 * @brief   AES encryption
 *
 * WARNING - this library was written without side channels attacks in mind,
 * it can be attacked easily by timing attacks, etc.
 *
 * @addtogroup utils
 * @{
 */

#ifndef __UTILS_AES_H
#define __UTILS_AES_H

#include <types.h>

/**
 * Encrypt 16 bytes of data by AES128
 *
 * @param data  16 bytes to encrypt, result is stored here
 * @param key   128bit encryption key
 */
extern void AES128_Encrypt(uint8_t *data, const uint8_t *key);

/**
 * Encrypt 16 bytes of data by AES128
 *
 * @param data  16 bytes to decrypt, result is stored here
 * @param key   128bit encryption key
 */
extern void AES128_Decrypt(uint8_t *data, const uint8_t *key);

#endif

/** @} */
