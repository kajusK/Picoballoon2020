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
 * Convert 4 bytes array into float number
 * @param bytes     Array of 4 bytes
 * @return Decoded number into float
 */
function toFloat(bytes) {
  var bits = (bytes[3] << 24) | (bytes[2] << 16) | (bytes[1] << 8) | (bytes[0]);
  var sign = ((bits >>> 31) == 0) ? 1.0 : -1.0;
  var e = ((bits >>> 23) & 0xff);
  var m = (e == 0) ? (bits & 0x7fffff) << 1 : (bits & 0x7fffff) | 0x800000;
  return sign * m * Math.pow(2, e - 150);
}

function toUint16(bytes)
{
  return bytes[1] << 8 | bytes[0];
}

function toInt16(bytes)
{
  var num = toUint16(bytes);
  if (bytes[1] & 0x80) {
      // negative number
      num = num | 0xffff0000;
  }
  return num;
}

function toInt8(data)
{
  var num = data;
  if (data & 0x80) {
      // negative number
      num = num | 0xffffff00;
  }
  return data;
}


/**
 * Main TTN decoder function
 *
 * @param bytes     Bytes to be decoded
 *
 * @return Dictionary with decoded payload
 */
function Decoder(bytes, port) {
  var decoded = {};
  var state = bytes[0];

  decoded['pressure_pa'] = toUint16([bytes[1], bytes[2]])*10;
  decoded['temp_c'] = toInt16([bytes[3], bytes[4]])/10;
  decoded['core_temp_c'] = toInt8(bytes[5]);
  decoded['RH'] = bytes[6];
  decoded['alt_m'] = toUint16([bytes[7], bytes[8]]);
  decoded['lat'] = toFloat(bytes.slice(9, 13));
  decoded['lon'] = toFloat(bytes.slice(13, 17));
  decoded['bat_mv'] = toUint16([bytes[17], bytes[18]]);
  decoded['solar_mv'] = toUint16([bytes[19], bytes[20]]);
  decoded['loop_time_s'] = bytes[21];

  decoded['gps_power'] = state & 0x01 != 0;
  decoded['power_latch'] = state & 0x02 != 0;
  decoded['gps_fix'] = state & 0x04 != 0;
  decoded['ms5607_ok'] = state & 0x08 != 0;
  decoded['si7020_ok'] = state & 0x10 != 0;

  return decoded;
}
