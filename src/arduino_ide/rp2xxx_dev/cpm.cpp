/**
 * @file cpm.cpp
 * @author ちみ/Chimi(https://github.com/Chimipupu)
 * @brief 評価モニタプログラム
 * @version 0.1
 * @date 2024-10-16
 * 
 * @copyright Copyright (c) 2024 ちみ/Chimi(https://github.com/Chimipupu)
 * 
 */

#include "cpm.hpp"

const char *p_cpm_version_str = "Ver1.0.3";

#ifdef MCU_RP2040
    const char *p_mcu_str = "RP2040";
#else
    const char *p_mcu_str = "RP2350";
#endif

#include "app_timer.hpp"
#include "app_util.hpp"
#include "app_filesystem.hpp"
#include "muc_board.hpp"
#include "benchmark_test.hpp"
#include "rp2xxx.hpp"

#ifdef __RTC_ENABLE__
#include "app_rtc.hpp"
#endif /* __RTC_ENABLE__ */

#ifdef __SENSOR_ENABLE__
#include "drv_bme280.hpp"
#endif /* __SENSOR_ENABLE__ */

#define DEBUG_CMD
#ifdef DEBUG_CMD
#define DBG_CMD_ARG         4
#endif

#include "math_uc.hpp"
#define MAX_CMD_LEN         100
#define CALC_CMD_ARG        4

#ifdef __WIFI_ENABLE__
extern char g_ssid[16];
extern char g_password[32];
#endif /* __WIFI_ENABLE__ */

static char s_cmd_buf[MAX_CMD_LEN] = {0};
static uint32_t s_idx = 0;

static void cpm_ansi_txt_color(const char *p_ansi_txt_color);
static void ascii_art(void);
static void help(void);
static void cls(void);
static void dir(void);
static void calculate(char *p_cmd);
static void rtc(void);
static void timer_test(void);
#ifdef DEBUG_CMD
static void dbg_cmd(char *p_cmd);
#endif
static void cmd_exec(char *p_cmd_buf, uint32_t idx);

static void cpm_ansi_txt_color(const char *p_ansi_txt_color)
{
    DEBUG_PRINTF_RTOS("%s", p_ansi_txt_color);
}

static void ascii_art(void)
{
    DEBUG_PRINTF_RTOS("   @                                     \n");
    DEBUG_PRINTF_RTOS("   @                                     \n");
    DEBUG_PRINTF_RTOS("@@@@@@@@     @@@@@        @@@@    @@@@@  \n");
    DEBUG_PRINTF_RTOS("   @             @       @    @  @     @ \n");
    DEBUG_PRINTF_RTOS("  @              @  @   @      @ @     @ \n");
    DEBUG_PRINTF_RTOS("  @ @@@         @   @   @      @  @@     \n");
    DEBUG_PRINTF_RTOS(" @@@   @     @@@@@@ @   @      @    @@   \n");
    DEBUG_PRINTF_RTOS(" @      @   @  @   @@@  @      @      @  \n");
    DEBUG_PRINTF_RTOS("        @  @  @     @ @ @      @ @     @ \n");
    DEBUG_PRINTF_RTOS("        @  @  @     @    @    @  @     @ \n");
    DEBUG_PRINTF_RTOS("      @@    @@     @      @@@@    @@@@@  \n");
    DEBUG_PRINTF_RTOS("   @@@           @@                      \n");
    DEBUG_PRINTF_RTOS("                                         \n");
}

