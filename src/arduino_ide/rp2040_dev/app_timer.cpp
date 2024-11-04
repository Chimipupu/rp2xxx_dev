/**
 * @file app_timer.hpp
 * @author your name (you@domain.com)
 * @brief RP2040 タイマーアプリ
 * @version 0.1
 * @date 2024-11-05
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include "common.hpp"

static struct repeating_timer s_repeating_timer_t;

/**
 * @brief タイマーアラーム0割込み ISR
 * 
 * @param p_rt 未使用
 * @return true アラーム継続
 * @return false アラーム停止
 */
bool TIMER_ALARM_0_ISR(repeating_timer_t *p_rt)
{
    // DEBUG_PRINTF("alarm 0 ISR\n");
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
    // DEBUG_PRINTF("alarm 0 ISR\n");
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
    // DEBUG_PRINTF("alarm 0 ISR\n");
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
    // DEBUG_PRINTF("alarm 0 ISR\n");
    return true;
}

/**
 * @brief 指定アラームをタイマーに設定
 * 
 * @param alarm_num アラーム番号(0～3)
 * @param time_us 32bit設定アラームタイム（usec単位）
 */
void app_timer_set_alarm(uint8_t alarm_num, uint32_t time_us)
{
    switch (alarm_num)
    {
        case 1:
            // 第一引数のマイナス ... コールバック関数の処理時間を含めない
            add_repeating_timer_us(-time_us, TIMER_ALARM_1_ISR, NULL, &s_repeating_timer_t);
            break;

        case 2:
            add_repeating_timer_us(-time_us, TIMER_ALARM_2_ISR, NULL, &s_repeating_timer_t);
            break;

        case 3:
            add_repeating_timer_us(-time_us, TIMER_ALARM_3_ISR, NULL, &s_repeating_timer_t);
            break;

        case 0:
        default:
            add_repeating_timer_us(-time_us, TIMER_ALARM_0_ISR, NULL, &s_repeating_timer_t);
            break;
    }
}

/**
 * @brief 指定アラームのタイマーカウントを取得
 * 
 * @return uint32_t 32bitタイマーカウント（usec単位）
 */
uint32_t app_timer_get_time(void)
{
    return time_us_64();
}