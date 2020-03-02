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

/**
 * HTTP endpoint for TTN http integration, stores data to sqlite database
 *
 * Basic HTTP authorization is required (Basic base64(user:pass))
 */

define("IN_APP", true);
require_once('config.php');
require_once('error.php');

/**
 * Average coordinates of the gateways to guess current location
 *
 * @param gateways  Gateways structure from parsed json
 * @return lat lon estimate as 2 member array
 */
function get_position($gateways)
{
    $lat = 0;
    $lon = 0;
    $count = 0;

    foreach ($gateways as $gw) {
        if (!isset($gw['latitude'])) {
            continue;
        }
        $lat += $gw['latitude'];
        $lon += $gw['longitude'];
        $count++;
    }

    if ($count == 0) {
        return [0, 0];
    }
    return [$lat/$count, $lon/$count];
}

/**
 * Store received data to sqlite database (create if not present)
 *
 * @param data      Dictionary with json data from TTN
 */
function storeData($data)
{
    $db = new SQLite3(Config::get('db_file'));
    $db->exec('CREATE TABLE IF NOT EXISTS data (
        time text,
        frequency REAL,
        rssi INTEGER,
        lora_lat REAL,
        lora_lon REAL,
        pressure_pa INTEGER,
        temp_c REAL,
        core_temp_c REAL,
        RH INTEGER,
        alt_m INTEGER,
        lat REAL,
        lon REAL,
        bat_mv INTEGER,
        solar_mv INTEGER,
        loop_time_s INTEGER,
        gps_fix INTEGER,
        raw TEXT,
        UNIQUE(time))');

    $stmt = $db->prepare('INSERT OR IGNORE INTO data VALUES
        (?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?)');

    $meta = $data['metadata'];
    $gateways = $meta['gateways'];
    $fields = $data['payload_fields'];
    $pos = get_position($gateways);

    $stmt->bindValue(1, $meta['time'], SQLITE3_TEXT);
    $stmt->bindValue(2, $meta['frequency'], SQLITE3_FLOAT);
    $stmt->bindValue(3, $gateways[0]['rssi'], SQLITE3_INTEGER);
    $stmt->bindValue(4, $pos[0], SQLITE3_FLOAT);
    $stmt->bindValue(5, $pos[1], SQLITE3_FLOAT);
    $stmt->bindValue(6, $fields['pressure_pa'], SQLITE3_INTEGER);
    $stmt->bindValue(7, $fields['temp_c'], SQLITE3_FLOAT);
    $stmt->bindValue(8, $fields['core_temp_c'], SQLITE3_FLOAT);
    $stmt->bindValue(9, $fields['RH'], SQLITE3_INTEGER);
    $stmt->bindValue(10, $fields['alt_m'], SQLITE3_INTEGER);
    $stmt->bindValue(11, $fields['lat'], SQLITE3_FLOAT);
    $stmt->bindValue(12, $fields['lon'], SQLITE3_FLOAT);
    $stmt->bindValue(13, $fields['bat_mv'], SQLITE3_INTEGER);
    $stmt->bindValue(14, $fields['solar_mv'], SQLITE3_INTEGER);
    $stmt->bindValue(15, $fields['loop_time_s'], SQLITE3_INTEGER);
    $stmt->bindValue(16, $fields['gps_fix'], SQLITE3_INTEGER);
    $stmt->bindValue(17, $data['payload_raw'], SQLITE3_TEXT);

    $stmt->execute();
}

/**
 * Check if user credentials are correct
 *
 * @param user      Username
 * @param pass      Password
 * @return True if valid
 */
function validateUser($user, $pass)
{
    if ($user != Config::get('username') || $pass != Config::get('password')) {
        return false;
    }
    return true;
}

if (!isset($_SERVER['PHP_AUTH_USER'])) {
    header('WWW-Authenticate: Basic realm="My Realm"');
    error('Authorization required', 401);
    exit;
} else if (!validateUser($_SERVER['PHP_AUTH_USER'], $_SERVER['PHP_AUTH_PW'])){
    error('Invalid user/password combination', 401);
    exit;
}

if ($_SERVER['REQUEST_METHOD'] === 'POST') {
    $data = json_decode(file_get_contents('php://input'), true);
    /* Store data to file, just in case something goes wrong */
    file_put_contents("received.txt", print_r($data, true), FILE_APPEND);
    storeData($data);
} else {
    error('Expecting post data with json encoded payload', 404);
    exit;
}

echo "Success";
