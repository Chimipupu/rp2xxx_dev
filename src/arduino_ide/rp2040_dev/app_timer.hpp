/**
 * @file app_timer.hpp
 * @author ちみ/Chimi(https://github.com/Chimipupu)）
 * @brief RP2040 タイマーヘッダー
 * @version 0.1
 * @date 2024-11-05
 * 
 * @copyright Copyright (c) 2024 ちみ/Chimi(https://github.com/Chimipupu)）
 * 
 */

#ifndef APP_TIMER_HPP
#define APP_TIMER_HPP

#include <stdint.h>
#include "hardware/timer.h"
#include "common.hpp"
#include "app_neopixel.hpp"

void app_timer_set_alarm(uint8_t alarm_num, uint32_t time_ms);
uint32_t app_get_time_us(void);

#endif /* APP_TIMER_HPP */