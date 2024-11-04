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

#ifdef __FREERTOS_USE__
void vTaskCore1monitor(void *param)
{
    while (1)
    {
        // DEBUG_PRINT("[Core1]vTaskCore1monitor\n");

        // モニタプログラム
        WDT_TOGGLE;
        cpm_main();
        WDT_TOGGLE;
        // delay(300);
        vTaskDelay(200 / portTICK_PERIOD_MS);
    }
}
#endif /* __FREERTOS_USE__ */

void app_main_init_core1(void)
{
    // OLED 初期化
    // app_oled_init();
    // app_oled_test();
    // DEBUG_PRINTF("[Core1] ... Init\n");
#ifdef __FREERTOS_USE__
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
#ifdef __FREERTOS_USE__
    // DEBUG_PRINTF("[Core0]app_main_core0\n");
    // SW_DELAY_MS(MAIN_DELAY);
    vTaskSuspend(NULL);
#else
    # if 0
    static uint8_t s_val = 0;

    DEBUG_PRINTF("[Core1] ... This is Application Core\n");

    i2c_scan();

    // LEDのトグル
    digitalWrite(OB_LED_PIN, s_val);
    s_val = !s_val;

    //(TBD) OLED メイン
    app_oled_test();
    #endif
    // モニタプログラム
    cpm_main();

    // SW_DELAY_MS(MAIN_DELAY);
#endif
}