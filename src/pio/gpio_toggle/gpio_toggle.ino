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

#include "gpio_toggle.pio.h"

// YD-RP2040
#define OB_LED_PIN    25   // 青色LED (GPIO 25)

void setup(void)
{
    uint offset = pio_add_program(pio0, &gpio_toggle_program);
    pio_gpio_init(pio0, 0, offset, OB_LED_PIN);
}

void loop(void)
{
    // NOP
}