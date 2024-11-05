/**
 * @file app_main_core0.cpp
 * @author ちみ/Chimi（https://github.com/Chimipupu）
 * @brief  Core0 アプリ
 * @version 0.1
 * @date 2024-10-16
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include "app_main_core0.hpp"
#include "app_timer.hpp"
#include "app_btn.hpp"
#include "app_neopixel.hpp"
#include "app_util.hpp"

#define MAIN_DELAY      200
static uint8_t s_cpu_core = 0;

static void gpio_init(void);

static void gpio_init(void)
{
    // GPIO Init
    app_btn_init();
    pinMode(OB_LED_PIN, OUTPUT);
    digitalWrite(OB_LED_PIN, LOW);
}

void vTaskCore0Btn(void *p_parameter)
{
    ButtonState btnstate;
    DEBUG_PRINTF("[Core%X] vTaskCore0Btn\n", s_cpu_core);

    while (1)
    {
        WDT_TOGGLE;
        app_btn_polling(btnstate);
        WDT_TOGGLE;
        vTaskDelay(300 / portTICK_PERIOD_MS);
    }
}

void vTaskCore0Neopixel(void *param)
{
    DEBUG_PRINTF("[Core%X] vTaskCore0Neopixel\n", s_cpu_core);

    while (1)
    {
        WDT_TOGGLE;
        app_neopixel_main();
        WDT_TOGGLE;
        vTaskDelay(500 / portTICK_PERIOD_MS);
    }
}

void app_main_init_core0(void)
{
    // WDT初期化
    app_wdt_init();
    WDT_TOGGLE;

    // UART 初期化
    DEBUG_PRINT_INIT(DEBUG_UART_BAUDRATE);

    // GPIO 初期化
    gpio_init();

    // タイマー初期化
    app_timer_set_alarm(0, 20000); // アラーム0, 20msec

    // NeoPicel 初期化
    app_neopixel_init();

    s_cpu_core = app_util_get_cpu_core_num();
    WDT_TOGGLE;
    DEBUG_PRINTF("[Core%X] ... Init\n", s_cpu_core);

#if 1
    xTaskCreate(vTaskCore0Btn,          // コールバック関数ポインタ
                "vTaskCore0Btn",        // タスク名
                512,                    // スタック
                nullptr,                // パラメータ
                2,                      // 優先度(0～7、7が最優先)
                nullptr                 // タスクハンドル
                );

    xTaskCreate(vTaskCore0Neopixel,     // コールバック関数ポインタ
                "vTaskCore0Neopixel",   // タスク名
                256,                    // スタック
                nullptr,                // パラメータ
                1,                      // 優先度(0～7、7が最優先)
                nullptr                 // タスクハンドル
                );
#endif
}

void app_main_core0(void)
{
    // DEBUG_PRINTF("[Core0]Core0 Loop Task\n");
    WDT_TOGGLE;
    vTaskSuspend(NULL);
}