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

void drv_ds3231_get_time_date(rtc_time_date_t *p_tm)
{
    Wire1.beginTransmission(I2C_DS3231_SLAVE_ADDR);
    Wire1.write(0x00);
    Wire1.endTransmission();

    Wire1.requestFrom(I2C_DS3231_SLAVE_ADDR, 7);

    p_tm->sec  = bcd_to_dec(Wire1.read() & 0x7F);
    p_tm->min  = bcd_to_dec(Wire1.read() & 0x7F);
    p_tm->hour = bcd_to_dec(Wire1.read() & 0x3F);
    p_tm->wday = bcd_to_dec(Wire1.read() & 0x07);
    p_tm->mday = bcd_to_dec(Wire1.read() & 0x3F);
    p_tm->mon  = bcd_to_dec(Wire1.read() & 0x1F);
    p_tm->year = bcd_to_dec(Wire1.read() & 0xFF);
}

void drv_ds3231_set_time_date(rtc_time_date_t *p_tm)
{
    Wire1.beginTransmission(I2C_DS3231_SLAVE_ADDR);
    Wire1.write(0x00);
    Wire1.write(dec_to_bcd(p_tm->sec)  & 0x7F);
    Wire1.write(dec_to_bcd(p_tm->min)  & 0x7F);
    Wire1.write(dec_to_bcd(p_tm->hour) & 0x3F);
    Wire1.write(dec_to_bcd(p_tm->wday) & 0x07);
    Wire1.write(dec_to_bcd(p_tm->mday) & 0x3F);
    Wire1.write(dec_to_bcd(p_tm->mon)  & 0x1F);
    Wire1.write(dec_to_bcd(p_tm->year) & 0xFF);
    Wire1.endTransmission();
}