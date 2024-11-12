/**
 * @file muc_board.hpp
 * @author ちみ/Chimi（https://github.com/Chimipupu）
 * @brief マイコン基板 アプリ実装
 * @version 0.1
 * @date 2024-11-13
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include "muc_board.hpp"

#include <SPI.h>
#include <SD.h>

static void spi_init(void);
static void sd_spi_init(void);

// SPI @10MHz, MSBファースト,モード0
// SPISettings spisettings(1000000, MSBFIRST, SPI_MODE0);

static void spi_init(void)
{
#ifdef __MCU_EX_BOARD_PICO_VGA__
    SPI.setRX(SPI_MISO_PIN);
    // SPI.setCS(SPI_CS_PIN);
    SPI.setSCK(SPI_SCK_PIN);
    SPI.setTX(SPI_MOSI_PIN);
    // SPI.begin(true);
    // pinMode(SPI_CS_PIN, OUTPUT);
    // digitalWrite(SPI_CS_PIN, HIGH);
#else
    SPI.setRX(SPI_MISO_PIN);
    SPI.setSCK(SPI_SCK_PIN);
    SPI.setTX(SPI_MOSI_PIN);
#endif /* __MCU_EX_BOARD_PICO_VGA__ */
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
    spi_init();
    sd_spi_init();
}