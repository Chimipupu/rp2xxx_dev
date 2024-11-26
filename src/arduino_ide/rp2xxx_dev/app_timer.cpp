/**
 * @file app_timer.cpp
 * @author ちみ/Chimi(https://github.com/Chimipupu)
 * @brief RP2040 タイマーアプリ
 * @version 0.1
 * @date 2024-11-05
 * 
 * @copyright Copyright (c) 2024 ちみ/Chimi(https://github.com/Chimipupu)
 * 
 */

#include "app_timer.hpp"
#include "app_neopixel.hpp"
#include "muc_board.hpp"

static repeating_timer s_rs_timer_0;
static repeating_timer s_rs_timer_1;
static repeating_timer s_rs_timer_2;
static repeating_timer s_rs_timer_3;

/**
 * @brief タイマーアラーム0割込み ISR
 * 
 * @param p_rt 未使用
 * @return true アラーム継続
 * @return false アラーム停止
 */
bool TIMER_ALARM_0_ISR(repeating_timer_t *p_rt)
{
    // TODO:タイマーアラーム0割込みの処理実装
    NOP;
    return true;
}

/**
 * @brief タイマーアラーム1割込み ISR
 * 
 * @param p_rt 未使用
 * @return true アラーム継続
 * @return false アラーム停止
 */
bool TIMER_ALARM_1_ISR(repeating_timer_t *p_rt)
{
#ifdef __MCU_BOARD_XIAO_RP2040__
    app_led_fade(OB_LED_RED_PIN);
    app_led_fade(OB_LED_GREEN_PIN);
    app_led_fade(OB_LED_PIN);
#else
    app_led_fade(OB_LED_PIN);
#endif /* __MCU_BOARD_XIAO_RP2040__ */
    return true;
}

/**
 * @brief タイマーアラーム2割込み ISR
 * 
 * @param p_rt 未使用
 * @return true アラーム継続
 * @return false アラーム停止
 */
bool TIMER_ALARM_2_ISR(repeating_timer_t *p_rt)
{
    // app_neopixel_fade();
    return true;
}

/**
 * @brief タイマーアラーム3割込み ISR
 * 
 * @param p_rt 未使用
 * @return true アラーム継続
 * @return false アラーム停止
 */
bool TIMER_ALARM_3_ISR(repeating_timer_t *p_rt)
{
    // TODO:タイマーアラーム3割込みの処理実装
    NOP;
    return true;
}

/**
 * @brief 指定アラームをタイマーに設定
 * 
 * @param alarm_num アラーム番号(0～3)
 * @param time_ms 32bit設定アラームタイム（msec単位）
 */
void app_timer_set_alarm(uint8_t alarm_num, uint32_t time_ms)
{
    switch (alarm_num)
    {
        case 1:
            // 第一引数のマイナス ... コールバック関数の処理時間を含めない
            add_repeating_timer_ms(-time_ms, TIMER_ALARM_1_ISR, NULL, &s_rs_timer_0);
            break;

        case 2:
            add_repeating_timer_ms(-time_ms, TIMER_ALARM_2_ISR, NULL, &s_rs_timer_1);
            break;

        case 3:
            add_repeating_timer_ms(-time_ms, TIMER_ALARM_3_ISR, NULL, &s_rs_timer_2);
            break;

        case 0:
        default:
            add_repeating_timer_ms(-time_ms, TIMER_ALARM_0_ISR, NULL, &s_rs_timer_3);
            break;
    }
}

/**
 * @brief 指定アラームのタイマーカウントを取得
 * 
 * @return uint32_t 32bitタイマーカウント（usec単位）
 */
uint32_t app_get_time_us(void)
{
    return time_us_64();
}