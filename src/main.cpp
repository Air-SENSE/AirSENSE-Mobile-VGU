#include "main.h"


void device_getData()
{
  struct sensorData sensorDataTemp_st;

  if(pms_getdata(sensorDataTemp_st.pm1_u32, sensorDataTemp_st.pm25_u32, sensorDataTemp_st.pm10_u32)== ERROR_NONE)
  {
    sensorData_st.pm1_u32   = sensorDataTemp_st.pm1_u32;
    sensorData_st.pm25_u32  = sensorDataTemp_st.pm25_u32;
    sensorData_st.pm10_u32  = sensorDataTemp_st.pm10_u32;
  }
  if(bme_readData(sensorDataTemp_st.temperature, sensorDataTemp_st.humidity, sensorDataTemp_st.pressure_u32) == ERROR_NONE)
    {
    sensorData_st.temperature   = sensorDataTemp_st.temperature;
    sensorData_st.humidity      = sensorDataTemp_st.humidity;
    sensorData_st.pressure_u32  = sensorDataTemp_st.pressure_u32;
  }
  if(bat_getdata(sensorDataTemp_st.bat_v_f) == ERROR_NONE)
  {
    sensorData_st.bat_v_f  = sensorDataTemp_st.bat_v_f;
  }
  if(gps_getdata(sensorDataTemp_st.lat_f, sensorDataTemp_st.lon_f) == ERROR_NONE)
  {
    sensorData_st.lat_f  = sensorDataTemp_st.lat_f;
    sensorData_st.lon_f  = sensorDataTemp_st.lon_f;
  }
}

void device_dataManagement()
{  
  struct sensorData sensorDataTemp_st;
  sensorDataTemp_st = sensorData_st;
  DS3231_getStringDateTime(realTime, DateTime::TIMESTAMP_FULL , dateTime_string);	
  createSensorDataString(sensorDataString, NAME_DEVICE, dateTime_string ,sensorDataTemp_st);
	DS3231_getStringDateTime(realTime, DateTime::TIMESTAMP_DATE, nameFileSaveData);
	SDcard_saveStringDataToFile(&connectionStatus_st, sensorDataString);
#ifdef USING_MQTT
  createMessageMQTTString(messageData, (const char *)espID, timeClient, sensorDataTemp_st);
  MQTT_postData(messageData.c_str(), &connectionStatus_st, mqttClient);
#endif

}

void setup() {
    Serial.begin(SERIAL_DEBUG_BAUDRATE);
    Serial2.begin(SERIAL_DEBUG_BAUDRATE);
    pinMode(PIN_BATTERY_VOL, INPUT);
    log_e("Booting...");
    Wire.begin(PIN_SDA_GPIO, PIN_SCL_GPIO, I2C_CLOCK_SPEED);
    bme_initialize(Wire);
    pms_init();
    gps_init();
    bat_init();
#ifdef USING_SDCARD
	SDcard_init(PIN_NUM_CLK, PIN_NUM_MISO, PIN_NUM_MOSI, PIN_CS_SD_CARD, &connectionStatus_st);
#endif
    WIFI_init();
	  DS3231_init(realTime, timeClient, Wire, connectionStatus_st);
#ifdef USING_MQTT
	MQTT_initClient(topic, espID, mqttClient, &connectionStatus_st);
	timeClient.begin();
#elif
    WiFi.disconnect();
#endif
    log_e("Init Done");
}

unsigned long device_previousDataControl = 0;
unsigned long device_previousWifiReconnect = 0;

void loop() {
  // get data from all sensor

   while (SerialGPS.available() >0) {
       gps.encode(SerialGPS.read());
    }
  if(millis() - device_previousDataControl > DEVICE_DATA_SAVE_INTERVAL) 
  {
    device_getData();
    device_dataManagement();
    device_previousDataControl = millis();
  }
#ifdef USING_MQTT
  // if WiFi is down, try reconnecting every CHECK_WIFI_TIME seconds
  if ((WiFi.status() != WL_CONNECTED) && (millis() - device_previousWifiReconnect >= WIFI_CONNECT_INTERVAL)) {
    log_e("Reconnecting to WiFi...");
    WiFi.disconnect();
    WiFi.reconnect();
    device_previousWifiReconnect = millis();
  }
#endif

}