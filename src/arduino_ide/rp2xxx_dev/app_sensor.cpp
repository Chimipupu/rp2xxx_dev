/**
 * @file app_sensor.cpp
 * @author ちみ/Chimi(https://github.com/Chimipupu)
 * @brief センサー制御アプリ
 * @version 0.1
 * @date 2024-11-28
 * 
 * @copyright Copyright (c) 2024 ちみ/Chimi(https://github.com/Chimipupu)
 * 
 */

#include "app_sensor.hpp"
#include "drv_bme280.hpp"

sensor_app_data_t g_sensor_dat;

void app_sensor_init(void)
{
    drv_bme280_init();
}

void app_sensor_main(void)
{
    g_sensor_dat.bme280_dat = drv_bme280_main();
}