static void help(void)
{
    cpm_ansi_txt_color(ANSI_TXT_COLOR_GREEN);

    DEBUG_RTOS_PRINTF("Command List:\n");
    DEBUG_RTOS_PRINTF("  HELP   - This Command. Show Command List\n");
    DEBUG_RTOS_PRINTF("  CLS    - Display Clear Command\n");
    DEBUG_RTOS_PRINTF("  DIR    - List directory(SD or SPI Flash)\n");
    DEBUG_RTOS_PRINTF("  CALC   - Calc add(+), sun(-), mul(*), div(*), mod(%), pow(^)\n");
    DEBUG_RTOS_PRINTF("  PI     - Calculate Pi using Gauss-Legendre method (e.g., PI 3)\n");
    DEBUG_RTOS_PRINTF("  FIB    - Display Fibonacci (e.g., FIB 10)\n");
    DEBUG_RTOS_PRINTF("  PRIME  - Display prime numbers (e.g., PRIME 10)\n");
    DEBUG_RTOS_PRINTF("  MANDEL - Display Mandelbrot (e.g., MANDEL)\n");
    DEBUG_RTOS_PRINTF("  RTC    - RTC Command\n");
    DEBUG_RTOS_PRINTF("  TIMER  - Timer Test\n");
    DEBUG_RTOS_PRINTF("  TEST   - Performance test cmd\n");
#ifdef DEBUG_CMD
#if 0
    DEBUG_RTOS_PRINTF("  REGR   - Register Read (e.g., REGR <Address>)\n");
    DEBUG_RTOS_PRINTF("  REGW   - Register Write (e.g., REGW <Address> <Val>)\n");
#endif
    DEBUG_RTOS_PRINTF("  DBG    - Develop cmd\n");
#endif

    // cpm_ansi_txt_color(ANSI_TXT_COLOR_WHITE);
}

static void cls(void)
{
    DEBUG_PRINTF_RTOS("\033[2J\033[H");
}

static void dir(void)
{
    app_fs_dir_print();
}

static void calculate(char *p_cmd)
{
    char op;
    double num1, num2;

    if (sscanf(p_cmd, "%lf %c %lf", &num1, &op, &num2) == 3) {
        DEBUG_RTOS_PRINTF("Debug: num1 = %.2lf, op = %c, num2 = %.2lf\n", num1, op, num2);
        switch (op) {
            case '+':
                DEBUG_RTOS_PRINTF("Result: %.2lf\n", num1 + num2);
                break;
            case '-':
                DEBUG_RTOS_PRINTF("Result: %.2lf\n", num1 - num2);
                break;
            case '*':
                DEBUG_RTOS_PRINTF("Result: %.2lf\n", num1 * num2);
                break;
            case '/':
                if (num2 != 0) {
                    DEBUG_RTOS_PRINTF("Result: %.2lf\n", num1 / num2);
                } else {
                    DEBUG_RTOS_PRINTF("Error: Division by zero!\n");
                }
                break;
            case '%':
                DEBUG_RTOS_PRINTF("Result: %.0lf\n", fmod(num1, num2));
                break;
            case '^':
                DEBUG_RTOS_PRINTF("Result: %.2lf\n", pow(num1, num2));
                break;
            default:
                DEBUG_RTOS_PRINTF("Unknown op: %c\n", op);
                break;
        }
    }
    else
    {
        DEBUG_RTOS_PRINTF("Invalid format. Use: CALC <num1> <op> <num2>\n");
    }
}

static void rtc(void)
{
#ifdef __RTC_ENABLE__
    if (xSemaphoreTake(xI2CMutex, portMAX_DELAY) == pdTRUE) {
        app_rtc_date_print();
        xSemaphoreGive(xI2CMutex);
    }
#endif /* __RTC_ENABLE__ */
}

static void timer_test(void)
{
    __DI();
    uint32_t start_time = time_us_32();

    // 2325000 = 処理時間 (RP2040:約97ms, RP2350:約92ms)
    for (uint32_t i = 0; i < 2325000; i++) {
        asm volatile("nop");
    }

    uint32_t end_time = time_us_32();
    __EI();

    DEBUG_RTOS_PRINTF("proc time : %d usec\n", end_time - start_time);
}

#ifdef DEBUG_CMD
static void dbg_cmd(char *p_cmd)
{
    DEBUG_RTOS_PRINTF("DEBUG Command\n");
    rp2xxx_reg_info();

    app_fs_test();

#ifdef __WIFI_ENABLE__
    memset(&g_ssid[0], 0x00, sizeof(g_ssid));
    memset(&g_password[0], 0x00, sizeof(g_password));
    app_fs_wifi_config_read(&g_ssid[0], &g_password[0]);
#endif /* __WIFI_ENABLE__ */

#ifdef __SENSOR_ENABLE__
    drv_bme280_data_print();
#endif /* __SENSOR_ENABLE__ */
}
#endif /* DEBUG_CMD */

static void init_msg(void)
{
    cpm_ansi_txt_color(ANSI_TXT_COLOR_GREEN);
    DEBUG_RTOS_PRINTF("**************************************************************************\n");
    cpm_op_msg();
    rp2xxx_develop_info_print();
    DEBUG_RTOS_PRINTF("**************************************************************************\n");
    ascii_art();
    DEBUG_RTOS_PRINTF("**************************************************************************\n");
    help();
    DEBUG_RTOS_PRINTF("**************************************************************************\n");
}

