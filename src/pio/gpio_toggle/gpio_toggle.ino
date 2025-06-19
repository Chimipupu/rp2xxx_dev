/**
 * @file gpio_toggle.ino
 * @author ちみ/Chimi（https://github.com/Chimipupu）
 * @brief PIOのGPIOトグルのinoファイル
 * @version 0.1
 * @date 2024-11-12
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include <stdint.h>
#include "gpio_toggle.pio.h"

// YD-RP2040
#define OB_LED_PIN             25   // 青色LED (GPIO 25)

// GPIOをトグルする周波数[Hz]
// CPU 133MHz 1サイクル = 1/133MHz ≒ 7.519ns
// freq = 1Hz, T ≒ (133MHz / (2 * freq) - 3) * 7.519ns * 2 [ms]
// freq = 2Hz, T ≒ (133MHz / (2 * freq) - 3) * 7.519ns * 2 [ms]
// freq = 3Hz, T ≒ (133MHz / (2 * freq) - 3) * 7.519ns * 2 [ms]
#define GPIO_TOGGLE_FREQ_HZ    2
static uint32_t s_clk_sys = 0;

void setup(void)
{
    // GPIO Init
    Serial.begin(115200);
    delay(3000);

    // PIO Init
    uint offset = pio_add_program(pio0, &gpio_toggle_program);
    Serial.printf("PIO0 SM%d, GPIO Pin %d Independent Toggle @%dHz\n", 0, OB_LED_PIN, GPIO_TOGGLE_FREQ_HZ);
    pio_gpio_toggle_hz(pio0, 0, offset, OB_LED_PIN, GPIO_TOGGLE_FREQ_HZ);

    s_clk_sys = clock_get_hz(clk_sys);
    Serial.printf("CLK_SYS = %d MHz\n", s_clk_sys / 1000000);
}

void loop(void)
{
    // NOP()
}