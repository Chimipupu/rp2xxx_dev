/**
 * @file rp2040_reg.cpp
 * @author ちみ/Chimi(https://github.com/Chimipupu)
 * @brief RP2040 レジスタ関連アプリ
 * @version 0.1
 * @date 2024-10-16
 * 
 * @copyright Copyright (c) 2024 ちみ/Chimi(https://github.com/Chimipupu)
 * 
 */

#include "rp2040_reg.hpp"
#include "app_util.hpp"

/**
 * @brief CPUのコア番号の取得
 * 
 * @return uint8_t 0=CPU0(コア0), 1=CPU1(コア1)
 */
uint8_t rp2040_get_cpu_core_num(void)
{
    uint8_t core_num = 0;

    uint32_t cpu_core = DRV_REG_READ_U32(SIO_CPUID_REG_ADDR);

    if(cpu_core != false) {
        core_num = 1;
    }

    return core_num;
}

/**
 * @brief RP2040のチップRevisonの取得
 * 
 * @return uint8_t Revsion.B0/B1/B2(0/1/2)
 */
uint8_t rp2040_read_reg_chip_rev(void)
{
    uint8_t chip_rev = 0;

    SYSINFO_CPUID SYSINFO_CPUID_REG;
    SYSINFO_CPUID_REG.DWORD = (*(volatile uint32_t *)SYSINFO_CPUID_REG_ADDR);
    chip_rev = SYSINFO_CPUID_REG.BIT.REVISION;

    return chip_rev;
}

/**
 * @brief Pico SDKのバージョン取得関数
 * 
 * @return const char* Pico SDKのバージョン
 */
const char* get_pico_sdk_version(void)
{
    return PICO_SDK_VERSION_STRING;
}

/**
 * @brief RP2040のチップRevisonとPico SDKのバージョンの表示
 * 
 */
void rp2040_develop_info_print(void)
{
    DEBUG_PRINTF("Pico SDK Ver.%s\n", get_pico_sdk_version());
    DEBUG_PRINTF("RP2040 Chip Rev.B%d\n", rp2040_read_reg_chip_rev());
}

/**
 * @brief コアレジスタを読み出し
 * 
 */
void rp2040_reg_info(void)
{
    uint32_t cpu_core = 0xFF;
    SYSINFO_CPUID SYSINFO_CPUID_REG; // Sysinfo CPUIDレジスタ
    SIO_CPUID SIO_CPUID_REG;         // SIO CPUIDレジスタ
    M0PLUS_CPUID M0PLUS_CPUID_REG;   // M0PLUS CPUIDレジスタ

    SIO_CPUID_REG.DWORD = (*(volatile uint32_t *)SIO_CPUID_REG_ADDR);
    SYSINFO_CPUID_REG.DWORD = (*(volatile uint32_t *)SYSINFO_CPUID_REG_ADDR);
    M0PLUS_CPUID_REG.DWORD = (*(volatile uint32_t *)M0PLUS_CPUID_REG_ADDR);
    cpu_core = SIO_CPUID_REG.DWORD;

    // RP2040のチップRev(B0 or B1 or B2)
    DEBUG_PRINTF("[Core%X] ... RP2040 Chip Rev.B%d\n", cpu_core, SYSINFO_CPUID_REG.BIT.REVISION);

    // SIO CPUIDレジスタ(Core0 or Core1のチェック)
    DEBUG_PRINTF("[Core%X] ... SIO CPUID Reg(0x%02X)\n", cpu_core, SIO_CPUID_REG_ADDR);
    DEBUG_PRINTF("[Core%X] ... SIO CPUID Reg Val = 0x%08X\n", cpu_core, SIO_CPUID_REG.DWORD);

    // SYSINFO CPUIDレジスタ
    DEBUG_PRINTF("[Core%X] ... SYSINFO CPUID Reg(0x%02X)\n", cpu_core, SYSINFO_CPUID_REG);
    DEBUG_PRINTF("[Core%X] ... SYSINFO CPUID Reg Val = 0x%02X\n", cpu_core, SYSINFO_CPUID_REG.DWORD);
    DEBUG_PRINTF("[Core%X] ... SYSINFO CPUID Reg MANUFACTURER[11:0] = 0x%02X\n", cpu_core, SYSINFO_CPUID_REG.BIT.MANUFACTURER);
    DEBUG_PRINTF("[Core%X] ... SYSINFO CPUID Reg PART[27:12] = 0x%02X\n", cpu_core, SYSINFO_CPUID_REG.BIT.PART);
    DEBUG_PRINTF("[Core%X] ... SYSINFO CPUID Reg REVISION[31:28] = 0x%02X\n", cpu_core, SYSINFO_CPUID_REG.BIT.REVISION);

    // M0PLUS CPUIDレジスタ
    DEBUG_PRINTF("[Core%X] ... M0PLUS CPUID Reg(0x%02X)\n", cpu_core, M0PLUS_CPUID_REG_ADDR);
    DEBUG_PRINTF("[Core%X] ... M0PLUS CPUID Reg Val = 0x%02X\n", cpu_core, M0PLUS_CPUID_REG.DWORD);
    DEBUG_PRINTF("[Core%X] ... M0PLUS CPUID Reg REVISION[3:0] = 0x%02X\n", cpu_core, M0PLUS_CPUID_REG.BIT.REVISION);
    DEBUG_PRINTF("[Core%X] ... M0PLUS CPUID Reg PARTNO[15:4] = 0x%02X\n", cpu_core, M0PLUS_CPUID_REG.BIT.PARTNO);
    DEBUG_PRINTF("[Core%X] ... M0PLUS CPUID Reg ARCHITECTURE[19:16] = 0x%02X\n", cpu_core, M0PLUS_CPUID_REG.BIT.ARCHITECTURE);
    DEBUG_PRINTF("[Core%X] ... M0PLUS CPUID Reg VARIANT[23:20] = 0x%02X\n", cpu_core, M0PLUS_CPUID_REG.BIT.VARIANT);
    DEBUG_PRINTF("[Core%X] ... M0PLUS CPUID Reg IMPLEMENTER[31:24] = 0x%02X\n", cpu_core, M0PLUS_CPUID_REG.BIT.IMPLEMENTER);
}