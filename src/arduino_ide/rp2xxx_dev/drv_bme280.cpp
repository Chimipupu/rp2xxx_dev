/**
 * @file drv_bme280.cpp
 * @author ちみ/Chimi(https://github.com/Chimipupu)
 * @brief BME280 ドライバ
 * @version 0.1
 * @date 2024-11-28
 * 
 * @copyright Copyright (c) 2024　ちみ/Chimi(https://github.com/Chimipupu)
 * 
 */

#include "drv_bme280.hpp"

#ifdef __SENSOR_ENABLE__
#include <Wire.h>
// #include <SPI.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

static Adafruit_BME280 s_bme280;
bme280_data_t g_bme280_data;

static void bme280_read_data(bme280_data_t *p_bme280_data);

static void bme280_read_data(bme280_data_t *p_bme280_data)
{
    p_bme280_data->temperature = s_bme280.readTemperature();
    p_bme280_data->humidity = s_bme280.readHumidity();
    p_bme280_data->pressure = s_bme280.readPressure() / 100.0F;
    p_bme280_data->altitude = s_bme280.readAltitude(PRESSURE_HPA);
}
#endif /* __SENSOR_ENABLE__ */

void drv_bme280_init(void)
{
#ifdef __SENSOR_ENABLE__
    bool ret = s_bme280.begin(I2C_GYBME280_SLAVE_ADDR, &Wire1);
#endif /* __SENSOR_ENABLE__ */
}

void drv_bme280_data_print(void)
{
    DEBUG_PRINTF("temperature : %.03f °C\n", g_bme280_data.temperature);
    DEBUG_PRINTF("humidity : %.03f %%\n", g_bme280_data.humidity);
    DEBUG_PRINTF("pressure : %.03f hPa\n", g_bme280_data.pressure);
    DEBUG_PRINTF("altitude : %.03f m\n", g_bme280_data.altitude);
}

void drv_bme280_main(void)
{
#ifdef __SENSOR_ENABLE__
    bme280_read_data(&g_bme280_data);
#endif /* __SENSOR_ENABLE__ */
}