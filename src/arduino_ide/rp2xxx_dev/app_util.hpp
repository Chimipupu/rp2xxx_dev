/**
 * @file app_util.hpp
 * @author ちみ/Chimi(https://github.com/Chimipupu)
 * @brief RP2040の評価プログラム用  アプリユーティリティ
 * @version 0.1
 * @date 2024-10-16
 * 
 * @copyright Copyright (c) 2024 ちみ/Chimi(https://github.com/Chimipupu)
 * 
 */

#ifndef DRV_UTIL_HPP
#define DRV_UTIL_HPP

#include "common.hpp"

#define SLAVE_FOUNED        0x00

/**
 * @brief レジスタ読み出し(32bit)
 * 
 * @param reg_addr レジスタアドレス(32bit)
 * @return uint32_t レジスタ値(32bit)
 */
static inline uint32_t DRV_REG_READ_U32(uint32_t reg_addr)
{
    return (*(volatile uint32_t *)reg_addr);
}

/**
 * @brief レジスタ書き込み(32bit)
 * 
 * @param reg_addr レジスタアドレス(32bit)
 * @param reg_val レジスタ値(32bit)
 */
static inline void DRV_REG_WRITE_U32(uint32_t reg_addr, uint32_t reg_val)
{
    (*(volatile uint32_t *)reg_addr) = reg_val;
}

char app_util_eng_to_upper_case(char c);
char app_util_eng_to_lower_case(char c);

#endif /* APP_UTIL_HPP */