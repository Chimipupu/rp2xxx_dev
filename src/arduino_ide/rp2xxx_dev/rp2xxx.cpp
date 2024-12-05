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

#ifdef MCU_RP2040
    const char *p_cpu_name_str = "M0PLUS";
#else
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
 * @brief 乱数生成
 * 
 * @return uint32_t 乱数
 */
uint32_t rp2xxx_get_hwrng(void)
{
    uint32_t rng_num = 0;

#if !defined(MCU_RP2040) && defined(MCU_RP2350)
    // （TRNG 真正乱数）RP2350はTRNGIからH/Wで生成
    // TODO: RP2350のTRNGで乱数の取得
#elif defined(MCU_RP2040) && !defined(MCU_RP2350)
    // （PRNG 擬似乱数）RP2040はarduino-picoのAPIから取得
    rng_num = rp2040.hwrand32();
#endif

    return rng_num;
}

/**
 * @brief RP2040/RP2350のチップRevisonの表示
 * 
 */
void rp2xxx_chip_rev_print(void)
{
#if defined(MCU_RP2040) && !defined(MCU_RP2350)
    DEBUG_RTOS_PRINTF("RP2040 Chip Rev.B%d\n", rp2xxx_read_reg_chip_rev());
#elif !defined(MCU_RP2040) && defined(MCU_RP2350)
    DEBUG_RTOS_PRINTF("RP2350 Chip Rev.A%d\n", rp2xxx_read_reg_chip_rev());
#endif
}

/**
 * @brief RP2040のチップRevisonとPico SDKのバージョンの表示
 * 
 */
