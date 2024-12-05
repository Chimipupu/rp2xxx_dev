/**
 * @file rp2xxx.hpp
 * @author ちみ/Chimi(https://github.com/Chimipupu)
 * @brief RP2xxx(RP2040,RP2350)共通ヘッダー
 * @version 0.1
 * @date 2024-11-26
 * 
 * @copyright Copyright (c) 2024 ちみ/Chimi(https://github.com/Chimipupu)
 * 
 */

#ifndef RP2XXX_HPP
#define RP2XXX_HPP

// #define MCU_RP2040
#define MCU_RP2350

#if defined(MCU_RP2040) && !defined(MCU_RP2350)
    #include "rp2040_reg.hpp"
#elif !defined(MCU_RP2040) && defined(MCU_RP2350)
    #include "rp2350_reg.hpp"
#elif !defined(MCU_RP2040) && !defined(MCU_RP2350)
    #error "Plz,Define RP2040 or RP2350 in rpxxx.hpp!"
#else
    #error "Plz,Define either one (RP2040 or RP2350) in rpxxx.hpp!"
#endif

uint8_t rp2xxx_read_reg_chip_rev(void);
uint8_t rp2xxx_get_cpu_core_num(void);
const char* get_pico_sdk_version(void);
uint32_t rp2xxx_get_hwrng(void);
void rp2xxx_chip_rev_print(void);
void rp2xxx_develop_info_print(void);
void rp2xxx_reg_info(void);
void rp2xxx_u2f_download_wait_reset(void);
void rp2xxx_sw_reset(void);

#endif /* RP2XXX_HPP */