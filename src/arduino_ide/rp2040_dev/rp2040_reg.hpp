/**
 * @file _reg.hpp
 * @author ちみ/Chimi（https://github.com/Chimipupu）
 * @brief レジスタ定義
 * @version 0.1
 * @date 2024-10-16
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef RP2040_REG_H
#define RP2040_REG_H

extern "C" {
#include <stdint.h>

#define M0PLUS_REG_BASE         0xE0000000
#define M0PLUS_REG_OFFSET       0x0000ED00

#define SIO_REG_BASE            0xD0000000
#define SIO_REG_OFFSET          0x00000000

#define M0PLUS_CPUID_REG_ADDR   (M0PLUS_REG_BASE + M0PLUS_REG_OFFSET)
#define SIO_CPUID_REG_ADDR      (SIO_REG_BASE + SIO_REG_OFFSET)

typedef union {
    uint32_t DWORD;
    struct {
        uint32_t REVISION:4;        // bit[3:0]
        uint32_t PARTNO:12;         // bit[15:4]
        uint32_t ARCHITECTURE:4;    // bit[19:16]
        uint32_t VARIANT:4;         // bit[23:20]
        uint32_t IMPLEMENTER:8;     // bit[31:24]
    }BIT;
} M0PLUS_CPUID;

// typedef union {
//     uint32_t DWORD;
// } SIO_CPUID;

} /* extern "C" */

#endif /* RP2040_REG_H */