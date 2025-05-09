/**
 * @file common.hpp
 * @author ちみ/Chimi(https://github.com/Chimipupu)
 * @brief RP2040の評価プログラム用 共通ヘッダー
 * @version 0.1
 * @date 2024-10-16
 * 
 * @copyright Copyright (c) 2024 ちみ/Chimi(https://github.com/Chimipupu)
 * 
 */

#ifndef COMMON_HPP
#define COMMON_HPP

// C/C++ std
#include <stdint.h>
#include <string.h>

// Arduino IDE
#include <Arduino.h>

// SDK
#include "pico/stdlib.h"
#include "hardware/pwm.h"

// APP
#include "muc_board.hpp"
// #define __WDT_ENABLE__

#ifdef __WDT_ENABLE__
#include "app_wdt.hpp"
#endif /* __WDT_ENABLE__ */

#define ON                  0x00    // ON ... Active Low
#define OFF                 0x01

#define TRUE                0x01
#define FALSE               0x00

// 割込みマスク・許可
#define __DI                taskENTER_CRITICAL
#define __EI                taskEXIT_CRITICAL
#define __DI_ISR            taskENTER_CRITICAL_FROM_ISR
#define __EI_ISR            taskEXIT_CRITICAL_FROM_ISR

#define DUAL_CORE_BUILD

#define core0_init          setup
#define core0_main          loop
#define core1_init          setup1
#define core1_main          loop1
#define DEBUG_PRINT         Serial.print
#define DEBUG_PRINTLN       Serial.println
#define DEBUG_RTOS_PRINTF   safeSerialPrintf
#define DEBUG_PRINT_INIT    Serial.begin

#define SW_DELAY_MS         delay

// GPIO
#define GPIO_PORT_DIR       pinMode
#define GPIO_OUTPUT         digitalWrite
#define GPIO_PWM            analogWrite

typedef enum {
    FW_INIT = 0x00,
    RF_OFFLINE = 0x08,
    FW_IDLE = 0x10,
    PROC_NOW = 0x16,
    RF_ONLINE = 0x18,
    SLEEP_NOW = 0x1A,
    UART_ERR = 0x20,
    SPI_ERR = 0x30,
    I2C_ERR = 0x40,
    USB_ERR = 0x50,
    FILESYSTEM_ERR = 0x60,
    PSRAM_ERR = 0x70,
    PIO_ERR = 0x80,
    FW_ERR = 0xFF
} e_firmware_info;

extern e_firmware_info g_firmware_info;

static inline void NOP(void)
{
    asm volatile("nop");
}

static inline void GPIO_TOGGLE(uint8_t port)
{
    static bool s_port_val = OFF;

    GPIO_OUTPUT(port, s_port_val);
    s_port_val = !s_port_val;
}

/***********************************/
//          FreeRTOS関連
/***********************************/
#include <FreeRTOS.h>
#include <task.h>
#include <semphr.h>

#define TICKS_PER_SECOND 1000
#define USEC_TO_TICKS(us) ((us) / (1000000 / TICKS_PER_SECOND))

extern SemaphoreHandle_t xSerialMutex;
extern SemaphoreHandle_t xI2CMutex;

#ifdef DEBUG_RTOS_PRINTF
static inline void safeSerialPrintf(const char *p_format, ...)
{
    if (xSemaphoreTake(xSerialMutex, portMAX_DELAY) == pdTRUE) {
        va_list args;
        va_start(args, p_format);

        for(const char *p = p_format; *p != '\0'; p++)
        {
            if (*p == '%') {
                p++;  // '%'の次の文字を見る
                int width = 0;
                int precision = -1;

                // 幅の取得
                while(*p >= '0' && *p <= '9')
                {
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
                switch(*p)
                {
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
#endif /* DEBUG_RTOS_PRINTF */
/***********************************/

#endif /* COMMON_HPP */