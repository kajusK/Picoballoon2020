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
 * @file    hal/power.c
 * @brief   System low power control
 *
 * @addtogroup hal
 * @{
 */

//rtc running from LSI
//EXTI 17 sensitive to rising edge
//rtc should generate rtc alarm
//rtc wakes up only from stop mode! interrupts are there for sleep mode

/**
 * Go to sleep mode
 *
 * Core clock halted, peripherals running, any interrupt processed by nvic
 * will wake the core
 */
void Powerd_Sleep(void)
{
//enter by wfi
}

/**
 * Go to stop mode
 *
 * In stop mode, all peripherals except RTC are down, enabled interrupt on
 * exti line will wake device up
 */
void Powerd_Stop(void)
{
    //Set SLEEPDEEP bit in ARM® Cortex®-M0 System Control register
    //Clear PDDS bit in Power Control register (PWR_CR)
    // Select the voltage regulator mode by configuring LPDS bit in PWR_CR
    /*
     * Note: To enter Stop mode, all EXTI Line pending bits (in Pending register (EXTI_PR)), all peripherals interrupt pending bits and RTC Alarm flag must be reset. Otherwise, the Stop mode entry procedure is ignored and program execution continues. If the application needs to disable the external oscillator (external clock) before entering Stop mode, the system clock source must be first switched to HSI and then clear the HSEON bit.Otherwise, if before entering Stop mode the HSEON bit is kept at 1, the security system (CSS) feature must be enabled to detect any external oscillator (external clock) failure and avoid a malfunction when entering Stop mode.
     */


    //verify adc is enabled, disable until wake up
    // nastaivit RTCEN v RCC_BDCR
    // povolit LSI v RCC_CSR LSION
    // po porbuzení jede z HSI, přehodit zpět na externí

}
