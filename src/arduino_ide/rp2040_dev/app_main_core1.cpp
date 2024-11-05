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
#include "app_oled.hpp"
#include "app_util.hpp"
#include "cpm.hpp"

#define MAIN_DELAY          300
static uint8_t s_cpu_core = 0;

#ifdef OLED_USE
void vTaskCore1oled(void *p_parameter)
{
    DEBUG_PRINTF("[Core%X] vTaskCore1oled\n", s_cpu_core);

    while (1)
    {
        WDT_TOGGLE;
        app_oled_test();
        WDT_TOGGLE;
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}
#endif /* OLED_USE */

void vTaskCore1monitor(void *p_parameter)
{
    DEBUG_PRINTF("[Core%X] vTaskCore1monitor\n", s_cpu_core);
    digitalWrite(OB_LED_PIN, HIGH);

    while (1)
    {
        WDT_TOGGLE;
        cpm_main();
        WDT_TOGGLE;
        vTaskDelay(200 / portTICK_PERIOD_MS);
    }
}

void app_main_init_core1(void)
{
    s_cpu_core = app_util_get_cpu_core_num();
    WDT_TOGGLE;
    DEBUG_PRINTF("[Core%X] ... Init\n", s_cpu_core);

#ifdef OLED_USE
    app_oled_init();

    xTaskCreate(vTaskCore1oled,       // コールバック関数
                "vTaskCore1oled",     // タスク名
                1024,                 // スタック
                nullptr,              //
                2,                    // 優先度(MAX8)
                nullptr               //
                );
#endif /* OLED_USE */

#if 1
    xTaskCreate(vTaskCore1monitor,    // コールバック関数
                "vTaskCore1monitor",  // タスク名
                2048,                 // スタック
                nullptr,              //
                5,                    // 優先度(MAX8)
                nullptr               //
                );
#endif
}

void app_main_core1(void)
{
    // DEBUG_PRINTF("[Core1]Core1 Loop Task\n");
    WDT_TOGGLE;
    vTaskSuspend(NULL);
}