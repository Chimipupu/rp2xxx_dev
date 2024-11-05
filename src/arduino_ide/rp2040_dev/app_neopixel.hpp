/**
 * @file app_neopixel.hpp
 * @author ちみ/Chimi（https://github.com/Chimipupu）
 * @brief NeoPixelアプリ
 * @version 0.1
 * @date 2024-10-16
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#ifndef APP_NEOPIXEL_HPP
#define APP_NEOPIXEL_HPP

#include "common.hpp"
#include <Adafruit_NeoPixel.h>

#define RGBLED_NUM              1   // NEOPIEXLの数
#define MAX_BRIGHTNESS          16  // NEOPIEXLの最大輝度
#define LED_COLOR_ON_TIMER      100

void app_neopixel_init(void);
void app_neopixel_main(void);

#endif /* APP_NEOPIXEL_HPP */