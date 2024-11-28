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
#include <DS3232RTC.h>
const char *p_weekday_str[] = {"Non", "San", "Mon",
                                "Tue", "Wed", "Thu",
                                "Fri", "Sat" };
static DS3232RTC s_ds3231_rtc;
static tmElements_t s_tm;
#endif /* __RTC_ENABLE__ */

tmElements_t app_rtc_read(void)
{
#ifdef __RTC_ENABLE__
    s_ds3231_rtc.read(s_tm);
    return s_tm;
#endif /* __RTC_ENABLE__ */
}

void app_rtc_write(tmElements_t *p_tm)
{
#ifdef __RTC_ENABLE__
    setTime(p_tm->Hour, p_tm->Minute, p_tm->Second,
            p_tm->Day, p_tm->Month, p_tm->Year);
    s_ds3231_rtc.set(now());
#endif /* __RTC_ENABLE__ */
}

void app_rtc_init(void)
{
#ifdef __RTC_ENABLE__
    s_ds3231_rtc.begin();
#endif /* __RTC_ENABLE__ */
}

void app_rtc_date_print(void)
{
#ifdef __RTC_ENABLE__
    s_tm = app_rtc_read();

    DEBUG_RTOS_PRINTF("%d/%02d/%02d %02d:%02d:%02d %s\n", s_tm.Year + 1970,
                                                        s_tm.Month,
                                                        s_tm.Day,
                                                        s_tm.Hour,
                                                        s_tm.Minute,
                                                        s_tm.Second,
                                                        p_weekday_str[s_tm.Wday]);
#endif /* __RTC_ENABLE__ */
}