static void cmd_exec(char *p_cmd_buf, uint32_t idx)
{
    if (strcmp(p_cmd_buf, "HELP") == 0) {
        init_msg();
    } else if (strcmp(p_cmd_buf, "CLS") == 0) {
        cls();
    } else if (strcmp(p_cmd_buf, "DIR") == 0) {
        dir();
    } else if (strstr(p_cmd_buf, "CALC") == p_cmd_buf) {
        char *p_cmd = p_cmd_buf + CALC_CMD_ARG;
        while(*p_cmd == ' ') {
            p_cmd++;
        }
        // DEBUG_RTOS_PRINTF("Debug: Expression = '%s'\n", p_cmd);
        calculate(p_cmd);
    } else if (strstr(p_cmd_buf, "FIB") == p_cmd_buf) {
        uint32_t n = atoi(p_cmd_buf + 4);
        math_uc_fibonacci(n);
    } else if (strstr(p_cmd_buf, "PRIME") == p_cmd_buf) {
        uint32_t n = atoi(p_cmd_buf + 6);
        math_uc_prime(n);
    } else if (strstr(p_cmd_buf, "PI") == p_cmd_buf) {
        uint32_t num = atoi(p_cmd_buf + 3);
        math_uc_calc_pi(num);
    } else if (strcmp(p_cmd_buf, "MANDEL") == 0) {
        cls();
        math_uc_mandelbrot();
    } else if (strcmp(p_cmd_buf, "RTC") == 0) {
        rtc();
    } else if (strcmp(p_cmd_buf, "TIMER") == 0) {
        timer_test();
    } else if (strcmp(p_cmd_buf, "TEST") == 0) {
#ifdef __BENCHMARK_TEST__
        benchmark_test();
#endif /* __BENCHMARK_TEST__ */
        math_uc_math_test();
    }
#ifdef DEBUG_CMD
    else if (strstr(p_cmd_buf, "DBG") == p_cmd_buf)
    {
        char *p_cmd = p_cmd_buf + DBG_CMD_ARG;
        while (*p_cmd == ' ')
        {
            p_cmd++;
        }
        // DEBUG_RTOS_PRINTF("Debug: Expression = '%s'\n", p_cmd);
        dbg_cmd(p_cmd);
    }
#endif /* DEBUG_CMD */
    else {
        DEBUG_RTOS_PRINTF("Bad Command: %s\n", p_cmd_buf);
    }
}

void cpm_op_msg(void)
{
    cpm_ansi_txt_color(ANSI_TXT_COLOR_GREEN);
    DEBUG_RTOS_PRINTF("Chimi Monitor Program for %s ", p_mcu_str);
    cpm_ansi_txt_color(ANSI_TXT_COLOR_RED);
    DEBUG_RTOS_PRINTF("%s\n", p_cpm_version_str);
    cpm_ansi_txt_color(ANSI_TXT_COLOR_GREEN);
    DEBUG_RTOS_PRINTF("Copyright(C) 2024, Chimi(");
    cpm_ansi_txt_color(ANSI_TXT_COLOR_BLUE);
    DEBUG_RTOS_PRINTF("https://github.com/Chimipupu");
    cpm_ansi_txt_color(ANSI_TXT_COLOR_GREEN);
    DEBUG_RTOS_PRINTF(")\n");
}

void cpm_init(void)
{
    memset(&s_cmd_buf[0], 0x00, sizeof(s_cmd_buf));
    s_idx = 0;

    cls();
    init_msg();
    DEBUG_RTOS_PRINTF("\n> ");
}

void cpm_main(void)
{
    if (Serial.available()) {
        char val = Serial.read();
        val = app_util_eng_to_upper_case(val);

        if (val == '\n') {
            s_cmd_buf[s_idx] = '\0';
            cmd_exec(&s_cmd_buf[0], s_idx);
            DEBUG_RTOS_PRINTF("\n> ");
            memset(&s_cmd_buf[0], 0x00, sizeof(s_cmd_buf));
            s_idx = 0;
        } else if (s_idx < MAX_CMD_LEN - 1) {   // バッファオーバーフロー防止
            s_cmd_buf[s_idx] = val;
            s_idx++;
        }
    }
}