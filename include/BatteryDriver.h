/**
 * @file BatteryDriver.h
 * @author Le Chi Tuyen (@hocj2me)
 * @brief Battery Voltage Monitoring 
 * @version 0.1
 * @date 2023-11-25
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef BATTERYDRIVER_H
#define BATTERYDRIVER_H

#include "esp_adc_cal.h"
#include "configs.h"

#define voltage_divider_offset 2.174 // Should be a value of 2.000, but ADC input impedance loads the voltage divider, requiring a correction
#define ADC_PIN     PIN_BATTERY_VOL               // Set for the Lolin D32 board with on-board voltage divider



#define ERROR_BATTERY_INIT_FAILED       0xa2
#define ERROR_BATTERY_GET_DATA_FAILED   0xa3

/**
 * @brief Initialize ADC
 *  
 * @return ERROR_CODE 
 * @retval ERROR_NONE: if success
 * @retval ERROR_BATTERY_INIT_FAILED: if failed
 */
ERROR_CODE bat_init();

/**
 * @brief Get new data from ADC 
 * 
 * @param[out] _vol: Battery VOLtage
 * 
 * @return ERROR_CODE 
 * @retval ERROR_NONE: if success
 * @retval ERROR_BATTERY_GET_DATA_FAILED: if failed
 */
ERROR_CODE bat_getdata(float  &_vol);


ERROR_CODE bat_init()
{
    return ERROR_NONE;
}

ERROR_CODE bat_getdata(float  &_vol)
{
 double reading = analogRead(PIN_BATTERY_VOL); // Reference voltage is 3v3 so maximum reading is 3v3 = 4095 in range 0 to 4095
  if(reading < 1 || reading > 4095) return 0;
  // return -0.000000000009824 * pow(reading,3) + 0.000000016557283 * pow(reading,2) + 0.000854596860691 * reading + 0.065440348345433;
  _vol = -0.000000000000016 * pow(reading,4) + 0.000000000118171 * pow(reading,3)- 0.000000301211691 * pow(reading,2)+ 0.001109019271794 * reading + 0.034143524634089;
  return ERROR_NONE;
}

#endif