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

/**
 * Throw http error and die
 *
 * @param message   Message to be shown
 * @param code      HTTP error code
 */
function error($message, $code)
{
    switch ($code) {
        case 301:
            $string = "301 Moved Permanently";
            break;
        case 401:
            $string = "401 Unauthorized";
            break;
        case 404:
            $string = "404 Not Found";
            break;
        case 503:
            $string = "503 Service Unavaliable";
            break;
        default:
            $string = "500 Internal Server Error";
            break;
    }

    header($_SERVER["SERVER_PROTOCOL"]." ".$string);
    echo "ERROR: $message";
    exit;
}
