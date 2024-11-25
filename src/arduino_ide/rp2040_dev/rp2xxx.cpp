/**
 * @file rp2xxx.cpp
 * @author ちみ/Chimi(https://github.com/Chimipupu)
 * @brief RP2040/RP2350関連 アプリ
 * @version 0.1
 * @date 2024-11-26
 * 
 * @copyright Copyright (c) 2024 ちみ/Chimi(https://github.com/Chimipupu)
 * 
 */

#include "rp2xxx.hpp"
#include "app_util.hpp"

#if defined(MCU_RP2040) && !defined(RP2350)
    const char *p_cpu_name_str = "M0PLUS";
#elif !defined(MCU_RP2040) && defined(RP2350)
    const char *p_cpu_name_str = "M33";
#endif

/**
 * @brief RP2040/RP2350のCPUのコア番号の取得
 * 
 * @return uint8_t 0=CPU0(コア0), 1=CPU1(コア1)
 */
uint8_t rp2xxx_get_cpu_core_num(void)
{
    uint8_t core_num = 0;
    uint32_t cpu_core = DRV_REG_READ_U32(SIO_CPUID_REG_ADDR);

    if(cpu_core != false) {
        core_num = 1;
    }

    return core_num;
}

/**
 * @brief RP2040/RP2350のチップRevisonの取得
 * 
 * @return uint8_t RP2040 ... B0/B1/B2, RP2350 ... A2
 */
uint8_t rp2xxx_read_reg_chip_rev(void)
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
 * @brief RP2040/RP2350のチップRevisonの表示
 * 
 */
void rp2xxx_chip_rev_print(void)
{
#if defined(MCU_RP2040) && !defined(RP2350)
    DEBUG_PRINTF("RP2040 Chip Rev.B%d\n", rp2xxx_read_reg_chip_rev());
#elif !defined(MCU_RP2040) && defined(RP2350)
    DEBUG_PRINTF("RP2350 Chip Rev.A%d\n", rp2xxx_read_reg_chip_rev());
#endif
}

/**
 * @brief RP2040のチップRevisonとPico SDKのバージョンの表示
 * 
 */
void rp2xxx_develop_info_print(void)
{
    DEBUG_PRINTF("Pico SDK Ver.%s\n", get_pico_sdk_version());
    rp2xxx_chip_rev_print();
}

/**
 * @brief コアレジスタを読み出し
 * 
 */
void rp2xxx_reg_info(void)
{
    uint32_t cpu_core = 0xFF;
    SYSINFO_CPUID SYSINFO_CPUID_REG; // Sysinfo CPUIDレジスタ
    SIO_CPUID SIO_CPUID_REG;         // SIO CPUIDレジスタ
    M0PLUS_CPUID M0PLUS_CPUID_REG;   // M0PLUS CPUIDレジスタ

    SIO_CPUID_REG.DWORD = (*(volatile uint32_t *)SIO_CPUID_REG_ADDR);
    SYSINFO_CPUID_REG.DWORD = (*(volatile uint32_t *)SYSINFO_CPUID_REG_ADDR);
    M0PLUS_CPUID_REG.DWORD = (*(volatile uint32_t *)M0PLUS_CPUID_REG_ADDR);
    cpu_core = SIO_CPUID_REG.DWORD;

    // RP2040/RP2350のチップRevison
    rp2xxx_chip_rev_print();

    // SIO CPUIDレジスタ(Core0 or Core1のチェック)
    DEBUG_PRINTF("[Core%X] ... SIO CPUID Reg(0x%02X)\n", cpu_core, SIO_CPUID_REG_ADDR);
    DEBUG_PRINTF("[Core%X] ... SIO CPUID Reg Val = 0x%08X\n", cpu_core, SIO_CPUID_REG.DWORD);

    // SYSINFO CPUIDレジスタ
    DEBUG_PRINTF("[Core%X] ... SYSINFO CPUID Reg(0x%02X)\n", cpu_core, SYSINFO_CPUID_REG);
    DEBUG_PRINTF("[Core%X] ... SYSINFO CPUID Reg Val = 0x%02X\n", cpu_core, SYSINFO_CPUID_REG.DWORD);
    DEBUG_PRINTF("[Core%X] ... SYSINFO CPUID Reg MANUFACTURER[11:0] = 0x%02X\n", cpu_core, SYSINFO_CPUID_REG.BIT.MANUFACTURER);
    DEBUG_PRINTF("[Core%X] ... SYSINFO CPUID Reg PART[27:12] = 0x%02X\n", cpu_core, SYSINFO_CPUID_REG.BIT.PART);
    DEBUG_PRINTF("[Core%X] ... SYSINFO CPUID Reg REVISION[31:28] = 0x%02X\n", cpu_core, SYSINFO_CPUID_REG.BIT.REVISION);

    // M0PLUS or M33 CPUIDレジスタ
    DEBUG_PRINTF("[Core%X] ... %s CPUID Reg(0x%02X)\n", p_cpu_name_str, cpu_core, M0PLUS_CPUID_REG_ADDR);
    DEBUG_PRINTF("[Core%X] ... %s CPUID Reg Val = 0x%02X\n", p_cpu_name_str, cpu_core, M0PLUS_CPUID_REG.DWORD);
    DEBUG_PRINTF("[Core%X] ... %s CPUID Reg REVISION[3:0] = 0x%02X\n", p_cpu_name_str, cpu_core, M0PLUS_CPUID_REG.BIT.REVISION);
    DEBUG_PRINTF("[Core%X] ... %s CPUID Reg PARTNO[15:4] = 0x%02X\n", p_cpu_name_str, cpu_core, M0PLUS_CPUID_REG.BIT.PARTNO);
    DEBUG_PRINTF("[Core%X] ... %s CPUID Reg ARCHITECTURE[19:16] = 0x%02X\n", p_cpu_name_str, cpu_core, M0PLUS_CPUID_REG.BIT.ARCHITECTURE);
    DEBUG_PRINTF("[Core%X] ... %s CPUID Reg VARIANT[23:20] = 0x%02X\n", p_cpu_name_str, cpu_core, M0PLUS_CPUID_REG.BIT.VARIANT);
    DEBUG_PRINTF("[Core%X] ... %s CPUID Reg IMPLEMENTER[31:24] = 0x%02X\n", p_cpu_name_str, cpu_core, M0PLUS_CPUID_REG.BIT.IMPLEMENTER);
}