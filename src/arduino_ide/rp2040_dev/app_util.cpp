/**
 * @file app_util.cpp
 * @author ちみ/Chimi（https://github.com/Chimipupu）
 * @brief RP2040の評価プログラム用  アプリユーティリティ
 * @version 0.1
 * @date 2024-10-16
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include "app_util.hpp"

/**
 * @brief コアレジスタを読み出し
 * 
 */
void app_util_system_reg_read(void)
{
    uint32_t cpu_core = 0xFF;
    M0PLUS_CPUID M0PLUS_CPUID_REG; // CPUIDレジスタ

    // どっちのコアかチェック(@SIO CPUID REG)
    cpu_core = DRV_REG_READ_U32(SIO_CPUID_REG_ADDR);
    DEBUG_PRINTF("[Core%X] ... SIO CPUID Reg(0x%02X)\n" ,cpu_core, SIO_CPUID_REG_ADDR);
    DEBUG_PRINTF("[Core%X] ... SIO CPUID Reg Val = 0x%08X\n" ,cpu_core, cpu_core);

    // M0PLUS CPUIDレジスタ値をUARTでprintf()
    M0PLUS_CPUID_REG.DWORD = (*(volatile uint32_t *)M0PLUS_CPUID_REG_ADDR);
    DEBUG_PRINTF("[Core%X] ... M0PLUS CPUID Reg(0x%02X)\n" ,cpu_core, M0PLUS_CPUID_REG_ADDR);
    DEBUG_PRINTF("[Core%X] ... M0PLUS CPUID Reg Val = 0x%02X\n" ,cpu_core, M0PLUS_CPUID_REG.DWORD);
    DEBUG_PRINTF("[Core%X] ... M0PLUS CPUID Reg IMPLEMENTER[31:24] = 0x%02X\n" ,cpu_core, M0PLUS_CPUID_REG.BIT.IMPLEMENTER);
    DEBUG_PRINTF("[Core%X] ... M0PLUS CPUID Reg VARIANT[23:20] = 0x%02X\n" ,cpu_core, M0PLUS_CPUID_REG.BIT.VARIANT);
    DEBUG_PRINTF("[Core%X] ... M0PLUS CPUID Reg ARCHITECTURE[19:16] = 0x%02X\n" ,cpu_core, M0PLUS_CPUID_REG.BIT.ARCHITECTURE);
    DEBUG_PRINTF("[Core%X] ... M0PLUS CPUID Reg PARTNO[15:4] = 0x%02X\n" ,cpu_core, M0PLUS_CPUID_REG.BIT.PARTNO);
    DEBUG_PRINTF("[Core%X] ... M0PLUS CPUID Reg REVISION[3:0] = 0x%02X\n" ,cpu_core, M0PLUS_CPUID_REG.BIT.REVISION);
}

# if 0
void app_util_i2c_scan(void)
{
    uint8_t res;
    uint8_t addr;
    uint8_t nDevices;
    uint8_t cnt;
    uint8_t addr_buf[128] = {0};
    uint8_t *p_buf;

    nDevices = 0;
    p_buf = &addr_buf[0];
    Serial.println("Scanning...");

    for(addr = 1; addr < 127; addr++ )
    {
        Wire1.beginTransmission(addr);
        res = Wire1.endTransmission();

        if (res == SLAVE_FOUNED)
        {
            *p_buf = addr;
            p_buf++;
            nDevices++;
        }else{
            // NOP
        }
    }

    if (nDevices == 0){
        Serial.println("No I2C Slave Found\n");
    }else{
        Serial.print("I2C Slave = ");
        Serial.print(nDevices);
        Serial.print("\n");

        for(cnt = 0; cnt < nDevices; cnt++)
        {
            Serial.print("0x");
            if (addr_buf[cnt] < 16)
            {
                Serial.print("0");
            }
            Serial.print(addr_buf[cnt],HEX);
            Serial.print(" ");
        }
        Serial.print("\n");
    }
}
#endif