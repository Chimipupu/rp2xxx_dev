/**
 * @file muc_board.hpp
 * @author ちみ/Chimi(https://github.com/Chimipupu)
 * @brief マイコン基板 アプリ実装
 * @version 0.1
 * @date 2024-11-13
 * 
 * @copyright Copyright (c) 2024 ちみ/Chimi(https://github.com/Chimipupu)
 * 
 */

#include "muc_board.hpp"

#ifdef __SD_TF_ENABLE__
#include <SPI.h>
#include <SD.h>

static sysinfo_t s_sysinfo;

static void spi_init(void);
static void sd_spi_init(void);

static void spi_init(void)
{
    SPI.setRX(SPI_MISO_PIN);
    SPI.setSCK(SPI_SCK_PIN);
    SPI.setTX(SPI_MOSI_PIN);
}

static void sd_spi_init(void)
{
    if (!SD.begin(SPI_CS_PIN)) {
        DEBUG_RTOS_PRINTF("No SD Card. Plz, Insert SD & Reboot\n");
    }

    DEBUG_RTOS_PRINTF("File System Init(@SD)\n");
}

#endif /* __SD_TF_ENABLE__ */

void mcu_board_gpio_init(void)
{
#if defined(__MCU_BOARD_PICO__) || defined(__MCU_BOARD_PICO_2__)
    GPIO_PORT_DIR(OB_LED_PIN, OUTPUT);
    GPIO_OUTPUT(OB_LED_PIN, HIGH);
#endif

#ifdef __MCU_BOARD_XIAO_RP2040__
    GPIO_PORT_DIR(OB_LED_RED_PIN, OUTPUT);
    GPIO_PORT_DIR(OB_LED_GREEN_PIN, OUTPUT);
    // GPIO_PORT_DIR(BUZZUER_PIN, OUTPUT);
#endif /* __MCU_BOARD_XIAO_RP2040__ */
}

void mcu_board_fs_init(void)
{
#ifdef __SD_TF_ENABLE__
    spi_init();
    sd_spi_init();
#endif
}

void mcu_board_get_system_info(sysinfo_t *p_sysinfo)
{
    DEBUG_RTOS_PRINTF("  LED Pin [%d]\n", OB_LED_PIN);
    DEBUG_RTOS_PRINTF("  Neopixel Pin [%d]\n", RGBLED_PIN);
    DEBUG_RTOS_PRINTF("  Button Pin [%d]\n", BUTTON_PIN);

#if defined(__WDT_ENABLE__)
    DEBUG_RTOS_PRINTF("  WDT  [Enable]\n");
#endif

    // DEBUG_RTOS_PRINTF("  SPI 0/1 [0]\n");
    DEBUG_RTOS_PRINTF("  SPI CS Pin [%d]\n", SPI_CS_PIN);
    DEBUG_RTOS_PRINTF("  SPI SCK Pin [%d]\n", SPI_SCK_PIN);
    DEBUG_RTOS_PRINTF("  SPI MISO Pin [%d]\n", SPI_MISO_PIN);
    DEBUG_RTOS_PRINTF("  SPI MOSI Pin [%d]\n", SPI_MOSI_PIN);

    DEBUG_RTOS_PRINTF("  I2C 0 SDA Pin [%d]\n", I2C_SDA);
    DEBUG_RTOS_PRINTF("  I2C 0 SCL Pin [%d]\n", I2C_SCL);
    DEBUG_RTOS_PRINTF("  I2C 1 SDA Pin [%d]\n", I2C_1_SDA);
    DEBUG_RTOS_PRINTF("  I2C 1 SCL Pin [%d]\n", I2C_1_SCL);

    DEBUG_RTOS_PRINTF("  UART TX Pin [%d]\n", UART_TX_PIN);
    DEBUG_RTOS_PRINTF("  UART RX Pin [%d]\n", UART_RX_PIN);

#if defined(__SD_TF_ENABLE__)
    p_sysinfo = &s_sysinfo;
    DEBUG_RTOS_PRINTF("  SD(@SPI) [Enable]\n");
#else
    DEBUG_RTOS_PRINTF("  SD(@SPI) [x]\n");
#endif

#if defined(__EEPROM_ENABLE__)
    DEBUG_RTOS_PRINTF("  EEPROM(@I2C) [Enable]\n");
#endif

#if defined(__LCD_ENABLE__)
    DEBUG_RTOS_PRINTF("  OLED(@I2C) [Enable]\n");
#endif

#if defined(__RTC_ENABLE__)
    DEBUG_RTOS_PRINTF("  RTC(@I2C) [Enable]\n");
#endif

#if defined(__SENSOR_ENABLE__)
    DEBUG_RTOS_PRINTF("  Sensor(@I2C) [Enable]\n");
#endif

#if defined(__WIFI_ENABLE__)
    DEBUG_RTOS_PRINTF("  WiFi [Enable]\n");
#endif

#if defined(__BLUETOOTH_ENABLE__)
    DEBUG_RTOS_PRINTF("  Bluetooth [Enable]\n");
#endif
}