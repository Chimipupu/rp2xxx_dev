/**
 * @file gpio_toggle.pio.h
 * @author ちみ/Chimi（https://github.com/Chimipupu）
 * @brief PIOのGPIOトグル inoファイル
 * @version 0.1
 * @date 2024-11-12
 * 
 * @copyright Copyright (c) 2024 ちみ/Chimi（https://github.com/Chimipupu）
 * 
 */

#pragma once

#if !PICO_NO_HARDWARE
#include "hardware/pio.h"
#endif

// ----------- //
// gpio_toggle //
// ----------- //

#define gpio_toggle_wrap_target 2
#define gpio_toggle_wrap 7
#define gpio_toggle_pio_version 0

static const uint16_t gpio_toggle_program_instructions[] = {
    0x80a0, //  0: pull   block                      
    0x6040, //  1: out    y, 32                      
            //     .wrap_target
    0xa022, //  2: mov    x, y                       
    0xe001, //  3: set    pins, 1                    
    0x0044, //  4: jmp    x--, 4                     
    0xa022, //  5: mov    x, y                       
    0xe000, //  6: set    pins, 0                    
    0x0047, //  7: jmp    x--, 7                     
            //     .wrap
};

#if !PICO_NO_HARDWARE
static const struct pio_program gpio_toggle_program = {
    .instructions = gpio_toggle_program_instructions,
    .length = 8,
    .origin = -1,
    .pio_version = 0,
#if PICO_PIO_VERSION > 0
    .used_gpio_ranges = 0x0
#endif
};

static inline pio_sm_config gpio_toggle_program_get_default_config(uint offset) {
    pio_sm_config c = pio_get_default_sm_config();
    sm_config_set_wrap(&c, offset + gpio_toggle_wrap_target, offset + gpio_toggle_wrap);
    return c;
}

/**
 * @brief PIO GPIOトグル初期化関数
 * 
 * @param pio pio0 or pio1
 * @param sm 0 or 1 or 2 or 3
 * @param offset program address
 * @param pin GPIO pin
 */
static inline void pio_gpio_init(PIO pio, uint sm, uint offset, uint pin) {
    pio_gpio_init(pio, pin);
    pio_sm_set_consecutive_pindirs(pio, sm, pin, 1, true);
    pio_sm_config c = gpio_toggle_program_get_default_config(offset);
    sm_config_set_set_pins(&c, pin, 1);
    pio_sm_init(pio, sm, offset, &c);
}

/**
 * @brief PIOが指定周波数でGPIOをトグルする関数
 * 
 * @param pio pio0 or pio1
 * @param sm 0 or 1 or 2 or 3
 * @param offset program address
 * @param pin GPIO pin
 * @param freq gpio toggle freq [Hz]
 */
static inline void pio_gpio_toggle_hz(PIO pio, uint sm, uint offset, uint pin, uint freq) {
    pio_gpio_init(pio, sm, offset, pin);
    pio_sm_set_enabled(pio, sm, true);

    // PIO counter program takes 3 more cycles in total than we pass as
    // input (wait for n + 1; mov; jmp)
    pio->txf[sm] = (clock_get_hz(clk_sys) / (2 * freq)) - 3;
}

#endif

