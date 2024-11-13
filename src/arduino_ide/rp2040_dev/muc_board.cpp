/**
 * @file muc_board.hpp
 * @author ちみ/Chimi(https://github.com/Chimipupu)）
 * @brief マイコン基板 アプリ実装
 * @version 0.1
 * @date 2024-11-13
 * 
 * @copyright Copyright (c) 2024 ちみ/Chimi(https://github.com/Chimipupu)）
 * 
 */

#include "muc_board.hpp"

#include <SPI.h>
#include <SD.h>

static void gpio_init(void);
static void spi_init(void);
static void sd_spi_init(void);

static void gpio_init(void)
{
#ifdef __MCU_BOARD_XIAO_RP2040__
    GPIO_PORT_DIR(OB_LED_RED_PIN, OUTPUT);
    GPIO_PORT_DIR(OB_LED_GREEN_PIN, OUTPUT);
    GPIO_PORT_DIR(OB_LED_PIN, OUTPUT);
    GPIO_PORT_DIR(BUZZUER_PIN, OUTPUT);
#else
    NOP;
#endif /* __MCU_BOARD_XIAO_RP2040__ */
}

static void spi_init(void)
{
    SPI.setRX(SPI_MISO_PIN);
    SPI.setSCK(SPI_SCK_PIN);
    SPI.setTX(SPI_MOSI_PIN);
}

static void sd_spi_init(void)
{
    if (!SD.begin(SPI_CS_PIN)) {
        DEBUG_PRINTF_RTOS("No SD Card. Plz, Insert SD & Reboot\n");
        while (1)
        {
            NOP;
        }
    }

    DEBUG_PRINTF_RTOS("File System Init(@SD)\n");
}

void mcu_board_init(void)
{
    gpio_init();
#if defined(__MCU_EX_BOARD_PICO_VGA__) || defined(__MCU_EX_XIAO_EXPANSION__)
    spi_init();
    sd_spi_init();
#else
    NOP
#endif /* __MCU_EX_BOARD_PICO_VGA__ */
}