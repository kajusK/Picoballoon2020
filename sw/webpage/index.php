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

    while ($row = $result->fetchArray) {
        $data[$i] = $row;
        $i++;
    }
    return $data;
}

$data = getData();
extract(['data'=> $data]);
require('page.phtml');
