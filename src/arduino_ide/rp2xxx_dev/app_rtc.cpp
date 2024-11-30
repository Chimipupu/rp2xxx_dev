/**
 * @file app_rtc.cpp
 * @author ちみ/Chimi(https://github.com/Chimipupu)
 * @brief RTC アプリ
 * @version 0.1
 * @date 2024-11-29
 * 
 * @copyright Copyright (c) 2024 ちみ/Chimi(https://github.com/Chimipupu)
 * 
 */

#include "app_rtc.hpp"

#ifdef __RTC_ENABLE__
#include "drv_ds3231.hpp"

const char weekday_buf[7][5] = {"Sun.", "Mon.", "Tue.", "Wed.", "Thu.", "Fri.", "Sat."};

static rtc_time_date_t s_tm;
static void rtc_date_print(rtc_time_date_t *p_tm);

static void rtc_date_print(rtc_time_date_t *p_tm)
{
    DEBUG_RTOS_PRINTF("%d/%02d/%02d %02d:%02d:%02d %s\n",
                    p_tm->year + 2000,
                    p_tm->mon,
                    p_tm->mday,
                    p_tm->hour,
                    p_tm->min,
                    p_tm->sec,
                    weekday_buf[p_tm->wday - 1]);
}
#endif /* __RTC_ENABLE__ */

rtc_time_date_t app_rtc_read(void)
{
#ifdef __RTC_ENABLE__
    drv_ds3231_get_time_date(&s_tm);
    return s_tm;
#endif /* __RTC_ENABLE__ */
}

void app_rtc_write(rtc_time_date_t *p_tm)
{
#ifdef __RTC_ENABLE__
    drv_ds3231_set_time_date(p_tm);
#endif /* __RTC_ENABLE__ */
}

void app_rtc_init(void)
{
    drv_ds3231_init();
}

void app_rtc_date_print(rtc_time_date_t *p_tm)
{
#ifdef __RTC_ENABLE__
    rtc_date_print(p_tm);
#endif /* __RTC_ENABLE__ */
}

void app_rtc_read_date_print(void)
{
#ifdef __RTC_ENABLE__
    s_tm = app_rtc_read();
    rtc_date_print(&s_tm);
#endif /* __RTC_ENABLE__ */
}