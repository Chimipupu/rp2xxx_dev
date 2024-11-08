/**
 * @file muc_board.hpp
 * @author ちみ/Chimi（https://github.com/Chimipupu）
 * @brief マイコン基板 ヘッダー
 * @version 0.1
 * @date 2024-11-08
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef MUC_BOARDHPP
#define MUC_BOARDHPP

#include "common.hpp"

#define _MCU_RP2040_
// #define _MCU_RP2350_

#ifdef _MCU_RP2040_
    #include "rp2040_reg.hpp"

    #define __MCU_BOARD_YD_RP2040__
    #ifdef __MCU_BOARD_YD_RP2040__
        #define RGBLED_PIN          23   // Neopixel (GPIO 23)
        #define BUTTON_PIN          24   // ボタン (GPIO 24)
        #define OB_LED_PIN          25   // 青色LED (GPIO 25)
        // #define PWM_PIN             OB_LED_PIN
        #define PWM_PIN             22
        #define PWM_PIN_2           21
        #define I2C_SDA             6    // I2C SDA (GPIO 6)
        #define I2C_SCL             7    // I2C SCL (GPIO 7)
    #endif /* __MCU_BOARD_YD_RP2040__ */
#endif /* _MCU_RP2040_ */

extern "C"
{
    static inline void NOP(void)
    {
        asm volatile("nop");
    }
}

#endif /* MUC_BOARDHPP */