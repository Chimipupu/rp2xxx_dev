/**
 * @file app_oled.cpp
 * @author ちみ/Chimi(https://github.com/Chimipupu)
 * @brief OLEDアプリ
 * @version 0.1
 * @date 2024-10-16
 * 
 * @copyright Copyright (c) 2024 ちみ/Chimi(https://github.com/Chimipupu)
 * 
 */

#include "app_oled.hpp"

#ifdef __LCD_ENABLE__
#include "math_uc.hpp"
#include <Wire.h>

#define MATH_PI_CALC_TIME   3
#define FIBONACCI_N         8

#define OLED_ENG_TEST       0
#define OLED_JPN_TEST       1
#define OLED_MATH_TEST      2

typedef enum
{
    ROTATION_A = 0, // USB (未調査)
    ROTATION_B,     // USB (未調査)
    ROTATION_C,     // USB 左
    ROTATION_D,     // USB 左 画面反転
} E_LCD_ROATATION;

#ifdef MCU_RP2040
    #ifdef __MCU_BOARD_PICO__
        const char *p_board_str = "Raspberry Pi Pico";
    #endif /* __MCU_BOARD_PICO__ */
#else
    #ifdef __MCU_BOARD_PICO_2__
        const char *p_board_str = "Raspberry Pi Pico 2";
    #endif /* __MCU_BOARD_PICO_2__ */
#endif

#if defined(LCD_SSD1306) && !defined(LCD_SH110x)
static LGFX_SSD1306 lcd;   // 0.96インチのOLED用
#elif !defined(LCD_SSD1306) && defined(LCD_SH110x)
static LGFX_SH110x lcd;    // 1.3インチのOLED用
#elif !defined(LCD_SSD1306) && !defined(LCD_SH110x)
static LGFX lcd;
#endif

static LGFX_Sprite sprite(&lcd);
static uint8_t s_type = OLED_ENG_TEST;

static void oled_i2c_init(void);
static void gfx_init(void);
void oled_clear(void);
static void oled_en_txt_test(void);
static void oled_jp_txt_test(void);
static void oled_math_txt_test(void);

static void oled_i2c_init(void)
{
    GPIO_PORT_DIR(I2C_SDA, INPUT_PULLUP);
    GPIO_PORT_DIR(I2C_SCL, INPUT_PULLUP);
    Wire1.setSDA(I2C_SDA);
    Wire1.setSCL(I2C_SCL);
    Wire1.begin();
}

static void gfx_init(void)
{
    lcd.init();
    lcd.setRotation(ROTATION_C);
    lcd.fillScreen(TFT_BLACK);
    // sprite.setColorDepth(8);
    // sprite.setTextWrap(false);  // 改行をしない
    sprite.setTextSize(OLED_TXT_SIZE);
    sprite.createSprite(lcd.width(), lcd.height());
}

void oled_clear(void)
{
    sprite.fillScreen(OLED_BACK_COLOR);
    sprite.setTextColor(OLED_TXT_COLOR);
    sprite.setCursor(0, 0);
    sprite.pushSprite(0, 0);
}

void app_oled_init(void)
{
    oled_i2c_init();
    gfx_init();
}

static void oled_en_txt_test(void)
{
    oled_clear();
    sprite.setFont(&fonts::Font0);
#ifdef MCU_RP2040
    sprite.printf("RP2040 F/W Test\n");
    sprite.printf("by Chimi\n");
    sprite.printf("github.com/Chimipupu\n");
    sprite.printf("%s\n", p_board_str);
    sprite.printf("2Core ARM CPU @133MHz\n");
    sprite.printf("ARM Cortex-M0+\n");
    sprite.printf("Flash:2MB SRAM:264KB\n");
#else
    sprite.printf("RP2350 F/W Test\n");
    sprite.printf("by Chimi\n");
    sprite.printf("github.com/Chimipupu\n");
    sprite.printf("%s\n", p_board_str);
    sprite.printf("2Core ARM CPU @133MHz\n");
    sprite.printf("ARM Cortex-M33\n");
    sprite.printf("Flash:4MB SRAM:520KB\n");
#endif
    sprite.printf("pi=%.15f\n", MATH_PI);
    sprite.pushSprite(0, 0);
}

