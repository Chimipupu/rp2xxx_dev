/**
 * @file app_sensor.hpp
 * @author ちみ/Chimi(https://github.com/Chimipupu)
 * @brief センサー制御アプリ ヘッダー
 * @version 0.1
 * @date 2024-11-28
 * 
 * @copyright Copyright (c) 2024 ちみ/Chimi(https://github.com/Chimipupu)
 * 
 */

#ifndef APP_SENSOR_HPP
#define APP_SENSOR_HPP

#include "common.hpp"
#include "drv_bme280.hpp"

// I2Cスレーブ
#define QMC5883_I2C_ADDR    0x0D  // HMC5883のパチモン
#define HMC5883_I2C_ADDR    0x1E
#define MPU9250_I2C_ADDR    0x68
#define MPU6050_I2C_ADDR    0x69  // ADOピンをHIGH = 0x69(Low/HiZ = 0x68)

typedef struct {
    bme280_data_t bme280_dat;
} sensor_app_data_t;

void app_sensor_init(void);
void app_sensor_main(void);

#endif /* APP_SENSOR_HPP */