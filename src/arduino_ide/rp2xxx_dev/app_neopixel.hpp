/**
 * @file app_neopixel.hpp
 * @author ちみ/Chimi(https://github.com/Chimipupu)
 * @brief NeoPixelアプリ
 * @version 0.1
 * @date 2024-10-16
 * 
 * @copyright Copyright (c) 2024 ちみ/Chimi(https://github.com/Chimipupu)
 * 
 */
#ifndef APP_NEOPIXEL_HPP
#define APP_NEOPIXEL_HPP

#include "common.hpp"
#ifdef __NEOPIXEL_ENABLE__
#include <Adafruit_NeoPixel.h>
#endif /* __NEOPIXEL_ENABLE__ */

typedef struct {
    uint8_t red;        // 赤色の輝度 (0-255)
    uint8_t green;      // 緑色の輝度 (0-255)
    uint8_t blue;       // 青色の輝度 (0-255)
    uint8_t brightness; // LEDの明るさ (0-255)
    bool onoff;         // LEDがオンかオフか
    bool autoled;       // 自動制御のフラグ
} rgbled_state_t;

void app_led_fade(uint8_t pin);
void app_neopixel_fade(void);
void app_neopixel_init(void);
void app_neopixel_ctrl(uint8_t red,uint8_t green, uint8_t blue, uint8_t led_no, uint8_t onoff, bool is_fade);
#endif /* APP_NEOPIXEL_HPP */