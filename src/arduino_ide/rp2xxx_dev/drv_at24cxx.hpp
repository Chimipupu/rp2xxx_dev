/**
 * @file drv_at24cxx.hpp
 * @author ちみ/Chimi(https://github.com/Chimipupu)
 * @brief EEPROM AT24Cxx ドライバ ヘッダー
 * @version 0.1
 * @date 2024-12-06
 * 
 * @copyright Copyright (c) 2024 ちみ/Chimi(https://github.com/Chimipupu)
 * 
 */

#ifndef DRV_AT24CXX_HPP
#define DRV_AT24CXX_HPP

#ifdef __EEPROM_ENABLE__
#include "common.hpp"
#define I2C_AT24C32_SLAVE_ADDR     0x57 // AT24C32のI2Cスレーブアドレス
#define EEPROM_SIZE                4096 // AT24C32のEEPROMサイズ = 32kbit = 4096Byte
#define COL_SIZE                   16

uint8_t drv_at24cxx_read(uint16_t addr);
void drv_at24cxx_write(uint16_t addr, uint8_t data);
#endif /* __EEPROM_ENABLE__ */
#endif /* DRV_AT24CXX_HPP */