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
        // DEBUG_PRINTF_RTOS("No SD Card. Plz, Insert SD & Reboot\n");
    }

    DEBUG_PRINTF_RTOS("File System Init(@SD)\n");
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
#if defined(__WDT_ENABLE__)
    DEBUG_RTOS_PRINTF("  WDT  [o]\n");
#endif

    // DEBUG_RTOS_PRINTF("  I2C [%c]\n", s_sysinfo.u_sysbit.BIT.is_i2c ? 'o' : 'x');
    // DEBUG_RTOS_PRINTF("  SPI [%c]\n", s_sysinfo.u_sysbit.BIT.is_spi ? 'o' : 'x');
    // DEBUG_RTOS_PRINTF("  UART [%c]\n", s_sysinfo.u_sysbit.BIT.is_uart ? 'o' : 'x');
    // DEBUG_RTOS_PRINTF("  Timer [%c]\n", s_sysinfo.u_sysbit.BIT.is_timer ? 'o' : 'x');
    // DEBUG_RTOS_PRINTF("  PIO [%c]\n", s_sysinfo.u_sysbit.BIT.is_pio ? 'o' : 'x');

#if defined(__SD_TF_ENABLE__)
    DEBUG_RTOS_PRINTF("  SD(@SPI) [o]\n");
#endif
#if defined(__EEPROM_ENABLE__)
    DEBUG_RTOS_PRINTF("  EEPROM(@I2C) [o]\n");
#endif
#if defined(__LCD_ENABLE__)
    DEBUG_RTOS_PRINTF("  OLED(@I2C) [o]\n");
#endif
#if defined(__RTC_ENABLE__)
    DEBUG_RTOS_PRINTF("  RTC(@I2C) [o]\n");
#endif
#if defined(__SENSOR_ENABLE__)
    DEBUG_RTOS_PRINTF("  Sensor(@I2C) [o]\n");
#endif
#if defined(__WIFI_ENABLE__)
    DEBUG_RTOS_PRINTF("  WiFi [o]\n");
#endif
#if defined(__BLUETOOTH_ENABLE__)
    DEBUG_RTOS_PRINTF("  Bluetooth [o]\n");
#endif

    p_sysinfo = &s_sysinfo;
}