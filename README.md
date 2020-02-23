Picoballoon Challenge 2020, Deadbadger probe
============================================

This probe was designed [Picoballoon Challenge](https://www.hvezdarna.cz/?p=8167)
organised by Brno Observatory and Planetarium. A goal of this competition
is to make a probe under 20 grams that would be launched on ballon to altitudes
around 5-15 km. Only requirement except weight is sending altitude of the probe.

A detailed description is available at [deadbadger.cz](https://deadbadger.cz/projects/picoballon-2020),
tracking site is at [bal.deadbadger.cz](bal.deadbadger.cz).

The probe contains
  * STM32F030 MCU
  * MS5607 Pressure and temperature sensor
  * Si7020 Relative humidity sensor
  * SIM28ML GPS module
  * RFM95 LoRa Transceiver
  * MCP1640 based solar supercap charger (optinal)
  * 3.3 V boost regulator with 2.7 V startup supervisor

Firmware
--------
As the commonly used [LMIC](https://github.com/matthijskooijman/arduino-lmic/tree/master/src)
library is quite bulky and far from perfect, I wrote my own LoRaWan library
inspired by [TinyLoRa](https://github.com/adafruit/TinyLoRa).

The main loop does about this:
  * Power up, initialize peripherals
  * Power on GPS
  * Measure system voltages, pressure, humidity
  * Wait for GPS data or timeout
  * Power off GPS
  * Send data over LoRa (ABP, unconfirmed uplink)
  * Unlock power latch (keeps probe powered when supercap voltage drops below 2.7 V)
  * Sleep for 30 minutes
  * Repeat (GPS is powered on every 4 cycles)

Hardware
--------
The board was designed for 0.6 mm thick two sided PCB to reduce weight as
much as possible. Using thicker boards (usually 1.6 mm) changes the antenna
trace impedance, but it should not be that significant.

The solar supercap charger can be snapped off if the probe is powered by battery

Frontend
--------
Data received by [TTN](https://www.thethingsnetwork.org/) are sent over
HTTP integration to custom endpoint written in PHP, it verifies the
auth header and stores data in sqlite database.

User frontend is written in PHP, it shows all received packets in table
and generates flight path on a [map](api. mapy.cz).
