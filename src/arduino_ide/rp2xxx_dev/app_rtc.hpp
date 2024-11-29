/**
 * @file app_rtc.hpp
 * @author ちみ/Chimi(https://github.com/Chimipupu)
 * @brief RTC アプリヘッダー
 * @version 0.1
 * @date 2024-11-29
 * 
 * @copyright Copyright (c) 2024 ちみ/Chimi(https://github.com/Chimipupu)
 * 
 */

#ifndef APP_RTC_HPP
#define APP_RTC_HPP

#include "common.hpp"
#include <Time.h>

void app_rtc_init(void);
tm app_rtc_read(void);
void app_rtc_write(tm *p_tm);
void app_rtc_date_print(void);

#endif /* APP_RTC_HPP */