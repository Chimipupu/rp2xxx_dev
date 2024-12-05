/**
 * @file app_oled.hpp
 * @author ちみ/Chimi(https://github.com/Chimipupu)
 * @brief OLEDアプリ
 * @version 0.1
 * @date 2024-10-16
 * 
 * @copyright Copyright (c) 2024 ちみ/Chimi(https://github.com/Chimipupu)
 * 
 */

#ifndef APP_OLED_HPP
#define APP_OLED_HPP

#include "common.hpp"

#ifdef __LCD_ENABLE__
#define OLED_I2C_ADDR       0x3C
#define LGFX_AUTODETECT
// #define LGFX_USE_V1
#include <LovyanGFX.hpp>
#include <LGFX_AUTODETECT.hpp>

// #define LCD_SSD1306        // 0.96インチのOLED用
#define LCD_SH110x         // 1.3インチのOLED用(128x64)

#define I2C_NORMAL_FREQ     100000 // I2C @100KHz
#define I2C_FAST_FREQ       400000 // I2C Fast Mode @400KHz
// #define I2C_FREQ            I2C_NORMAL_FREQ
#define I2C_FREQ            I2C_FAST_FREQ

#define SCREEN_WIDTH        130 // 128だと左端1列にゴミが出る
#define SCREEN_HEIGHT       64
#define OLED_RESET          -1

#define OLED_BACK_COLOR     TFT_BLACK
#define OLED_TXT_COLOR      TFT_WHITE
#define OLED_TXT_SIZE       1

#ifdef LCD_SSD1306
class LGFX_SSD1306 : public lgfx::LGFX_Device
{
    lgfx::Panel_SSD1306   _panel_instance;
    lgfx::Bus_I2C         _bus_instance;

    public:
        LGFX_SSD1306()
        {
            {
                auto cfg = _bus_instance.config();
                cfg.i2c_port    = 1;                // 使用するI2C (0 or 1)
                cfg.freq_write  = I2C_FREQ;         // Write @100KHz or 400KHz
                cfg.freq_read   = I2C_FREQ;         // read  @100KHz or 400KHz
                cfg.pin_sda     = I2C_SDA;          // SDAピン
                cfg.pin_scl     = I2C_SCL;          // SCLピン
                cfg.i2c_addr    = OLED_I2C_ADDR;    // スレーブアドレス
                _bus_instance.config(cfg);
                _panel_instance.setBus(&_bus_instance);
            }

            {
                auto cfg = _panel_instance.config();
                // cfg.memory_width  = SCREEN_WIDTH;     // LCDのの幅
                // cfg.memory_height =  SCREEN_HEIGHT;   // LCDの高さ
                cfg.pin_cs           = -1;
                cfg.pin_rst          = -1;
                cfg.pin_busy         = -1;
                cfg.panel_width      = SCREEN_WIDTH;
                cfg.panel_height     = SCREEN_HEIGHT;
                cfg.offset_x         = 0;
                cfg.offset_y         = 0;
                cfg.offset_rotation  = 0;
                cfg.dummy_read_pixel = 8;
                cfg.dummy_read_bits  = 1;
                cfg.readable         = false;
                cfg.invert           = false;
                cfg.rgb_order        = false;
                cfg.dlen_16bit       = false;
                cfg.bus_shared       = false;
                _panel_instance.config(cfg);
            }
            setPanel(&_panel_instance);
        }
};
#endif /* LCD_SSD1306 */

#ifdef LCD_SH110x
class LGFX_SH110x : public lgfx::LGFX_Device
{
    lgfx::Panel_SH110x  _panel_instance;
    lgfx::Bus_I2C       _bus_instance;

    public:
        LGFX_SH110x()
        {
            {
                auto cfg = _bus_instance.config();
                cfg.i2c_port    = 1;                // 使用するI2C (0 or 1)
                cfg.freq_write  = I2C_FREQ;         // Write @100KHz or 400KHz
                cfg.freq_read   = I2C_FREQ;         // read  @100KHz or 400KHz
                cfg.pin_sda     = I2C_SDA;          // SDAピン
                cfg.pin_scl     = I2C_SCL;          // SCLピン
                cfg.i2c_addr    = OLED_I2C_ADDR;    // スレーブアドレス
                _bus_instance.config(cfg);
                _panel_instance.setBus(&_bus_instance);
            }

            {
                auto cfg = _panel_instance.config();
                // cfg.memory_width  = SCREEN_WIDTH;    // LCDのの幅
                // cfg.memory_height = SCREEN_HEIGHT;   // LCDの高さ
                cfg.pin_cs           = -1;
                cfg.pin_rst          = -1;
                cfg.pin_busy         = -1;
                cfg.panel_width      = SCREEN_WIDTH;
                cfg.panel_height     = SCREEN_HEIGHT;
                cfg.offset_x         = 0;
                cfg.offset_y         = 0;
                cfg.offset_rotation  = 0;
                cfg.dummy_read_pixel = 8;
                cfg.dummy_read_bits  = 1;
                cfg.readable         = false;
                cfg.invert           = false;
                cfg.rgb_order        = false;
                cfg.dlen_16bit       = false;
                cfg.bus_shared       = false;
                _panel_instance.config(cfg);
            }
            setPanel(&_panel_instance);
        }
};
#endif /* LCD_SH110x */

#include "app_rtc.hpp"
#include "app_sensor.hpp"
typedef struct {
    sensor_app_data_t sensor_dat;
    rtc_time_date_t rtc_dat;
} oled_app_data_t;

void app_oled_init(void);
void app_oled_test(void);
void app_oled_main(oled_app_data_t *p_oled_dat);
#endif /* __LCD_ENABLE__ */
#endif /* APP_OLED_HPP */