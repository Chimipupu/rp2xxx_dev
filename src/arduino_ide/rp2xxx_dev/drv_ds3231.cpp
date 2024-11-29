/**
 * @file drv_ds3231.cpp
 * @author ちみ/Chimi(https://github.com/Chimipupu)
 * @brief DS3231 RTCのドライバ
 * @version 0.1
 * @date 2024-11-29
 * 
 * @copyright Copyright (c) 2024 ちみ/Chimi(https://github.com/Chimipupu)
 * 
 */

#include "drv_ds3231.hpp"

static uint8_t dec_to_bcd(uint8_t val);
static uint8_t bcd_to_dec(uint8_t val);

static uint8_t bcd_to_dec(uint8_t val)
{
  return (val / 16 * 10) + (val % 16);
}

static uint8_t dec_to_bcd(uint8_t val)
{
  return (val / 10 * 16) + (val % 10);
}

void drv_ds3231_init(void)
{
    Wire1.begin(I2C_DS3231_SLAVE_ADDR);
}

void drv_ds3231_get_time_date(tm *p_tm)
{
    Wire1.beginTransmission(I2C_DS3231_SLAVE_ADDR);
    Wire1.write(0x00);
    Wire1.endTransmission();

    Wire1.requestFrom(I2C_DS3231_SLAVE_ADDR, 7);

    p_tm->tm_sec  = bcd_to_dec(Wire1.read());
    p_tm->tm_min  = bcd_to_dec(Wire1.read());
    p_tm->tm_hour = bcd_to_dec(Wire1.read());
    p_tm->tm_wday = bcd_to_dec(Wire1.read());
    p_tm->tm_mday = bcd_to_dec(Wire1.read());
    p_tm->tm_mon  = bcd_to_dec(Wire1.read() - 1);
    p_tm->tm_year = bcd_to_dec(Wire1.read() + 100);
}

void drv_ds3231_set_time_date(tm *p_tm)
{
    Wire1.beginTransmission(I2C_DS3231_SLAVE_ADDR);
    Wire1.write(0x00);
    Wire1.write(dec_to_bcd(p_tm->tm_sec));
    Wire1.write(dec_to_bcd(p_tm->tm_min));
    Wire1.write(dec_to_bcd(p_tm->tm_hour));
    Wire1.write(dec_to_bcd(p_tm->tm_wday));
    Wire1.write(dec_to_bcd(p_tm->tm_mday));
    Wire1.write(dec_to_bcd(p_tm->tm_mon + 1));
    Wire1.write(dec_to_bcd(p_tm->tm_year - 100));
    Wire1.endTransmission();
}