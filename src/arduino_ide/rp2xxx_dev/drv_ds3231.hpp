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
#include <Wire.h>

typedef struct {
    uint8_t sec;     // 秒[0~59]
    uint8_t min;     // 分[0~59]
    uint8_t hour;    // 時[0~24]
    uint8_t wday;    // 曜日[日曜日~土曜日]
    uint8_t mday;    // 日[1~31]
    uint8_t mon;     // 月[1~12]
    uint8_t year;    // 年[0~99 ※2000年から数えて]
} rtc_time_date_t;

#define I2C_DS3231_SLAVE_ADDR      0x68 // DS3231 RTCのI2Cスレーブアドレス
#define DS3231_REG_SECONDS_ADDR    0x00

void drv_ds3231_init(void);
void drv_ds3231_get_time_date(rtc_time_date_t *p_tm);
void drv_ds3231_set_time_date(rtc_time_date_t *p_tm);

#endif /* DRV_DS3231_HPP */