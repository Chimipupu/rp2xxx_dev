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

// 文字の色を変更するのANSIエスケープシーケンス
#define ANSI_TXT_COLOR_WHITE    "\033[0m"
#define ANSI_TXT_COLOR_RED      "\033[31m"
#define ANSI_TXT_COLOR_GREEN    "\033[32m"
#define ANSI_TXT_COLOR_YELLOW   "\033[33m"
#define ANSI_TXT_COLOR_BLUE     "\033[34m"
#define ANSI_TXT_COLOR_PURPLE   "\033[35m"

#ifdef __cplusplus
extern "C" {
#endif
void cpm_main(void);
#ifdef __cplusplus
}
#endif

#endif /* CPM_HPP */