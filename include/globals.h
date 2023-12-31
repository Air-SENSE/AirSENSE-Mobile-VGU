/*
 * File: globals.h
 * Authors: Hank <hankso1106@gmail.com>
 * Create: 2019-04-20 00:34:02
 *
 * Copyright (c) 2019 EmBCI. All right reserved.
 *
 * Variables declared here are global to all source files in project.
*/

#ifndef GLOBALS_H
#define GLOBALS_H

#include "string.h"
#include "esp_log.h"
#include <WiFiUdp.h>
#include <WiFiClient.h>
#include <PubSubClient.h>
#include <NTPClient.h>
#include <RTClib.h>
#include "BME280I2C.h"
#include <PMserial.h> 
#include <ErriezMHZ19B.h>
#include "TinyGPS++.h";
#include <SoftwareSerial.h>

extern const char *NAME, *prompt;
extern struct sensorData sensorData_st;

extern char dateTime_string[25];
extern char dataCalib_string[50];
extern char sensorDataString[64];
extern String messageData;

extern const char* remote_host_string;

extern const char fileNameCalib[];
extern char nameFileSaveData[12];

extern char topic[32];
extern char espID[32];


extern struct sensorData sensorData_st;

extern struct calibData calibData_st;

extern struct connectionStatus connectionStatus_st;

extern BME280I2C bmeSensor;
extern SerialPM  pmsSensor;
extern ErriezMHZ19B mhz19b;
extern TinyGPSPlus gps;
extern EspSoftwareSerial::UART SerialGPS;


extern WiFiUDP ntpUDP;
extern WiFiClient espClient;
extern PubSubClient mqttClient;
extern NTPClient timeClient;

extern const char fileNameCalib[];			// file chua cac gia tri calib
extern char nameFileSaveData[12];							// ten file luu du lieu cua sensor theo tung ngay

extern const char* remote_host_string;
extern RTC_DS3231 realTime;

extern const char* const log_level_list[];

extern void verbose();
extern void quiet();
extern void version_info();

#endif // GLOBALS_H