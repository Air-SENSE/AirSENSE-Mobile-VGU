/**
 * @file PMS7003Sensor.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-11-20
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef PMS7003SENSOR_H
#define PMS7003SENSOR_H

#include <PMserial.h> // Arduino library for PM sensors with serial interface
#include "HardwareSerial.h"
#include "esp_log.h"
// #include "Plantower_PMS7003.h"
#include "configs.h"


SerialPM pmsSensor(PMSx003, Serial2); // PMSx003, UART

// Plantower_PMS7003 pmsSensor = Plantower_PMS7003();

#define ERROR_PMS_INIT_FAILED       0xe0
#define ERROR_PMS_GET_DATA_FAILED   0xe1

/**
 * @brief Initialize PMS7003 Sensor
 * 
 * @param[in] _stream: HardwareSerial stream use to communicate with MCU
 * 
 * @return ERROR_CODE 
 * @retval ERROR_NONE: if success
 * @retval ERROR_PMS_INIT_FAILED: if failed
 */
ERROR_CODE pms_init();

/**
 * @brief Get new data from PMS7003 sensor
 * 
 * @param[out] _pm_1_0: PM 1.0
 * @param[out] _pm_2_5: PM 2.5
 * @param[out] _pm_10_0: PM 10.0
 * 
 * @return ERROR_CODE 
 * @retval ERROR_NONE: if success
 * @retval ERROR_PMS_GET_DATA_FAILED: if failed
 */
ERROR_CODE pms_getdata(int32_t &_pm_1_0, int32_t &_pm_2_5, int32_t &_pm_10_0);


ERROR_CODE pms_init()
{
    // if ()
    // {  
          pmsSensor.init();
        log_e("PMS7003 Sensor initialize successfully!");
        return ERROR_NONE;
    // } else {
        // ESP_LOGI("Hardware serial not available.\r\nPMS7003 Sensor initialize failed!");
        // return ERROR_PMS_INIT_FAILED;
    // }
}

ERROR_CODE pms_getdata(uint32_t &_pm_1_0, uint32_t &_pm_2_5, uint32_t &_pm_10_0)
{
    if (pmsSensor)
    {
        // ESP_LOGI("\nSensor Version: %d.\n", pmsSensor.getHWVersion());
        _pm_1_0 = pmsSensor.pm01;
        _pm_2_5 = pmsSensor.pm25;
        _pm_10_0 = pmsSensor.pm10;

        // ESP_LOGI("PMS7003 Sensor get new data successfully!");
        return ERROR_NONE;
    } else {
        _pm_1_0 = NULL;
        _pm_2_5 = NULL;
        _pm_10_0 = NULL;
        // ESP_LOGI("PMS7003 Sensor get new data failed!");
        return ERROR_PMS_GET_DATA_FAILED;
    }
}

#endif