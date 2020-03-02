<?php
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

define("IN_APP", true);
require_once('config.php');
require_once('error.php');

/**
 * Convert pressure in Pa to altitude in m (QNH)
 *
 * based on https://en.wikipedia.org/wiki/Pressure_altitude
 * @param pressure  pressure in Pa
 * @return altitude in m
 */
function Pa2Alt($pressure)
{
    $ft = 145366.45*(1-pow($pressure/101325, 0.190284));
    return round($ft / 3.2808);
}

/**
 * Read all data from database
 *
 * @return Array of dictionaries
 */
function getData()
{
    $config = parse_ini_file("config.ini");
    if (!$config || !isset($config['db_file'])) {
        echo "Invalid config file";
        exit;
    }

    $db = new SQLite3($config['db_file']);
    $result = $db->query("SELECT * from data");
    if (!$result || $result->numColumns() == 0) {
        return [];
    }

    $data = Array();
    $i = 0;

    while ($row = $result->fetchArray()) {
        $data[$i] = $row;
        $data[$i]['qnh_m'] = Pa2Alt($data[$i]['pressure_pa']);
        /* always valid lat, lon, altitude */
        if ($data[$i]['gps_fix']) {
            $data[$i]['a_lat'] = $data[$i]['lat'];
            $data[$i]['a_lon'] = $data[$i]['lon'];
            $data[$i]['a_alt_m'] = $data[$i]['alt_m'];
        } else {
            $data[$i]['a_lat'] = $data[$i]['lora_lat'];
            $data[$i]['a_lon'] = $data[$i]['lora_lon'];
            $data[$i]['a_alt_m'] = $data[$i]['qnh_m'];
        }
        $i++;
    }

    return $data;
}

$data = getData();
extract(['data'=> $data]);
require('page.phtml');
