/**
 * @file dev.ino
 * @author ちみ/Chimi（https://github.com/Chimipupu）
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

e_firmware_info g_firmware_info = FW_INIT;
SemaphoreHandle_t xSerialMutex;
// portMUX_TYPE g_mux = portMUX_INITIALIZER_UNLOCKED;

void core0_init(void)
{
    app_main_init_core0();
}

void core1_init(void)
{
    xSerialMutex = xSemaphoreCreateMutex();
    app_main_init_core1();
}

void core0_main(void)
{
    // DEBUG_PRINT("[Core0]app_main_core0\n");
    // SW_DELAY_MS(MAIN_DELAY);
    WDT_TOGGLE;
    vTaskSuspend(NULL);
}

void core1_main(void)
{
    // DEBUG_PRINT("[Core1]app_main_core1\n");
    // SW_DELAY_MS(MAIN_DELAY);
    WDT_TOGGLE;
    vTaskSuspend(NULL);
}