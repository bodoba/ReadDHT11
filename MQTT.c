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

#include "MQTT.h"

static struct mosquitto *mosq = NULL;

bool mqtt_init( const char* broker, int port ) {
    bool success = true;
    int err;
    
    mosquitto_lib_init();
    mosq = mosquitto_new(NULL, true, NULL);
    if(mosq){
        err = mosquitto_connect(mosq, broker, port, MQTT_KEEPALIVE);
        if( err != MOSQ_ERR_SUCCESS ) {
            fprintf(stderr, "Error: mosquitto_connect [%s]\n", mosquitto_strerror(err));
            success = false;
        }
    } else {
        fprintf(stderr, "Error: Out of memory.\n");
        success = false;
    }
    
    err = mosquitto_loop_start(mosq);
    if( err != MOSQ_ERR_SUCCESS ) {
        fprintf(stderr, "Error: mosquitto_connect [%s]\n", mosquitto_strerror(err));
        success = false;
    }
    return success;
}

void mqtt_end( void ) {
    mosquitto_loop_stop(mosq, true);
    mosquitto_destroy(mosq);
    mosquitto_lib_cleanup();
    mosq = NULL;
}

bool mqtt_publish ( const char *topic, const char *message ) {
    bool success = true;
    int  err;

    if ( mosq ) {
        err = mosquitto_publish( mosq, NULL, topic, strlen(message), message, 0, false);
        if ( err != MOSQ_ERR_SUCCESS) {
            fprintf(stderr, "Error: mosquitto_publish failed [%s]\n", mosquitto_strerror(err));
            success = false;
        }
    } else {
        fprintf(stderr, "Error: mosq == NULL, Init failed?\n");
        success = false;
    }
    return success;
}
