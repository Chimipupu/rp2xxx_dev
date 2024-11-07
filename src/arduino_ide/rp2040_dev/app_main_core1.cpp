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

static uint8_t s_cpu_core = 0;
#ifdef OLED_USE
static xTaskHandle s_xTaskCore1oled;
#endif /* OLED_USE */
static xTaskHandle s_xTaskCore1monitor;
static xTaskHandle s_xTaskCore1Main;

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
        g_firmware_info = PROC_NOW;
        cpm_main();
        g_firmware_info = FW_IDLE;
        WDT_TOGGLE;
        vTaskDelay(200 / portTICK_PERIOD_MS);
    }
}

void vTaskCore1Main(void *p_parameter)
{
    DEBUG_PRINTF("[Core%X] vTaskCore1Main\n", s_cpu_core);

    while (1)
    {
        g_firmware_info = PROC_NOW;
        // TODO: Core1メイン処理
        NOP;
        g_firmware_info = FW_IDLE;
        WDT_TOGGLE;
        vTaskDelay(100 / portTICK_PERIOD_MS);
    }
}

void app_main_init_core1(void)
{
    s_cpu_core = app_util_get_cpu_core_num();
    WDT_TOGGLE;
    DEBUG_PRINTF("[Core%X] ... Init\n", s_cpu_core);

#ifdef OLED_USE
    app_oled_init();

    xTaskCreate(vTaskCore1oled,         // コールバック関数ポインタ
                "vTaskCore1oled",       // タスク名
                512,                    // スタック
                nullptr,                // パラメータ
                2,                      // 優先度(0～7、7が最優先)
                &s_xTaskCore1oled       // タスクハンドル
                );
#endif /* OLED_USE */

    xTaskCreate(vTaskCore1monitor,      // コールバック関数ポインタ
                "vTaskCore1monitor",    // タスク名
                2048,                   // スタック
                nullptr,                // パラメータ
                5,                      // 優先度(0～7、7が最優先)
                &s_xTaskCore1monitor    // タスクハンドル
                );

#if 0
    xTaskCreate(vTaskCore1Main,         // コールバック関数ポインタ
                "vTaskCore1Main",       // タスク名
                2048,                   // スタック
                nullptr,                // パラメータ
                7,                      // 優先度(0～7、7が最優先)
                &s_xTaskCore1Main       // タスクハンドル
                );
#endif

    g_firmware_info = FW_IDLE;
}

void app_main_core1(void)
{
    // DEBUG_PRINTF("[Core1]Core1 Loop Task\n");
    WDT_TOGGLE;
    vTaskSuspend(NULL);
}