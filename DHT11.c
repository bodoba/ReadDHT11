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

#include "DHT11.h"

int8_t dht11_get_pulse( uint8_t pin ) {
    int8_t   retval = DHT11_ERROR_TIMEOUT;
    uint16_t loopCnt = 10000;
    
    while(digitalRead(pin) == LOW && loopCnt--);
    if ( loopCnt > 0 ) {
        printf("  low: %d\n", loopCnt);
        loopCnt = 10000;
        unsigned long t = micros();
        while(digitalRead(pin) == HIGH && loopCnt--);
        if ( loopCnt > 0 ) {
            printf("  high: %d\n", loopCnt);
            retval = ((micros() - t) > 40) ? 1 : 0;
        }
    }
    printf("pulse: %d\n", retval);
    return retval;
}

int8_t dht11_read_val( uint8_t pin, uint8_t *humidity, uint8_t *celcius ) {
    int8_t retval=DHT11_ERROR;
    uint8_t bits[5] = {0,0,0,0,0};
    uint8_t cnt = 7;
    uint8_t idx = 0;
    
    // send request
    pinMode(pin, OUTPUT);
    digitalWrite(pin, LOW);
    delay(18);
    digitalWrite(pin, HIGH);
    delayMicroseconds(40);
    pinMode(pin, INPUT);
    
    if ( dht11_get_pulse(pin) == DHT11_OK ) {       // got ackknowledgement?
        for (int i=0; i<40; i++) {                  // read 5 bites (40bits)
            retval=dht11_get_pulse(pin);
            if ( retval >= 0  ) {                   // timeout?
                if ( retval > 0 ) bits[idx] |= (1 << cnt);
                if (cnt == 0) {                     // next byte?
                    cnt = 7;                        // restart at MSB
                    idx++;                          // next byte!
                } else {
                    cnt--;
                }
            } else {
                return retval;
            }
        }
        if ( bits[4] == (bits[0] + bits[2])) {      // calcutalate checksum
            if ( humidity ) *humidity = bits[0];
            if ( celcius )  *celcius  = bits[2];
            retval = DHT11_OK;
        } else {
            retval = DHT11_ERROR_CHECKSUM;
        }
    }
    return retval;
}
