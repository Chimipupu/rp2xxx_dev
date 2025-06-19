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

// I2C
#define I2C_SDA                  20   // I2C0 SDA
#define I2C_SCL                  21   // I2C0 SCL
#define I2C_1_SDA                18   // I2C1 SDA
#define I2C_1_SCL                19   // I2C1 SCL
// SPI
#define SPI_CS_PIN               9   // SPI0 CS
#define SPI_SCK_PIN              6   // SPI0 CLK
#define SPI_MISO_PIN             8   // SPI0 MISO
#define SPI_MOSI_PIN             7   // SPI0 MOSI
#define SPI_1_CS_PIN             13  // SPI1 CS
#define SPI_1_SCK_PIN            10  // SPI1 CLK
#define SPI_1_MISO_PIN           12  // SPI1 MISO
#define SPI_1_MOSI_PIN           11  // SPI1 MOSI
// UART
#define UART_TX_PIN              0  // UART0 TX
#define UART_RX_PIN              1  // UART0 RX
#define UART_1_TX_PIN            4  // UART1 TX
#define UART_1_RX_PIN            5  // UART1 RX

#ifdef MCU_RP2040
    #define __DEBUG_MONITOR_ENABLE__
    // #define __MCU_BOARD_PICO__
    // #define __MCU_BOARD_PICO_W__
    #define __MCU_BOARD_YD_RP2040__
    // #define __MCU_BOARD_XIAO_RP2040__

    #ifdef __MCU_BOARD_PICO__
        // GPIO
        #define OB_LED_PIN               25  // 基板の緑LED
        #define RGBLED_PIN               22  // Neopixel
        #define BUTTON_PIN               28  // ボタン
        // その他
        #define __RTC_ENABLE__
        #define __SENSOR_ENABLE__
        #define __SD_TF_ENABLE__
        #define __LCD_ENABLE__
        #define __BENCHMARK_TEST__
        #define __DEBUG_MONITOR_ENABLE__
    #endif /* __MCU_BOARD_PICO__ */

    // Pico W
    #ifdef __MCU_BOARD_PICO_W__
        #define RGBLED_PIN               20  // Neopixel (GPIO 20)
        #define OB_LED_PIN               0   // 緑色LED (GPIO 0)
        #define BUTTON_PIN               19  // ボタン (GPIO 19)
        // その他
        // #define __WIFI_ENABLE__
        #define __BLUETOOTH_ENABLE__
        #define __RTC_ENABLE__
        #define __SENSOR_ENABLE__
        #define __SD_TF_ENABLE__
        #define __LCD_ENABLE__
        #define __BENCHMARK_TEST__
        #define __DEBUG_MONITOR_ENABLE__
    #endif /* __MCU_BOARD_PICO_W__ */

    // VCC-GND RP2040
    #ifdef __MCU_BOARD_YD_RP2040__
        #define RGBLED_PIN               23  // Neopixel (GPIO 23)
        #define OB_LED_PIN               25  // 青色LED (GPIO 25)
        #define BUTTON_PIN               24  // ボタン (GPIO 24)
        // その他
        #define __NEOPIXEL_ENABLE__
        #define __BTN_ENABLE__
        // #define __RTC_ENABLE__
        // #define __SENSOR_ENABLE__
        // #define __SD_TF_ENABLE__
        // #define __LCD_ENABLE__
        #define __BENCHMARK_TEST__
        #define __DEBUG_MONITOR_ENABLE__
    #endif /* __MCU_BOARD_YD_RP2040__ */

    // XIAO RP2040
    #ifdef __MCU_BOARD_XIAO_RP2040__
        #define RGBLED_PIN               12  // Neopixel (GPIO 12)
        #define OB_LED_RED_PIN           17  // 赤色LED  (GPIO 17)
        #define OB_LED_GREEN_PIN         16  // 緑色LED  (GPIO 16)
        #define OB_LED_PIN               25  // 青色LED  (GPIO 25)
        #define BUTTON_PIN               27  // ボタン (GPIO 27)
        // その他
        #define __SD_TF_ENABLE__
        #define __LCD_ENABLE__
        #define __BENCHMARK_TEST__
        #define __DEBUG_MONITOR_ENABLE__
    #endif /* __MCU_BOARD_XIAO_RP2040__ */
#endif /* MCU_RP2040 */

#ifdef MCU_RP2350
    #define __MCU_BOARD_PICO_2__
    #ifdef __MCU_BOARD_PICO_2__
        // GPIO
        #define OB_LED_PIN               25  // 基板の緑LED
        #define RGBLED_PIN               22  // Neopixel
        #define BUTTON_PIN               28  // ボタン
        // その他
        // #define __NEOPIXEL_ENABLE__
        // #define __BTN_ENABLE__
        #define __RTC_ENABLE__
        #define __SENSOR_ENABLE__
        #define __SD_TF_ENABLE__
        #define __LCD_ENABLE__
        #define __BENCHMARK_TEST__
        #define __DEBUG_MONITOR_ENABLE__
    #endif /* __MCU_BOARD_PICO_2__ */
#endif /* MCU_RP2350 */

typedef union {
    uint32_t DWORD;
    struct {
        uint32_t is_wdt:1;
        uint32_t is_i2c:1;
        uint32_t is_spi:1;
        uint32_t is_uart:1;
        uint32_t is_timer:1;
        uint32_t is_pio:1;
        uint32_t is_eeprom:1;
        uint32_t is_sd:1;
        uint32_t is_oled:1;
        uint32_t is_rtc:1;
        uint32_t is_sensor:1;
        uint32_t is_wifi:1;
        uint32_t is_bluetooth:1;
        uint32_t _Reserved_:19;
    }BIT;
} SYSINFO_BIT;

typedef struct
{
    SYSINFO_BIT u_sysbit;
} sysinfo_t;

void mcu_board_gpio_init(void);
void mcu_board_fs_init(void);
void mcu_board_get_system_info(sysinfo_t *p_sysinfo);
#endif /* MUC_BOARDHPP */