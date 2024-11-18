/**
 * @file app_util.cpp
 * @author ちみ/Chimi(https://github.com/Chimipupu)
 * @brief RP2040の評価プログラム用  アプリユーティリティ
 * @version 0.1
 * @date 2024-10-16
 * 
 * @copyright Copyright (c) 2024 ちみ/Chimi(https://github.com/Chimipupu)
 * 
 */

#include "app_util.hpp"

/**
 * @brief 英語の小文字を大文字に変換
 * 
 * @param c 入力文字
 * @return char 変換or無変換した文字
 */
char app_util_eng_to_upper_case(char c)
{
    if (c >= 'a' && c <= 'z') {
        return c - ('a' - 'A');
    }

    return c;
}