/**
 * @file rp2350_reg.hpp
 * @author ちみ/Chimi(https://github.com/Chimipupu)
 * @brief RP2350レジスタ定義
 * @version 0.1
 * @date 2024-11-25
 * 
 * @copyright Copyright (c) 2024 ちみ/Chimi(https://github.com/Chimipupu)
 * 
 */
#ifndef RP2350_REG_H
#define RP2350_REG_H

#ifdef MCU_RP2350
    #include <stdint.h>

    #define SYSINFO_REG_BASE            0x40000000
    #define SYSINFO_CPUID_REG_OFFSET    0x00000000
    #define M33_REG_BASE                0xE0000000
    #define M33_REG_OFFSET              0x0000ED00
    #define SIO_REG_BASE                0xD0000000
    #define SIO_REG_OFFSET              0x00000000

    #define SYSINFO_CPUID_REG_ADDR      (SYSINFO_REG_BASE + SYSINFO_CPUID_REG_OFFSET)
    #define M33_CPUID_REG_ADDR          (M33_REG_BASE + M33_REG_OFFSET)
    #define SIO_CPUID_REG_ADDR          (SIO_REG_BASE + SIO_REG_OFFSET)

    typedef union {
        uint32_t DWORD;
        struct {
            uint32_t REVISION:4;        // bit[3:0]
            uint32_t PARTNO:12;         // bit[15:4]
            uint32_t ARCHITECTURE:4;    // bit[19:16]
            uint32_t VARIANT:4;         // bit[23:20]
            uint32_t IMPLEMENTER:8;     // bit[31:24]
        }BIT;
    } M33_CPUID;
    typedef union {
        uint32_t DWORD;
    } SIO_CPUID;

    typedef union {
        uint32_t DWORD;
        struct {
            uint32_t STOP_BIT:1;         // bit[0]
            uint32_t MANUFACTURER:11;    // bit[11:1]
            uint32_t PART:16;            // bit[27:12]
            uint32_t REVISION:4;         // bit[31:28]
        }BIT;
    } SYSINFO_CPUID;
#endif /* MCU_RP2350 */
#endif /* RP2350_REG_H */