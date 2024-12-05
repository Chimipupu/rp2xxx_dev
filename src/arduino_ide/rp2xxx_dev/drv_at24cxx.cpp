/**
 * @file drv_at24cxx.cpp
 * @author ちみ/Chimi(https://github.com/Chimipupu)
 * @brief EEPROM AT24Cxx ドライバ
 * @version 0.1
 * @date 2024-12-06
 * 
 * @copyright Copyright (c) 2024 ちみ/Chimi(https://github.com/Chimipupu)
 * 
 */

#include "drv_at24cxx.hpp"
#include <Wire.h>

uint8_t drv_at24cxx_read(uint16_t addr)
{
    Wire.beginTransmission(I2C_AT24C32_SLAVE_ADDR);
    Wire.write((uint8_t)(addr >> 8));   // アドレス上位
    Wire.write((uint8_t)(addr & 0xFF)); // アドレス下位
    Wire.endTransmission();
    Wire.requestFrom(I2C_AT24C32_SLAVE_ADDR, 1);

    if (Wire.available()) {
        return Wire.read();
    }else{
        return 0;
    }
}

void drv_at24cxx_write(uint16_t addr, uint8_t data)
{
    Wire.beginTransmission(I2C_AT24C32_SLAVE_ADDR);
    Wire.write((uint8_t)(addr >> 8));   // アドレス上位
    Wire.write((uint8_t)(addr & 0xFF)); // アドレス下位
    Wire.write(data);
    Wire.endTransmission();
}