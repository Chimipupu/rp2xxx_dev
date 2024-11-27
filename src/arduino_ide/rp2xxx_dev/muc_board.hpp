/**
 * @file muc_board.hpp
 * @author ちみ/Chimi(https://github.com/Chimipupu)
 * @brief マイコン基板 ヘッダー
 * @version 0.1
 * @date 2024-11-13
 * 
 * @copyright Copyright (c) 2024 ちみ/Chimi(https://github.com/Chimipupu)
 * 
 */

#ifndef MUC_BOARDHPP
#define MUC_BOARDHPP

#include "common.hpp"
#include "rp2xxx.hpp"

#ifdef MCU_RP2040
    #define __DEBUG_MONITOR_ENABLE__

    // #define __MCU_BOARD_PICO__
    // #define __MCU_BOARD_PICO_W__
    #define __MCU_BOARD_YD_RP2040__
    // #define __MCU_BOARD_XIAO_RP2040__
    // #define __MCU_EX_XIAO_EXPANSION__
    // #define __MCU_EX_BOARD_PICO_VGA__

    // Pico W
    #ifdef __MCU_BOARD_PICO_W__
        #define RGBLED_PIN               20  // Neopixel (GPIO 20)
        #define OB_LED_PIN               0   // 緑色LED (GPIO 0)
        #define BUTTON_PIN               19  // ボタン (GPIO 19)
        // PWM
        #define PWM_PIN                  22
        #define PWM_PIN_2                21
        // I2C
        #define I2C_SDA                  6   // I2C SDA (GPIO 6)
        #define I2C_SCL                  7   // I2C SCL (GPIO 7)
        // SPI
        #define SPI_CS_PIN               5   // SPI CS
        #define SPI_SCK_PIN              6   // SPI CLK
        #define SPI_MISO_PIN             4   // SPI MOSI
        #define SPI_MOSI_PIN             7   // SPI MISO
    #endif /* __MCU_BOARD_PICO_W__ */

    // VCC-GND RP2040
    #ifdef __MCU_BOARD_YD_RP2040__
        #define RGBLED_PIN               23  // Neopixel (GPIO 23)
        #define OB_LED_PIN               25  // 青色LED (GPIO 25)
        #define BUTTON_PIN               24  // ボタン (GPIO 24)
        // PWM
        #define PWM_PIN                  22
        #define PWM_PIN_2                21
        // I2C
        #define I2C_SDA                  6   // I2C SDA (GPIO 6)
        #define I2C_SCL                  7   // I2C SCL (GPIO 7)
        // SPI
        #define SPI_SCK_PIN              6   // SPI CLK
        #define SPI_MISO_PIN             4   // SPI MISO
        #define SPI_MOSI_PIN             7   // SPI MOSI
        #define SPI_CS_PIN               5   // SPI CS
    #endif /* __MCU_BOARD_YD_RP2040__ */

    // XIAO RP2040
    #ifdef __MCU_BOARD_XIAO_RP2040__
        #define RGBLED_PIN               12  // Neopixel (GPIO 12)
        #define OB_LED_RED_PIN           17  // 赤色LED  (GPIO 17)
        #define OB_LED_GREEN_PIN         16  // 緑色LED  (GPIO 16)
        #define OB_LED_PIN               25  // 青色LED  (GPIO 25)
        #define BUTTON_PIN               27  // ボタン (GPIO 27)

        // PWM
        #define PWM_PIN                  22
        #define PWM_PIN_2                21

        // I2C
        #define I2C_SDA                  6   // I2C SDA (GPIO 6)
        #define I2C_SCL                  7   // I2C SCL (GPIO 7)
    #endif /* __MCU_BOARD_XIAO_RP2040__ */

    // XIAO Expansion Board
    #ifdef __MCU_EX_XIAO_EXPANSION__
        // #define BUTTON_PIN             27  // ボタン (GPIO 27)
        #define BUZZUER_PIN            29  // ブザー (GPIO 29)

        // SPI
        #define SPI_SCK_PIN             2   // SPI CLK
        #define SPI_MISO_PIN            3   // SPI MISO
        #define SPI_MOSI_PIN            4   // SPI MOSI
        #define SPI_CS_PIN              28  // SPI CS
    #endif /* __MCU_EX_XIAO_EXPANSION__ */

    // Pimoroni Pico VGA Demo Base
    #ifdef __MCU_EX_BOARD_PICO_VGA__
        // SD
        #define SD_CLK_PIN              7   // SPI CLK
        #define SD_CMD_PIN              24  // SPI MOSI
        #define SD_DAT_0_PIN            25  // SPI MISO
        #define SD_DAT_1_PIN            26  // 未使用（microSDでは不要）
        #define SD_DAT_2_PIN            27  // 未使用（microSDでは不要）
        #define SD_DAT_3_PIN            29  // SPI CS

        // SPI
        #define SPI_SCK_PIN              7   // SPI CLK
        #define SPI_MISO_PIN             24  // SPI MISO
        #define SPI_MOSI_PIN             25  // SPI MOSI
        #define SPI_CS_PIN               29  // SPI CS

        // Button(SW_A ～ SW_C)
        #define SW_A_PIN                1
        #define SW_B_PIN                9
        #define SW_C_PIN                15

        // VGA
        #define VGA_RED_0_PIN           1
        #define VGA_RED_1_PIN           2
        #define VGA_RED_2_PIN           4
        #define VGA_RED_3_PIN           5
        #define VGA_RED_4_PIN           6

        #define VGA_GREEN_0_PIN         9
        #define VGA_GREEN_1_PIN         10
        #define VGA_GREEN_2_PIN         11
        #define VGA_GREEN_3_PIN         12
        #define VGA_GREEN_4_PIN         14

        #define VGA_BLUE_0_PIN          15
        #define VGA_BLUE_1_PIN          16
        #define VGA_BLUE_2_PIN          17
        #define VGA_BLUE_3_PIN          19
        #define VGA_BLUE_4_PIN          20

        #define VGA_V_SYNC_PIN          22
        #define VGA_H_SYNC_PIN          21

        // PWM
        #define PWM_0_PIN               34
        #define PWM_1_PIN               32

        // PCM
        #define PCM_LRCLK_PIN           34
        #define PCM_BCLK_PIN            32
        #define PCM_DATA_PIN            31
    #endif /* __MCU_EX_BOARD_PICO_VGA__ */