void rp2xxx_develop_info_print(void)
{
    DEBUG_RTOS_PRINTF("Pico SDK Ver.%s\n", get_pico_sdk_version());
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

    SIO_CPUID_REG.DWORD = (*(volatile uint32_t *)SIO_CPUID_REG_ADDR);
    SYSINFO_CPUID_REG.DWORD = (*(volatile uint32_t *)SYSINFO_CPUID_REG_ADDR);
    cpu_core = SIO_CPUID_REG.DWORD;

    DEBUG_RTOS_PRINTF("**************************************************************************\n");
#ifdef MCU_RP2040
    DEBUG_RTOS_PRINTF("[Core%X] ... RP2040 Reg Info\n", cpu_core);
    M0PLUS_CPUID M0PLUS_CPUID_REG;   // M0PLUS CPUIDレジスタ
    M0PLUS_CPUID_REG.DWORD = (*(volatile uint32_t *)M0PLUS_CPUID_REG_ADDR);
#else
    DEBUG_RTOS_PRINTF("[Core%X] ... RP2350 Reg Info\n", cpu_core);
    M33_CPUID M33_CPUID_REG;   // M33 CPUIDレジスタ
    M33_CPUID_REG.DWORD = (*(volatile uint32_t *)M33_CPUID_REG_ADDR);
#endif
    DEBUG_RTOS_PRINTF("**************************************************************************\n");

    // SIO CPUIDレジスタ(Core0 or Core1のチェック)
    DEBUG_RTOS_PRINTF("[Core%X] ... SIO CPUID Reg(0x%02X)\n", cpu_core, SIO_CPUID_REG_ADDR);
    DEBUG_RTOS_PRINTF("[Core%X] ... SIO CPUID Reg Val = 0x%08X\n", cpu_core, SIO_CPUID_REG.DWORD);
    DEBUG_RTOS_PRINTF("--------------------------------------------------------------------------\n");

    // SYSINFO CPUIDレジスタ
    DEBUG_RTOS_PRINTF("[Core%X] ... SYSINFO CPUID Reg(0x%02X)\n", cpu_core, SYSINFO_CPUID_REG);
    DEBUG_RTOS_PRINTF("[Core%X] ... SYSINFO CPUID Reg Val = 0x%02X\n", cpu_core, SYSINFO_CPUID_REG.DWORD);
    DEBUG_RTOS_PRINTF("[Core%X] ... SYSINFO CPUID Reg MANUFACTURER[11:0] = 0x%02X\n", cpu_core, SYSINFO_CPUID_REG.BIT.MANUFACTURER);
    DEBUG_RTOS_PRINTF("[Core%X] ... SYSINFO CPUID Reg PART[27:12] = 0x%02X\n", cpu_core, SYSINFO_CPUID_REG.BIT.PART);
    DEBUG_RTOS_PRINTF("[Core%X] ... SYSINFO CPUID Reg REVISION[31:28] = 0x%02X\n", cpu_core, SYSINFO_CPUID_REG.BIT.REVISION);
    DEBUG_RTOS_PRINTF("--------------------------------------------------------------------------\n");
    rp2xxx_chip_rev_print(); // RP2040/RP2350のチップRevison

    // M0PLUS or M33 CPUIDレジスタ
#ifdef MCU_RP2040
    DEBUG_RTOS_PRINTF("[Core%X] ... %s CPUID Reg(0x%02X)\n", cpu_core, p_cpu_name_str, M0PLUS_CPUID_REG_ADDR);
    DEBUG_RTOS_PRINTF("[Core%X] ... %s CPUID Reg Val = 0x%02X\n", cpu_core, p_cpu_name_str, M0PLUS_CPUID_REG.DWORD);
    DEBUG_RTOS_PRINTF("[Core%X] ... %s CPUID Reg REVISION[3:0] = 0x%02X\n", cpu_core, p_cpu_name_str, M0PLUS_CPUID_REG.BIT.REVISION);
    DEBUG_RTOS_PRINTF("[Core%X] ... %s CPUID Reg PARTNO[15:4] = 0x%02X\n", cpu_core, p_cpu_name_str, M0PLUS_CPUID_REG.BIT.PARTNO);
    DEBUG_RTOS_PRINTF("[Core%X] ... %s CPUID Reg ARCHITECTURE[19:16] = 0x%02X\n", cpu_core, p_cpu_name_str, M0PLUS_CPUID_REG.BIT.ARCHITECTURE);
    DEBUG_RTOS_PRINTF("[Core%X] ... %s CPUID Reg VARIANT[23:20] = 0x%02X\n", cpu_core, p_cpu_name_str, M0PLUS_CPUID_REG.BIT.VARIANT);
    DEBUG_RTOS_PRINTF("[Core%X] ... %s CPUID Reg IMPLEMENTER[31:24] = 0x%02X\n", cpu_core, p_cpu_name_str, M0PLUS_CPUID_REG.BIT.IMPLEMENTER);
#else
    DEBUG_RTOS_PRINTF("[Core%X] ... %s CPUID Reg(0x%02X)\n", cpu_core, p_cpu_name_str, M33_CPUID_REG_ADDR);
    DEBUG_RTOS_PRINTF("[Core%X] ... %s CPUID Reg Val = 0x%02X\n", cpu_core, p_cpu_name_str, M33_CPUID_REG.DWORD);
    DEBUG_RTOS_PRINTF("[Core%X] ... %s CPUID Reg REVISION[3:0] = 0x%02X\n", cpu_core, p_cpu_name_str, M33_CPUID_REG.BIT.REVISION);
    DEBUG_RTOS_PRINTF("[Core%X] ... %s CPUID Reg PARTNO[15:4] = 0x%02X\n", cpu_core, p_cpu_name_str, M33_CPUID_REG.BIT.PARTNO);
    DEBUG_RTOS_PRINTF("[Core%X] ... %s CPUID Reg ARCHITECTURE[19:16] = 0x%02X\n", cpu_core, p_cpu_name_str, M33_CPUID_REG.BIT.ARCHITECTURE);
    DEBUG_RTOS_PRINTF("[Core%X] ... %s CPUID Reg VARIANT[23:20] = 0x%02X\n", cpu_core, p_cpu_name_str, M33_CPUID_REG.BIT.VARIANT);
    DEBUG_RTOS_PRINTF("[Core%X] ... %s CPUID Reg IMPLEMENTER[31:24] = 0x%02X\n", cpu_core, p_cpu_name_str, M33_CPUID_REG.BIT.IMPLEMENTER);
#endif
    DEBUG_RTOS_PRINTF("**************************************************************************\n");
}

/**
 * @brief U2Fのダウンロード待ちにリセット
 * 
 */
void rp2xxx_u2f_download_wait_reset(void)
{
    rp2040.rebootToBootloader();
}

/**
 * @brief S/Wリセット
 * 
 */
void rp2xxx_sw_reset(void)
{
    rp2040.reboot();
}