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
 * @file    app/main.c
 * @brief   Main file for deadbadger picoballoon
 *
 * @addtogroup utils
 * @{
 */
#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/i2c.h>
#include <libopencm3/stm32/spi.h>

#include <hal/io.h>
#include <hal/i2c.h>
#include <hal/spi.h>
#include <hal/uart.h>

#include <modules/log.h>
#include <drivers/gps.h>
#include <utils/time.h>
#include "utils/assert.h"

/**
 * Configure system clock
 */
static void setClock(void)
{
#if 0
    /* Enable crystal oscillator and use it as a system clock */
    rcc_osc_on(RCC_HSE);
    rcc_wait_for_osc_ready(RCC_HSE);
    rcc_set_sysclk_source(RCC_HSE);

    rcc_apb1_frequency = 16000000;
    rcc_ahb_frequency = 16000000;

    /* No prescalers for system clock and peripherals */
    rcc_set_hpre(RCC_CFGR_HPRE_NODIV);
    rcc_set_ppre(RCC_CFGR_PPRE_NODIV);

    /* Setup PLL to generate 48 MHz for usb */
    rcc_set_pll_multiplication_factor(RCC_CFGR_PLLMUL_MUL6);
    rcc_set_pll_source(RCC_CFGR_PLLSRC_HSE_CLK);
    rcc_set_prediv(RCC_CFGR2_PREDIV_DIV2);
    rcc_osc_on(RCC_PLL);
    rcc_wait_for_osc_ready(RCC_PLL);
    rcc_set_usbclk_source(RCC_PLL);
#endif
}

int main(void)
{
    /* Initialize clock system, IO pins and systick */
    setClock();
    IOd_Init();
    Time_Init();

    /* early init - debug output */
    UARTd_Init(USART_DEBUG_TX, 115200);
    Log_SetLevel(LOG_DEBUG);
    Log_Info(NULL, "PicoBalloon Challenge 2020");
    Log_Info(NULL, "Deadbadger.cz");

    I2Cd_Init(1, true);
    SPId_Init(1, SPID_PRESC_2, SPI_MODE_0);
    UARTd_Init(USART_GPS_TX, 9600);
//    RTCd_Init();

    Log_Info(NULL, "System initialized, running main loop");
    while (1) {
    }
}

/** @} */
