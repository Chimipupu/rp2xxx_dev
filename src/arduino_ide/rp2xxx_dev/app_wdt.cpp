/**
 * @file app_wdt.cpp
 * @author ちみ/Chimi(https://github.com/Chimipupu)
 * @brief 
 * @version 0.1
 * @date 2024-11-05
 * 
 * @copyright Copyright (c) 2024 ちみ/Chimi(https://github.com/Chimipupu)
 * 
 */

#include "app_wdt.hpp"
#include "rp2xxx.hpp"

void app_wdt_init(void)
{
#ifdef __WDT_ENABLE__
    if (watchdog_caused_reboot()) {
        rp2xxx_u2f_download_wait_reset();
    }

    watchdog_enable(WDT_TIME_OUT, true);
#endif /* __WDT_ENABLE__ */
}