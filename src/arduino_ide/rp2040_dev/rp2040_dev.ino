/**
 * @file dev.ino
 * @author Chimipupu（https://github.com/Chimipupu）
 * @brief 評価プログラムの評価プログラム
 * @version 0.1
 * @date 2024-10-16
 * 
 * @copyright Copyright (c) 2024
 * 
 */
// C/C++ Std Lib
#include <stdio.h>
#include <stdint.h>
#include <string.h>

// SDK, IDE Lib
#include <Arduino.h>

// My App
#include "common.hpp"
#include "app_main_core0.hpp"
#include "app_main_core1.hpp"

#ifdef __FREERTOS_USE__
SemaphoreHandle_t xSerialMutex;
#endif /* __FREERTOS_USE__ */

void core0_init(void)
{
    app_main_init_core0();
#ifdef __WDT_ENABLE__
    // WDTの初期化
    if (watchdog_caused_reboot()) {
        DEBUG_PRINTF("Rebooted by WDT wanwan\n");
    }
    watchdog_enable(WDT_TIME_OUT, false);
#endif
}

void core1_init(void)
{
#ifdef __FREERTOS_USE__
    xSerialMutex = xSemaphoreCreateMutex();
    app_main_init_core1();
#else
    app_main_init_core1();
#endif
}

void core0_main(void)
{
#ifdef __FREERTOS_USE__
    DEBUG_PRINT("[Core0]app_main_core0\n");
    // SW_DELAY_MS(MAIN_DELAY);
    vTaskSuspend(NULL);
#else
    app_main_core0();
#endif
}

void core1_main(void)
{
#ifdef __FREERTOS_USE__
    DEBUG_PRINT("[Core1]app_main_core1\n");
    // SW_DELAY_MS(MAIN_DELAY);
    vTaskSuspend(NULL);
#else
    app_main_core1();
#endif
}