static void oled_jp_txt_test(void)
{
    oled_clear();

    // 日本語は12pxが下限
    // sprite.setFont(&fonts::lgfxJapanGothic_12); // ゴシック体 12px
    sprite.setFont(&fonts::efontJA_12);
    sprite.printf("ちみさん電子工作すき\n");
    sprite.printf("あいうえおかきくけこ\n");
    sprite.printf("アイウエオカキクケコ\n");
    sprite.printf("らずべりーぱい ぴこ\n");
    sprite.printf("ラズベリーパイ ピコ\n");
    sprite.pushSprite(0, 0);
}

static void oled_math_txt_test(void)
{
    uint32_t i, cnt;
    volatile double c;
    volatile double pi;
    volatile double phi;
    volatile double napier;
    volatile uint32_t a_fib[FIBONACCI_N] = {0};
    volatile double result;

    oled_clear();
    sprite.setFont(&fonts::Font0);
#ifdef MCU_RP2040
    sprite.printf("RP2040 F/W Test\n");
#else
    sprite.printf("RP2350 F/W Test\n");
#endif

    // tan(355/226)の計算（※期待値:-7497258.185...）
    result = math_calc_accuracy();
    sprite.printf("tan(355/226)\n");
    sprite.printf("=%.6f\n", result);

    // 円周率π
    for(i=1; i<=MATH_PI_CALC_TIME; i++)
    {
        pi = math_pi_calc(i);
    }
    sprite.printf("pi=%.15f\n", pi);
    sprite.printf("2pi=%.15f\n", pi * 2);

    // ネイピアe
    napier = math_napier_calc();
    sprite.printf("e=%.15f\n", napier);

    // 黄金比φ
    phi = math_goldenratio_calc();
    sprite.printf("phi=%.15f\n", phi);

    // フィボナッチ数列
    sprite.printf("Fn=");
    for(i = 1; i <= FIBONACCI_N; i++)
    {
        a_fib[i-1] = math_fibonacci_calc(i);
        sprite.print(a_fib[i-1]);
        sprite.print(" ");
    }
    sprite.pushSprite(0, 0);
}

/**
 * @brief OLED LCDの表示テスト
 * 
 */
void app_oled_test(void)
{
    switch(s_type)
    {
        // 英数字 表示テスト
        case OLED_ENG_TEST:
            oled_en_txt_test();
            break;

        // 日本語 表示テスト
        case OLED_JPN_TEST:
            oled_jp_txt_test();
            break;

        // 計算結果表示テスト
        case OLED_MATH_TEST:
            oled_math_txt_test();
            break;

        default:
            break;
    }

    s_type++;
    if(s_type > OLED_MATH_TEST){
        s_type = OLED_ENG_TEST;
    }
}

/**
 * @brief OLED LCDメイン関数
 * 
 */
void app_oled_main(oled_app_data_t *p_oled_dat)
{
    sprite.setCursor(0, 0);
    sprite.fillScreen(OLED_BACK_COLOR);
    sprite.printf("[System Data Info]\n");

    // 時刻データ
    sprite.printf("%4d/%2d/%2d ",
                    p_oled_dat->rtc_dat.year + 2000,
                    p_oled_dat->rtc_dat.mon,
                    p_oled_dat->rtc_dat.mday);
    sprite.printf("%2d:%2d:%2d\n",
                    p_oled_dat->rtc_dat.hour,
                    p_oled_dat->rtc_dat.min,
                    p_oled_dat->rtc_dat.sec);

    // センサデータ（湿度、温度、気圧）
    sprite.printf("temp=%.2fC\n", p_oled_dat->sensor_dat.bme280_dat.temperature);
    sprite.printf("humi=%.2f%%\n", p_oled_dat->sensor_dat.bme280_dat.humidity);
    sprite.printf("press=%.2fhPa\n", p_oled_dat->sensor_dat.bme280_dat.pressure);
    sprite.printf("alti=%.2fm\n", p_oled_dat->sensor_dat.bme280_dat.altitude);

    sprite.pushSprite(0, 0);
}
#endif /* __LCD_ENABLE__ */