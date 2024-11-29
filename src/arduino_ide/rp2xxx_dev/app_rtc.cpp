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

const char *p_weekday_str[] = {"Sun.", "Mon.", "Tue.", "Wed.", "Thu.", "Fri.", "Sat." };

static tm s_tm;
#endif /* __RTC_ENABLE__ */

tm app_rtc_read(void)
{
#ifdef __RTC_ENABLE__
    drv_ds3231_get_time_date(&s_tm);
    return s_tm;
#endif /* __RTC_ENABLE__ */
}

void app_rtc_write(tm *p_tm)
{
#ifdef __RTC_ENABLE__
    drv_ds3231_set_time_date(p_tm);
#endif /* __RTC_ENABLE__ */
}

void app_rtc_init(void)
{
    drv_ds3231_init();
}

void app_rtc_date_print(void)
{
#ifdef __RTC_ENABLE__
    s_tm = app_rtc_read();
    DEBUG_RTOS_PRINTF("%d/%02d/%02d %02d:%02d:%02d %s\n",
                    s_tm.tm_year + 2000,
                    s_tm.tm_mon,
                    s_tm.tm_mday,
                    s_tm.tm_hour,
                    s_tm.tm_min,
                    s_tm.tm_sec,
                    p_weekday_str[s_tm.tm_wday]);
#endif /* __RTC_ENABLE__ */
}