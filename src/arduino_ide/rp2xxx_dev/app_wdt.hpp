/**
 * @file app_wdt.hpp
 * @author ちみ/Chimi(https://github.com/Chimipupu)
 * @brief WDT ヘッダー
 * @version 0.1
 * @date 2024-11-05
 * 
 * @copyright Copyright (c) 2024 ちみ/Chimi(https://github.com/Chimipupu)
 * 
 */

#ifndef APP_WDT_HPP
#define APP_WDT_HPP

#include "common.hpp"
#include "hardware/watchdog.h"

// #define WDT_TIME_OUT        6 * 1000 // WDTを6秒に設定
#define WDT_TIME_OUT        0x7fffff // WDTを8.3秒に設定(8.3秒 = 0x7fffff)

static inline void WDT_TOGGLE(void)
{
#ifdef __WDT_ENABLE__
    watchdog_update();
#else
    asm volatile("nop");
#endif /* __WDT_ENABLE__ */
}


void app_wdt_init(void);

#endif /* APP_WDT_HPP */