#endif /* MCU_RP2040 */

#ifdef MCU_RP2350
    #define __MCU_BOARD_PICO_2__
    #ifdef __MCU_BOARD_PICO_2__
        // GPIO
        #define OB_LED_PIN               25  // 基板の緑LED
        #define RGBLED_PIN               22  // Neopixel
        #define BUTTON_PIN               28  // ボタン
        // I2C
        #define I2C_SDA                  6   // I2C0 SDA
        #define I2C_SCL                  7   // I2C0 SCL
        #define I2C_1_SDA                10  // I2C1 SDA
        #define I2C_1_SCL                11  // I2C1 SCL
        // SPI
        #define SPI_CS_PIN               1   // SPI0 CS
        #define SPI_SCK_PIN              2   // SPI0 CLK
        #define SPI_MISO_PIN             0   // SPI0 MISO
        #define SPI_MOSI_PIN             3   // SPI0 MOSI
        // UART
        #define UART_TX_PIN              12  // UART0 TX
        #define UART_RX_PIN              13  // UART0 RX
        // その他
        #define __SD_TF_ENABLE__
        #define __LCD_ENABLE__
        #define __DEBUG_MONITOR_ENABLE__
        #define __BENCHMARK_TEST__
    #endif /* __MCU_BOARD_PICO_2__ */
#endif /* MCU_RP2350 */

extern "C"
{
    static inline void NOP(void)
    {
        asm volatile("nop");
    }
}

void mcu_board_gpio_init(void);
void mcu_board_fs_init(void);
#endif /* MUC_BOARDHPP */