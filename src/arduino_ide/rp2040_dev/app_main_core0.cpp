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
#include "app_neopixel.hpp"
// #include "app_oled.hpp"
// #include "app_util.hpp"

#define MAIN_DELAY      200

static void gpio_init(void);

static void gpio_init(void)
{
    // GPIO Init
    pinMode(BUTTON_PIN, INPUT_PULLUP);
    pinMode(OB_LED_PIN, OUTPUT);
    digitalWrite(OB_LED_PIN, LOW);
}

#ifdef __FREERTOS_USE__
void vTaskCore0LED(void *param)
{
    static uint8_t val = 0;

    while (1)
    {
        // DEBUG_PRINT("[Core0]vTaskCore0LED\n");
        // digitalWrite(OB_LED_PIN, val);
        // val = !val;
        WDT_TOGGLE;
        vTaskDelay(100 / portTICK_PERIOD_MS);
    }
}

void vTaskCore0Neopixel(void *param)
{
    while (1)
    {
        // DEBUG_PRINT("[Core0]vTaskCore0Neopixel\n");
        app_neopixel_main();
        WDT_TOGGLE;
        vTaskDelay(200 / portTICK_PERIOD_MS);
    }
}
#endif /* __FREERTOS_USE__ */

void app_main_init_core0(void)
{
    // UART 初期化
    DEBUG_PRINT_INIT(DEBUG_UART_BAUDRATE);

    // GPIO 初期化
    gpio_init();

    // タイマー初期化
    app_timer_set_alarm(0, 20000); // アラーム0, 20msec

    // NeoPicel 初期化
    app_neopixel_init();

    // OLED 初期化
    // app_oled_init();

    DEBUG_PRINTF("[Core0] ... Init\n");

#ifdef __FREERTOS_USE__
    xTaskCreate(vTaskCore0LED,    //
                "vTaskCore0LED",  //
                128,                 //
                nullptr,             //
                2,                   // 優先度
                nullptr              //
                );

    xTaskCreate(vTaskCore0Neopixel,    //
                "vTaskCore0Neopixel",  //
                128,                 //
                nullptr,             //
                2,                   // 優先度
                nullptr              //
                );
#endif /* __FREERTOS_USE__ */
}

void app_main_core0(void)
{
    // DEBUG_PRINTF("[Core0] ... This is Driver Core\n");

    // NeoPixel メイン
    app_neopixel_main();

    // OLED メイン
    // (TBD)
    // app_oled_test();

    SW_DELAY_MS(MAIN_DELAY);
}