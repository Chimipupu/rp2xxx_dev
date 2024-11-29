/**
 * @file drv_ds3231.hpp
 * @author ちみ/Chimi(https://github.com/Chimipupu)
 * @brief DS3231 RTCのドライバ ヘッダー
 * @version 0.1
 * @date 2024-11-29
 * 
 * @copyright Copyright (c) 2024 ちみ/Chimi(https://github.com/Chimipupu)
 * 
 */

#ifndef DRV_DS3231_HPP
#define DRV_DS3231_HPP

#include <stdint.h>
#include <string.h>
#include <time.h>
#include <Wire.h>

#define I2C_DS3231_SLAVE_ADDR     0x68 // DS3231 RTCのI2Cスレーブアドレス
#define I2C_AT24C32_SLAVE_ADDR    0x57 // 32Kbit EEPROM AT24C32のI2Cスレーブアドレス

#define DS3231_REG_SECONDS_ADDR    0x00

void drv_ds3231_init(void);
void drv_ds3231_get_time_date(tm *p_tm);
void drv_ds3231_set_time_date(tm *p_tm);

#endif /* DRV_DS3231_HPP */