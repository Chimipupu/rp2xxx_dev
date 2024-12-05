/**
 * @file drv_bme280.hpp
 * @author ちみ/Chimi(https://github.com/Chimipupu)
 * @brief BME280 ドライバ ヘッダー
 * @version 0.1
 * @date 2024-11-28
 * 
 * @copyright Copyright (c) 2024　ちみ/Chimi(https://github.com/Chimipupu)
 * 
 */

#ifndef DRV_BME280_HPP
#define DRV_BME280_HPP

#include "common.hpp"

#define PRESSURE_HPA    1013.25 // 1気圧 = 約1013.25hPa
#define I2C_GYBME280_SLAVE_ADDR    0x76    // GY-BME280 (@I2C スレーブ)
// #define I2C_GYBME280_SLAVE_ADDR    0x77    // GY-BME280 (@I2C スレーブ ※SDOピンがLow)

typedef struct {
    double temperature; // 温度
    double humidity;    // 湿度
    double pressure;    // 気圧
    double altitude;    // 高度(メートル)
} bme280_data_t;

void drv_bme280_init(void);
void drv_bme280_data_print(void);
bme280_data_t drv_bme280_main(void);

#endif /* DRV_BME280_HPP */