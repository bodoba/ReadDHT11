/*
 * ---------------------------------------------------------------------------------------
 * Copyright 2017 by Bodo Bauer <bb@bb-zone.com>
 *
 *
 * This file is part of the RPI DHT11 Sensor Client 'ReadDHT11'
 *
 * ReadDHT11 is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * ReadDHT11 is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with ReadDHT11.  If not, see <http://www.gnu.org/licenses/>.
 * ---------------------------------------------------------------------------------------
 */

#ifndef DHT11_h
#define DHT11_h

#include <stdio.h>
#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#define DHT11_OK                 0
#define DHT11_ERROR             -1
#define DHT11_ERROR_CHECKSUM    -2
#define DHT11_ERROR_TIMEOUT     -3

int8_t dht11_read_val( uint8_t pin, uint8_t *humidity, uint8_t *celcius );
// Input:
//   pin      -> GPIO ping DHT11 sensor is connected to
//
// Output:
//   humidity <- pointer to write humidity value to or NULL
//   celcius  <- pointer to write celcius value to or NULL
//
// Return value: DHT11_OK on success, DHT11_ERROR_* on failure

#endif /* DHT11_h */
