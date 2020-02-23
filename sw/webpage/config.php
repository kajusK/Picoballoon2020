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

defined("IN_APP") or die("Unauthorized access");

require_once('error.php');

class Config
{
    private static $config = false;

    /**
     * Read value from database, throw 500 if not defined
     *
     * @param option    Name of the value to read
     * @return Corresponding value
     */
    public static function get($option) {
        if (!self::$config) {
            self::$config = parse_ini_file("config.ini");
            if (!self::$config) {
                error("Failed to parse config", 500);
                exit;
            }
        }

        if (!isset(self::$config[$option])) {
            error("Invalid condig file", 500);
            exit;
        }
        return self::$config[$option];
    }
}
