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
 * Store received data to sqlite database (create if not present)
 *
 * @param data      Dictionary with json data from TTN
 */
function storeData($data)
{
    $db = new SQLite3(Config::get('db_file'));
    $db->exec('CREATE TABLE IF NOT EXISTS data (time text,
        frequency REAL,
        rssi INTEGER,
        lora_lat REAL,
        lora_lon REAL,
        lora_alt INTEGER,
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
        raw TEXT)');

    $stmt = $db->prepare('INSERT INTO log VALUES
        (?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?)');

    $meta = $data['metadata'];
    $gw = $meta['gateways'][0];
    $fields = $data['payload_fields'];

    $stmt->bindValue(1, $meta['time'], SQLITE3_TEXT);
    $stmt->bindValue(2, $meta['frequency'], SQLITE3_REAL);
    $stmt->bindValue(3, $gw['rssi'], SQLITE3_INTEGER);
    $stmt->bindValue(4, $meta['latitude'], SQLITE3_REAL);
    $stmt->bindValue(5, $meta['longitude'], SQLITE3_REAL);
    $stmt->bindValue(6, $meta['altitude'], SQLITE3_INTEGER);
    $stmt->bindValue(7, $fields['pressure_pa'], SQLITE3_INTEGER);
    $stmt->bindValue(8, $fields['temp_c'], SQLITE3_REAL);
    $stmt->bindValue(9, $fields['core_temp_c'], SQLITE3_REAL);
    $stmt->bindValue(10, $fields['RH'], SQLITE3_INTEGER);
    $stmt->bindValue(11, $fields['alt_m'], SQLITE3_INTEGER);
    $stmt->bindValue(12, $fields['lat'], SQLITE3_REAL);
    $stmt->bindValue(13, $fields['lon'], SQLITE3_REAL);
    $stmt->bindValue(14, $fields['bat_mv'], SQLITE3_INTEGER);
    $stmt->bindValue(15, $fields['solar_mv'], SQLITE3_INTEGER);
    $stmt->bindValue(16, $fields['loop_time_s'], SQLITE3_INTEGER);
    $stmt->bindValue(17, $fields['gps_fix'], SQLITE3_INTEGER);
    $stmt->bindValue(18, $data['payload_raw'], SQLITE3_TEXT);

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
    storeData($data);
} else {
    error('Expecting post data with json encoded payload', 404);
    exit;
}

echo "Success";
