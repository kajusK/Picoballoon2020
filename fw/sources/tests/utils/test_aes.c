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
 * @file    utils/test_aes.c
 * @brief   Unit tests for aes.c
 *
 * @addtogroup tests
 * @{
 */

#include <string.h>

#include <main.h>
#include "utils/aes.c"

/* *****************************************************************************
 * Tests
***************************************************************************** */
TEST_GROUP(AES);

TEST_SETUP(AES)
{
}

TEST_TEAR_DOWN(AES)
{

}

TEST(AES, AddRoundKey)
{
    uint8_t state[] = {
            0x11, 0x23, 0x45, 0x67,
            0x5c, 0x68, 0x7f, 0xf8,
            0xaa, 0xa1, 0xb0, 0x0c,
            0x9c, 0x36, 0xff, 0x7f,
    };
    uint8_t key[] = {
            0x82, 0x26, 0x6e, 0x85,
            0x4a, 0x45, 0xd2, 0x41,
            0xac, 0x32, 0xe7, 0xfe,
            0xde, 0x05, 0x16, 0xd2,
    };
    uint8_t state_exp[] = {
            0x93, 0x05, 0x2b, 0xe2,
            0x16, 0x2d, 0xad, 0xb9,
            0x06, 0x93, 0x57, 0xf2,
            0x42, 0x33, 0xe9, 0xad,
    };

    AESi_AddRoundKey(state, key);
    TEST_ASSERT_EQUAL_HEX8_ARRAY(state_exp, state, 16);
}

TEST(AES, SubBytes)
{
    uint8_t state[] = {
            0x11, 0x23, 0x45, 0x67,
            0x5c, 0x68, 0x7f, 0xf8,
            0xaa, 0xa1, 0xb0, 0x0c,
            0x9c, 0x36, 0xff, 0x7f,
    };
    uint8_t state_exp[] = {
            0x82, 0x26, 0x6e, 0x85,
            0x4a, 0x45, 0xd2, 0x41,
            0xac, 0x32, 0xe7, 0xfe,
            0xde, 0x05, 0x16, 0xd2,
    };

    AESi_SubBytes(state);
    TEST_ASSERT_EQUAL_HEX8_ARRAY(state_exp, state, 16);
}

TEST(AES, SubBytesInv)
{
    uint8_t state[] = {
            0x82, 0x26, 0x6e, 0x85,
            0x4a, 0x45, 0xd2, 0x41,
            0xac, 0x32, 0xe7, 0xfe,
            0xde, 0x05, 0x16, 0xd2,
    };

    uint8_t state_exp[] = {
            0x11, 0x23, 0x45, 0x67,
            0x5c, 0x68, 0x7f, 0xf8,
            0xaa, 0xa1, 0xb0, 0x0c,
            0x9c, 0x36, 0xff, 0x7f,
    };

    AESi_SubBytesInv(state);
    TEST_ASSERT_EQUAL_HEX8_ARRAY(state_exp, state, 16);
}

TEST(AES, ShiftRows)
{
    /* columns are shown as rows here, using 2d arrayfor addressing */
    uint8_t state[] = {
            0x11, 0x22, 0x33, 0x44,
            0x55, 0x66, 0x77, 0x88,
            0x99, 0xaa, 0xbb, 0xcc,
            0xdd, 0xee, 0xff, 0x00,
    };
    uint8_t state_exp[] = {
            0x11, 0x66, 0xbb, 0x00,
            0x55, 0xaa, 0xff, 0x44,
            0x99, 0xee, 0x33, 0x88,
            0xdd, 0x22, 0x77, 0xcc,
    };

    AESi_ShiftRows(state);
    TEST_ASSERT_EQUAL_HEX8_ARRAY(state_exp, state, 16);
}

TEST(AES, ShiftRowsInv)
{
    uint8_t state[] = {
            0x11, 0x66, 0xbb, 0x00,
            0x55, 0xaa, 0xff, 0x44,
            0x99, 0xee, 0x33, 0x88,
            0xdd, 0x22, 0x77, 0xcc,
    };
    uint8_t state_exp[] = {
            0x11, 0x22, 0x33, 0x44,
            0x55, 0x66, 0x77, 0x88,
            0x99, 0xaa, 0xbb, 0xcc,
            0xdd, 0xee, 0xff, 0x00,
    };

    AESi_ShiftRowsInv(state);
    TEST_ASSERT_EQUAL_HEX8_ARRAY(state_exp, state, 16);
}

TEST(AES, MixColumns)
{
    /* Test vectors from https://en.wikipedia.org/wiki/Rijndael_MixColumns */
    uint8_t state[] = {
            0xdb, 0x13, 0x53, 0x45,
            0xf2, 0x0a, 0x22, 0x5c,
            0x01, 0x01, 0x01, 0x01,
            0xd4, 0xd4, 0xd4, 0xd5,
    };

    uint8_t state_exp[] = {
            0x8e, 0x4d, 0xa1, 0xbc,
            0x9f, 0xdc, 0x58, 0x9d,
            0x01, 0x01, 0x01, 0x01,
            0xd5, 0xd5, 0xd7, 0xd6,
    };

    AESi_MixColumns(state);
    TEST_ASSERT_EQUAL_HEX8_ARRAY(state_exp, state, 16);
}

TEST(AES, MixColumnsInv)
{
    uint8_t state[] = {
            0x8e, 0x4d, 0xa1, 0xbc,
            0x9f, 0xdc, 0x58, 0x9d,
            0x01, 0x01, 0x01, 0x01,
            0xd5, 0xd5, 0xd7, 0xd6,
    };
    uint8_t state_exp[] = {
            0xdb, 0x13, 0x53, 0x45,
            0xf2, 0x0a, 0x22, 0x5c,
            0x01, 0x01, 0x01, 0x01,
            0xd4, 0xd4, 0xd4, 0xd5,
    };

    AESi_MixColumnsInv(state);
    TEST_ASSERT_EQUAL_HEX8_ARRAY(state_exp, state, 16);
}

TEST(AES, GenRoundKey)
{
    uint8_t round_key[16];
    uint8_t rcon = 1;
    uint8_t vector[][16] = {
        { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
        { 0x62, 0x63, 0x63, 0x63, 0x62, 0x63, 0x63, 0x63, 0x62, 0x63, 0x63, 0x63, 0x62, 0x63, 0x63, 0x63 },
        { 0x9b, 0x98, 0x98, 0xc9, 0xf9, 0xfb, 0xfb, 0xaa, 0x9b, 0x98, 0x98, 0xc9, 0xf9, 0xfb, 0xfb, 0xaa },
        { 0x90, 0x97, 0x34, 0x50, 0x69, 0x6c, 0xcf, 0xfa, 0xf2, 0xf4, 0x57, 0x33, 0x0b, 0x0f, 0xac, 0x99 },
        { 0xee, 0x06, 0xda, 0x7b, 0x87, 0x6a, 0x15, 0x81, 0x75, 0x9e, 0x42, 0xb2, 0x7e, 0x91, 0xee, 0x2b },
        { 0x7f, 0x2e, 0x2b, 0x88, 0xf8, 0x44, 0x3e, 0x09, 0x8d, 0xda, 0x7c, 0xbb, 0xf3, 0x4b, 0x92, 0x90 },
        { 0xec, 0x61, 0x4b, 0x85, 0x14, 0x25, 0x75, 0x8c, 0x99, 0xff, 0x09, 0x37, 0x6a, 0xb4, 0x9b, 0xa7 },
        { 0x21, 0x75, 0x17, 0x87, 0x35, 0x50, 0x62, 0x0b, 0xac, 0xaf, 0x6b, 0x3c, 0xc6, 0x1b, 0xf0, 0x9b },
        { 0x0e, 0xf9, 0x03, 0x33, 0x3b, 0xa9, 0x61, 0x38, 0x97, 0x06, 0x0a, 0x04, 0x51, 0x1d, 0xfa, 0x9f },
        { 0xb1, 0xd4, 0xd8, 0xe2, 0x8a, 0x7d, 0xb9, 0xda, 0x1d, 0x7b, 0xb3, 0xde, 0x4c, 0x66, 0x49, 0x41 },
        { 0xb4, 0xef, 0x5b, 0xcb, 0x3e, 0x92, 0xe2, 0x11, 0x23, 0xe9, 0x51, 0xcf, 0x6f, 0x8f, 0x18, 0x8e }
    };

    memcpy(round_key, vector[0], 16);
    for (uint8_t i = 1; i <= 10; i++) {
        AESi_GenRoundKey(round_key, rcon);
        TEST_ASSERT_EQUAL_HEX8_ARRAY(vector[i], round_key, 16);

        rcon = AESi_Mul2(rcon);
    }
}

TEST(AES, GenRoundKeyLast)
{
    uint8_t key[] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
    uint8_t exp[]  = { 0xb4, 0xef, 0x5b, 0xcb, 0x3e, 0x92, 0xe2, 0x11, 0x23, 0xe9, 0x51, 0xcf, 0x6f, 0x8f, 0x18, 0x8e };
    AESi_GenRoundKeyLast(key);
    TEST_ASSERT_EQUAL_HEX8_ARRAY(exp, key, 16);
}

TEST(AES, GenRoundKeyInv)
{
    uint8_t round_key[16];
    uint8_t rcon = 0x36;
    uint8_t vector[][16] = {
        { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
        { 0x62, 0x63, 0x63, 0x63, 0x62, 0x63, 0x63, 0x63, 0x62, 0x63, 0x63, 0x63, 0x62, 0x63, 0x63, 0x63 },
        { 0x9b, 0x98, 0x98, 0xc9, 0xf9, 0xfb, 0xfb, 0xaa, 0x9b, 0x98, 0x98, 0xc9, 0xf9, 0xfb, 0xfb, 0xaa },
        { 0x90, 0x97, 0x34, 0x50, 0x69, 0x6c, 0xcf, 0xfa, 0xf2, 0xf4, 0x57, 0x33, 0x0b, 0x0f, 0xac, 0x99 },
        { 0xee, 0x06, 0xda, 0x7b, 0x87, 0x6a, 0x15, 0x81, 0x75, 0x9e, 0x42, 0xb2, 0x7e, 0x91, 0xee, 0x2b },
        { 0x7f, 0x2e, 0x2b, 0x88, 0xf8, 0x44, 0x3e, 0x09, 0x8d, 0xda, 0x7c, 0xbb, 0xf3, 0x4b, 0x92, 0x90 },
        { 0xec, 0x61, 0x4b, 0x85, 0x14, 0x25, 0x75, 0x8c, 0x99, 0xff, 0x09, 0x37, 0x6a, 0xb4, 0x9b, 0xa7 },
        { 0x21, 0x75, 0x17, 0x87, 0x35, 0x50, 0x62, 0x0b, 0xac, 0xaf, 0x6b, 0x3c, 0xc6, 0x1b, 0xf0, 0x9b },
        { 0x0e, 0xf9, 0x03, 0x33, 0x3b, 0xa9, 0x61, 0x38, 0x97, 0x06, 0x0a, 0x04, 0x51, 0x1d, 0xfa, 0x9f },
        { 0xb1, 0xd4, 0xd8, 0xe2, 0x8a, 0x7d, 0xb9, 0xda, 0x1d, 0x7b, 0xb3, 0xde, 0x4c, 0x66, 0x49, 0x41 },
        { 0xb4, 0xef, 0x5b, 0xcb, 0x3e, 0x92, 0xe2, 0x11, 0x23, 0xe9, 0x51, 0xcf, 0x6f, 0x8f, 0x18, 0x8e }
    };

    memcpy(round_key, vector[10], 16);
    for (uint8_t i = 9; i > 0; i--) {
        AESi_GenRoundKeyInv(round_key, rcon);
        TEST_ASSERT_EQUAL_HEX8_ARRAY(vector[i], round_key, 16);
        rcon = AESi_Div2(rcon);
    }
}

TEST(AES, AES128_Encrypt)
{
    uint8_t key[] = {0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6, 0xab, 0xf7, 0x15, 0x88, 0x09, 0xcf, 0x4f, 0x3c};
    /* input followed by expected output, from https://nvlpubs.nist.gov/nistpubs/Legacy/SP/nistspecialpublication800-38a.pdf */
    uint8_t vector[][16] = {
            {0x6b, 0xc1, 0xbe, 0xe2, 0x2e, 0x40, 0x9f, 0x96, 0xe9, 0x3d, 0x7e, 0x11, 0x73, 0x93, 0x17, 0x2a},
            {0x3a, 0xd7, 0x7b, 0xb4, 0x0d, 0x7a, 0x36, 0x60, 0xa8, 0x9e, 0xca, 0xf3, 0x24, 0x66, 0xef, 0x97},
            {0xae, 0x2d, 0x8a, 0x57, 0x1e, 0x03, 0xac, 0x9c, 0x9e, 0xb7, 0x6f, 0xac, 0x45, 0xaf, 0x8e, 0x51},
            {0xf5, 0xd3, 0xd5, 0x85, 0x03, 0xb9, 0x69, 0x9d, 0xe7, 0x85, 0x89, 0x5a, 0x96, 0xfd, 0xba, 0xaf},
            {0x30, 0xc8, 0x1c, 0x46, 0xa3, 0x5c, 0xe4, 0x11, 0xe5, 0xfb, 0xc1, 0x19, 0x1a, 0x0a, 0x52, 0xef},
            {0x43, 0xb1, 0xcd, 0x7f, 0x59, 0x8e, 0xce, 0x23, 0x88, 0x1b, 0x00, 0xe3, 0xed, 0x03, 0x06, 0x88},
            {0xf6, 0x9f, 0x24, 0x45, 0xdf, 0x4f, 0x9b, 0x17, 0xad, 0x2b, 0x41, 0x7b, 0xe6, 0x6c, 0x37, 0x10},
            {0x7b, 0x0c, 0x78, 0x5e, 0x27, 0xe8, 0xad, 0x3f, 0x82, 0x23, 0x20, 0x71, 0x04, 0x72, 0x5d, 0xd4},
    };

    for (uint8_t i = 0; i < sizeof(vector)/sizeof(vector[0]); i += 2) {
        AES128_Encrypt(vector[i], key);
        TEST_ASSERT_EQUAL_HEX8_ARRAY(vector[i+1], vector[i], 16);
    }
}

TEST(AES, AES128_Decrypt)
{
    uint8_t key[] = {0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6, 0xab, 0xf7, 0x15, 0x88, 0x09, 0xcf, 0x4f, 0x3c};
    /* input followed by expected output, from https://nvlpubs.nist.gov/nistpubs/Legacy/SP/nistspecialpublication800-38a.pdf */
    uint8_t vector[][16] = {
            {0x6b, 0xc1, 0xbe, 0xe2, 0x2e, 0x40, 0x9f, 0x96, 0xe9, 0x3d, 0x7e, 0x11, 0x73, 0x93, 0x17, 0x2a},
            {0x3a, 0xd7, 0x7b, 0xb4, 0x0d, 0x7a, 0x36, 0x60, 0xa8, 0x9e, 0xca, 0xf3, 0x24, 0x66, 0xef, 0x97},
            {0xae, 0x2d, 0x8a, 0x57, 0x1e, 0x03, 0xac, 0x9c, 0x9e, 0xb7, 0x6f, 0xac, 0x45, 0xaf, 0x8e, 0x51},
            {0xf5, 0xd3, 0xd5, 0x85, 0x03, 0xb9, 0x69, 0x9d, 0xe7, 0x85, 0x89, 0x5a, 0x96, 0xfd, 0xba, 0xaf},
            {0x30, 0xc8, 0x1c, 0x46, 0xa3, 0x5c, 0xe4, 0x11, 0xe5, 0xfb, 0xc1, 0x19, 0x1a, 0x0a, 0x52, 0xef},
            {0x43, 0xb1, 0xcd, 0x7f, 0x59, 0x8e, 0xce, 0x23, 0x88, 0x1b, 0x00, 0xe3, 0xed, 0x03, 0x06, 0x88},
            {0xf6, 0x9f, 0x24, 0x45, 0xdf, 0x4f, 0x9b, 0x17, 0xad, 0x2b, 0x41, 0x7b, 0xe6, 0x6c, 0x37, 0x10},
            {0x7b, 0x0c, 0x78, 0x5e, 0x27, 0xe8, 0xad, 0x3f, 0x82, 0x23, 0x20, 0x71, 0x04, 0x72, 0x5d, 0xd4},
    };

    for (uint8_t i = 0; i < sizeof(vector)/sizeof(vector[0]); i += 2) {
        AES128_Decrypt(vector[i+1], key);
        TEST_ASSERT_EQUAL_HEX8_ARRAY(vector[i], vector[i+1], 16);
    }
}

TEST(AES, AES128_CMACGetKeys)
{
    uint8_t key[] = {0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6, 0xab, 0xf7, 0x15, 0x88, 0x09, 0xcf, 0x4f, 0x3c};
    uint8_t exp1[] = {0xfb, 0xee, 0xd6, 0x18, 0x35, 0x71, 0x33, 0x66, 0x7c, 0x85, 0xe0, 0x8f, 0x72, 0x36, 0xa8, 0xde};
    uint8_t exp2[] = {0xf7, 0xdd, 0xac, 0x30, 0x6a, 0xe2, 0x66, 0xcc, 0xf9, 0x0b, 0xc1, 0x1e, 0xe4, 0x6d, 0x51, 0x3b};
    uint8_t k1[16], k2[16];

    AES128_CMACGetKeys(k1, k2, key);
    TEST_ASSERT_EQUAL_HEX8_ARRAY(exp1, k1, 16);
    TEST_ASSERT_EQUAL_HEX8_ARRAY(exp2, k2, 16);
}

TEST(AES, AES128_CMAC)
{
    uint8_t key[] = {0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6, 0xab, 0xf7, 0x15, 0x88, 0x09, 0xcf, 0x4f, 0x3c};
    uint8_t expected[][16] = {
            { 0xbb, 0x1d, 0x69, 0x29, 0xe9, 0x59, 0x37, 0x28, 0x7f, 0xa3, 0x7d, 0x12, 0x9b, 0x75, 0x67, 0x46 },
            { 0x07, 0x0a, 0x16, 0xb4, 0x6b, 0x4d, 0x41, 0x44, 0xf7, 0x9b, 0xdd, 0x9d, 0xd0, 0x4a, 0x28, 0x7c },
            { 0xdf, 0xa6, 0x67, 0x47, 0xde, 0x9a, 0xe6, 0x30, 0x30, 0xca, 0x32, 0x61, 0x14, 0x97, 0xc8, 0x27 },
    };
    uint8_t data0[] = "";
    uint8_t data1[] = { 0x6b, 0xc1, 0xbe, 0xe2, 0x2e, 0x40, 0x9f, 0x96, 0xe9, 0x3d, 0x7e, 0x11, 0x73, 0x93, 0x17, 0x2a };
    uint8_t data2[] = { 0x6b, 0xc1, 0xbe, 0xe2, 0x2e, 0x40, 0x9f, 0x96, 0xe9, 0x3d, 0x7e, 0x11, 0x73, 0x93,
                        0x17, 0x2a, 0xae, 0x2d, 0x8a, 0x57, 0x1e, 0x03, 0xac, 0x9c, 0x9e, 0xb7, 0x6f, 0xac,
                        0x45, 0xaf, 0x8e, 0x51, 0x30, 0xc8, 0x1c, 0x46, 0xa3, 0x5c, 0xe4, 0x11 };
    uint8_t tag[16];

    AES128_CMAC(data0, 0, key, tag);
    TEST_ASSERT_EQUAL_HEX8_ARRAY(expected[0], tag, 16);
    AES128_CMAC(data1, sizeof(data1), key, tag);
    TEST_ASSERT_EQUAL_HEX8_ARRAY(expected[1], tag, 16);
    AES128_CMAC(data2, sizeof(data2), key, tag);
    TEST_ASSERT_EQUAL_HEX8_ARRAY(expected[2], tag, 16);
}

TEST_GROUP_RUNNER(AES)
{
    RUN_TEST_CASE(AES, AddRoundKey);
    RUN_TEST_CASE(AES, SubBytes);
    RUN_TEST_CASE(AES, SubBytesInv);
    RUN_TEST_CASE(AES, ShiftRows);
    RUN_TEST_CASE(AES, ShiftRowsInv);
    RUN_TEST_CASE(AES, MixColumns);
    RUN_TEST_CASE(AES, MixColumnsInv);
    RUN_TEST_CASE(AES, GenRoundKey);
    RUN_TEST_CASE(AES, GenRoundKeyLast);
    RUN_TEST_CASE(AES, GenRoundKeyInv);
    RUN_TEST_CASE(AES, AES128_Encrypt);
    RUN_TEST_CASE(AES, AES128_Decrypt);
    RUN_TEST_CASE(AES, AES128_CMACGetKeys);
    RUN_TEST_CASE(AES, AES128_CMAC);
}

void AES_RunTests(void)
{
    RUN_TEST_GROUP(AES);
}

/** @} */

