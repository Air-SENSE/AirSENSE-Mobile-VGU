/**
 * @file GpsDriver.h
 * @author Le Chi Tuyen (@hocj2me)
 * @brief gps module 
 * @version 0.1
 * @date 2023-11-28
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef GPSDRIVER_H
#define GPSDRIVER_H 

#include <SoftwareSerial.h>
#include "types.h"
#include "TinyGPS++.h";
#include "HardwareSerial.h";
#include "configs.h"

TinyGPSPlus gps;

#define MYPORT_TX 15
#define MYPORT_RX 13

EspSoftwareSerial::UART SerialGPS;


#define ERROR_GPS_INIT_FAILED       0xa2
#define ERROR_GPS_GET_DATA_FAILED   0xa3

/**
 * @brief Initialize ADC
 *  
 * @return ERROR_CODE 
 * @retval ERROR_NONE: if success
 * @retval ERROR_BATTERY_INIT_FAILED: if failed
 */
ERROR_CODE gps_init();

/**
 * @brief Get new data from ADC 
 * 
 * @param[out] _vol: Battery VOLtage
 * 
 * @return ERROR_CODE 
 * @retval ERROR_NONE: if success
 * @retval ERROR_BATTERY_GET_DATA_FAILED: if failed
 */
ERROR_CODE gps_getdata(float  &_lat, float  &_lon);


ERROR_CODE gps_init()
{        
SerialGPS.begin(9600, SWSERIAL_8N1, MYPORT_RX, MYPORT_TX, false);

    return ERROR_NONE;
}

ERROR_CODE gps_getdata(double  &_lat, double  &_lon)
{
 
    _lat = gps.location.lat();
    _lon = gps.location.lng();
     Serial.print("LAT=");  Serial.println(gps.location.lat(), 6);
        Serial.print("LONG="); Serial.println(gps.location.lng(), 6);
        Serial.print("ALT=");  Serial.println(gps.altitude.meters());
    return ERROR_NONE;
}

#endif