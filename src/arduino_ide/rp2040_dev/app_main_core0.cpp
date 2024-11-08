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

static uint8_t s_cpu_core = 0;
static xTaskHandle s_xTaskCore0Btn;
static xTaskHandle s_xTaskCore0Main;

static void gpio_init(void);
static void pwm_init(void);

static void gpio_init(void)
{
    app_btn_init();
}

static void pwm_init(void)
{
    // GPIO 22
    gpio_set_function(PWM_PIN, GPIO_FUNC_PWM);          // GPIOピンをPWM機能に設定
    uint slice_num = pwm_gpio_to_slice_num(PWM_PIN);    // GPIOに対応するPWMスライスを取得
    pwm_set_clkdiv(slice_num, 133.0f);                  // 分周比を133に設定して、PWMクロックを1MHzに
    pwm_set_wrap(slice_num, 999);                       // カウント範囲を999に設定（1kHzの周期）
    pwm_set_chan_level(slice_num, PWM_CHAN_A, 500);     // デューティ比を50%に設定（500/1000）
    pwm_set_enabled(slice_num, true);                   // PWMを有効化

    // GPIO 21
    GPIO_PWM(PWM_PIN_2, 127);
}

void vTaskCore0Btn(void *p_parameter)
{
    ButtonState btnstate;
    DEBUG_PRINTF("[Core%X] vTaskCore0Btn\n", s_cpu_core);

    while (1)
    {
        app_btn_polling(btnstate);
        WDT_TOGGLE;
        vTaskDelay(300 / portTICK_PERIOD_MS);
    }
}

void vTaskCore0Main(void *p_parameter)
{
    DEBUG_PRINTF("[Core%X] vTaskCore0Main\n", s_cpu_core);

    while (1)
    {
        switch (g_firmware_info)
        {
            case FW_INIT:
            case RF_OFFLINE:
                app_neopixel_ctrl(16, 0, 0, 0, true, false); // 赤
                break;

            case RF_ONLINE:
                app_neopixel_ctrl(0, 0, 16, 0, true, false); // 青
                break;

            case FW_IDLE:
                app_neopixel_ctrl(16, 16, 16, 0, true, false); // 白
                break;

            case PROC_NOW:
                app_neopixel_ctrl(0, 16, 0, 0, true, false); // 緑
                break;

            default:
                app_neopixel_ctrl(16, 0, 16, 0, true, false); // 紫
                break;
        }
        WDT_TOGGLE;
        vTaskDelay(100 / portTICK_PERIOD_MS);
    }
}

void app_main_init_core0(void)
{
    // WDT s初期化
    app_wdt_init();
    WDT_TOGGLE;

    // GPIO 初期化
    gpio_init();

    // PWM 初期化
    pwm_init();

    // NeoPicel 初期化
    app_neopixel_init();
    app_neopixel_ctrl(16, 0, 0, 0, true, false); // 赤

    // タイマー初期化
    app_timer_set_alarm(0, 1);      // アラーム0, 1msec(実行時間計測用)
    app_timer_set_alarm(1, 8);      // アラーム1, 8msec(メインタスク起床)
    app_timer_set_alarm(2, 20);     // アラーム2, 20msec(ボタンタスク起床)
    app_timer_set_alarm(3, 1000);   // アラーム3, 1000msec(LEDを処理)

    // UART 初期化
    DEBUG_PRINT_INIT(DEBUG_UART_BAUDRATE);

    s_cpu_core = app_util_get_cpu_core_num();
    WDT_TOGGLE;
    DEBUG_PRINTF("[Core%X] ... Init\n", s_cpu_core);

    // FreeRTOS 初期化
    xTaskCreate(vTaskCore0Btn,          // コールバック関数ポインタ
                "vTaskCore0Btn",        // タスク名
                512,                    // スタック
                nullptr,                // パラメータ
                2,                      // 優先度(0～7、7が最優先)
                &s_xTaskCore0Btn        // タスクハンドル
                );

    xTaskCreate(vTaskCore0Main,         // コールバック関数ポインタ
                "vTaskCore0Main",       // タスク名
                2048,                   // スタック
                nullptr,                // パラメータ
                7,                      // 優先度(0～7、7が最優先)
                &s_xTaskCore0Main       // タスクハンドル
                );
}

void app_main_core0(void)
{
    // DEBUG_PRINTF("[Core0]Core0 Loop Task\n");
    WDT_TOGGLE;
    vTaskSuspend(NULL);
}