/**
 * @file app_main_core1.cpp
 * @author ちみ/Chimi（https://github.com/Chimipupu）
 * @brief  Core1 アプリ
 * @version 0.1
 * @date 2024-10-16
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include "app_main_core1.hpp"
// #include "app_neopixel.hpp"
#include "app_oled.hpp"
// #include "app_util.hpp"s

#include "cpm.hpp"

#define MAIN_DELAY          300

void vTaskCore1monitor(void *param)
{
    DEBUG_PRINTLN("[Core1] vTaskCore1monitor");
    while (1)
    {

        // モニタプログラム
        WDT_TOGGLE;
        cpm_main();
        WDT_TOGGLE;
        // delay(300);
        vTaskDelay(200 / portTICK_PERIOD_MS);
    }
}

void app_main_init_core1(void)
{
    DEBUG_PRINTF("[Core1] ... Init\n");

    xTaskCreate(vTaskCore1monitor,    // コールバック関数
                "vTaskCore1monitor",  // タスク名
                2048,                 // スタック
                nullptr,              //
                5,                    // 優先度(MAX8)
                nullptr               //
                );
}

void app_main_core1(void)
{
    // DEBUG_PRINTF("[Core1]Core1 Loop Task\n");
    vTaskSuspend(NULL);
}