/**
 * @file cpm.hpp
 * @author ちみ/Chimi(https://github.com/Chimipupu)
 * @brief 評価モニタプログラム
 * @version 0.1
 * @date 2024-10-16
 * 
 * @copyright Copyright (c) 2024 ちみ/Chimi(https://github.com/Chimipupu)
 * 
 */
#ifndef CPM_HPP
#define CPM_HPP

#include "common.hpp"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

// ANSIエスケープシーケンス(文字の色)
#define ANSI_TXT_COLOR_RESET    "\e[0m"
#define ANSI_TXT_COLOR_WHITE    "\e[37sm"
#define ANSI_TXT_COLOR_RED      "\e[31m"
#define ANSI_TXT_COLOR_GREEN    "\e[32m"
#define ANSI_TXT_COLOR_YELLOW   "\e[33m"
#define ANSI_TXT_COLOR_BLUE     "\e[34m"
#define ANSI_TXT_COLOR_PURPLE   "\e[35m"
#define ANSI_TXT_COLOR_MAGENTA  "\e[36m"

void cpm_op_msg(void);
void cpm_init(void);
void cpm_main(void);

#endif /* CPM_HPP */