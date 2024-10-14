/**
 * @file dev.ino
 * @author Chimipupu
 * @brief YD-RP2040の評価プログラム
 * @version 0.1
 * @date 2024-10-07
 * 
 * @copyright Copyright (c) 2024
 * 
 */

// C/C++ Std Lib
#include <stdio.h>
#include <stdint.h>
#include <string.h>

// SDK, IDE Lib
#include <Arduino.h>

// My App
#include "common.hpp"
#include "app_main_core0.hpp"
#include "app_main_core1.hpp"

void core0_init(void)
{
    app_main_init_core0();
}

void core1_init(void)
{
    app_main_init_core1();
}

void core0_main(void)
{
    app_main_core0();
}

void core1_main(void)
{
    app_main_core1();
}