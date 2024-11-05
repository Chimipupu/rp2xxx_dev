/**
 * @file common.hpp
 * @author ちみ/Chimi（https://github.com/Chimipupu）
 * @brief RP2040の評価プログラム用 共通ヘッダー
 * @version 0.1
 * @date 2024-10-16
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef COMMON_HPP
#define COMMON_HPP

#include <Arduino.h>
#include <stdint.h>
#include "pico/stdlib.h"
#include "rp2040_reg.hpp"

// #define __WDT_ENABLE__
#include "app_wdt.hpp"

extern "C"
{
    static inline void NOP(void)
    {
        asm volatile("nop");
    }
}

// #define OLED_USE

/***********************************/
//          FreeRTOS関連
/***********************************/
#include <FreeRTOS.h>
#include <task.h>
#include <semphr.h>

// 割込みマスク・許可
#define __DI            taskENTER_CRITICAL
#define __EI            taskEXIT_CRITICAL
#define __DI_ISR        taskENTER_CRITICAL_FROM_ISR
#define __EI_ISR        taskEXIT_CRITICAL_FROM_ISR

extern SemaphoreHandle_t xSerialMutex;

// FreeRTOS用のprintf
#define DEBUG_PRINTF_RTOS   safeSerialPrintf
#ifdef DEBUG_PRINTF_RTOS
extern "C"
{
    static inline void safeSerialPrintf(const char *format, ...)
    {
        if (xSemaphoreTake(xSerialMutex, portMAX_DELAY) == pdTRUE) {
            va_list args;
            va_start(args, format);

            for (const char *p = format; *p != '\0'; p++) {
                if (*p == '%') {
                    p++;  // '%'の次の文字を見る
                    int width = 0;
                    int precision = -1;

                    // 幅の取得
                    while (*p >= '0' && *p <= '9') {
                        width = width * 10 + (*p - '0');
                        p++;
                    }

                    // 精度の取得
                    if (*p == '.') {
                        p++;
                        precision = 0;
                        while (*p >= '0' && *p <= '9') {
                            precision = precision * 10 + (*p - '0');
                            p++;
                        }
                    }

                    // フォーマット指定子に基づいて処理
                    switch (*p) {
                        case 'd':  // 整数
                            Serial.print(va_arg(args, int));
                            break;
                        case 'f':  // 浮動小数点数（float）
                        case 'l':  // 'l' は無視
                        case 'F':  // 浮動小数点数（float、大文字）
                            Serial.print(va_arg(args, double), (precision >= 0) ? precision : 2);
                            break;
                        case 's':  // 文字列
                            Serial.print(va_arg(args, char*));
                            break;
                        case 'c':  // 文字
                            Serial.print((char)va_arg(args, int));
                            break;
                        case 'x':  // 16進数（小文字）
                        case 'X':  // 16進数（大文字）
                            Serial.print(va_arg(args, int), HEX);
                            break;
                        default:  // 他のフォーマット指定子はそのまま表示
                            Serial.print(*p);
                            break;
                    }
                } else if (*p == '\r' || *p == '\n') {
                    // 改行シーケンスの処理
                    Serial.println(); // 改行
                } else {
                    // '%'でない文字はそのまま表示
                    Serial.print(*p);
                }
            }
            va_end(args);
            xSemaphoreGive(xSerialMutex);
        } else {
            Serial.println("Failed to acquire mutex!");
        }
    }
}
#endif /* DEBUG_PRINTF_RTOS */
/***********************************/

// typedef enum {
//     CPU_CORE_0 = 0x00,
//     CPU_CORE_1,
//     CPU_CORE_UNKNOWN = 0xFF
// } E_CPU_CORE;

#define DUAL_CORE_BUILD

// YD-RP2040の使用ピン
#define RGBLED_PIN          23   // Neopixel (GPIO 23)
#define BUTTON_PIN          24   // ボタン (GPIO 24)
#define OB_LED_PIN          25   // 青色LED (GPIO 25)
#define I2C_SDA             6    // I2C SDA (GPIO 6)
#define I2C_SCL             7    // I2C SCL (GPIO 7)

#define core0_init          setup
#define core0_main          loop
#define core1_init          setup1
#define core1_main          loop1
#define DEBUG_PRINT         Serial.print
#define DEBUG_PRINTLN       Serial.println
#define DEBUG_PRINTF        safeSerialPrintf
#define DEBUG_PRINT_INIT    Serial.begin

#define SW_DELAY_MS         delay

#define GPIO_PORT_DIR       pinMode
#define GPIO_OUTPUT         digitalWrite

#define ON                  0x00    // ON ... Active Low
#define OFF                 0x01

// I2Cスレーブ
#define QMC5883_I2C_ADDR    0x0D  // HMC5883のパチモン
#define HMC5883_I2C_ADDR    0x1E
#define MPU9250_I2C_ADDR    0x68
#define MPU6050_I2C_ADDR    0x69  // ADOピンをHIGH = 0x69(Low/HiZ = 0x68)
#define OLED_I2C_ADDR       0x3C

extern "C"
{
    static inline void GPIO_TOGGLE(uint8_t port)
    {
        static bool s_port_val = OFF;

        GPIO_OUTPUT(port, s_port_val);
        s_port_val = !s_port_val;
    }
} /* extern "C" */

#endif /* COMMON_HPP */