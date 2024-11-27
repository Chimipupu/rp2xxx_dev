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
#include "app_timer.hpp"
#include "app_util.hpp"
#include "app_filesystem.hpp"
#include "muc_board.hpp"
#include "benchmark_test.hpp"
#include "rp2xxx.hpp"

extern char g_ssid[16];
extern char g_password[32];

#define DEBUG_CMD
#ifdef DEBUG_CMD
#define DBG_CMD_ARG         4
#endif

#include "math_uc.hpp"
#define MAX_CMD_LEN         100
#define CALC_CMD_ARG        4

static void cpm_ansi_txt_color(const char *p_ansi_txt_color);
static void ascii_art(void);
static void help(void);
static void cls(void);
static void dir(void);
static void calculate(char *p_cmd);
static void timer_test(void);
#ifdef DEBUG_CMD
static void dbg_cmd(char *p_cmd);
#endif

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

    DEBUG_PRINTF("Command List:\n");
    DEBUG_PRINTF("  HELP   - This Command. Show Command List\n");
    DEBUG_PRINTF("  CLS    - Display Clear Command\n");
    DEBUG_PRINTF("  DIR    - List directory(SD or SPI Flash)\n");
    DEBUG_PRINTF("  CALC   - Calc add(+), sun(-), mul(*), div(*), mod(%), pow(^)\n");
    DEBUG_PRINTF("  PI     - Calculate Pi using Gauss-Legendre method (e.g., PI 3)\n");
    DEBUG_PRINTF("  FIB    - Display Fibonacci (e.g., FIB 10)\n");
    DEBUG_PRINTF("  PRIME  - Display prime numbers (e.g., PRIME 10)\n");
    DEBUG_PRINTF("  MANDEL - Display Mandelbrot (e.g., MANDEL)\n");
    DEBUG_PRINTF("  TIMER  - Timer Test\n");
    DEBUG_PRINTF("  TEST   - Performance test cmd\n");
#ifdef DEBUG_CMD
#if 0
    DEBUG_PRINTF("  REGR   - Register Read (e.g., REGR <Address>)\n");
    DEBUG_PRINTF("  REGW   - Register Write (e.g., REGW <Address> <Val>)\n");
#endif
    DEBUG_PRINTF("  DBG    - Develop cmd\n");
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
        DEBUG_PRINTF("Debug: num1 = %.2lf, op = %c, num2 = %.2lf\n", num1, op, num2);
        switch (op) {
            case '+':
                DEBUG_PRINTF("Result: %.2lf\n", num1 + num2);
                break;
            case '-':
                DEBUG_PRINTF("Result: %.2lf\n", num1 - num2);
                break;
            case '*':
                DEBUG_PRINTF("Result: %.2lf\n", num1 * num2);
                break;
            case '/':
                if (num2 != 0) {
                    DEBUG_PRINTF("Result: %.2lf\n", num1 / num2);
                } else {
                    DEBUG_PRINTF("Error: Division by zero!\n");
                }
                break;
            case '%':
                DEBUG_PRINTF("Result: %.0lf\n", fmod(num1, num2));
                break;
            case '^':
                DEBUG_PRINTF("Result: %.2lf\n", pow(num1, num2));
                break;
            default:
                DEBUG_PRINTF("Unknown op: %c\n", op);
                break;
        }
    }
    else
    {
        DEBUG_PRINTF("Invalid format. Use: CALC <num1> <op> <num2>\n");
    }
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

    DEBUG_PRINTF("proc time : %d usec\n", end_time - start_time);
}

#ifdef DEBUG_CMD
static void dbg_cmd(char *p_cmd)
{
    DEBUG_PRINTF("DEBUG Command\n");
    rp2xxx_reg_info();

    memset(&g_ssid[0], 0x00, sizeof(g_ssid));
    memset(&g_password[0], 0x00, sizeof(g_password));
    app_fs_wifi_config_read(&g_ssid[0], &g_password[0]);
}
#endif /* DEBUG_CMD */

void cpm_op_msg(void)
{
#ifdef MCU_RP2040
    DEBUG_PRINTF("Chimi Monitor Program for RP2040 Ver.1.0.0\n");
#else
    DEBUG_PRINTF("Chimi Monitor Program for RP2350 Ver.1.0.0\n");
#endif
    DEBUG_PRINTF("Copyright(C) 2024, Chimi(");
    cpm_ansi_txt_color(ANSI_TXT_COLOR_BLUE);
    DEBUG_PRINTF("https://github.com/Chimipupu");
    cpm_ansi_txt_color(ANSI_TXT_COLOR_GREEN);
    DEBUG_PRINTF(")\n");
}

void cpm_main(void)
{
    char command[MAX_CMD_LEN];
    uint32_t idx = 0;

    cls();
    cpm_op_msg();
    rp2xxx_develop_info_print();
    ascii_art();
    cpm_ansi_txt_color(ANSI_TXT_COLOR_GREEN);
    help();
    // cpm_ansi_txt_color(ANSI_TXT_COLOR_WHITE);

    while (1)
    {
        DEBUG_PRINTF("\n> ");
        idx = 0;

        while (true)
        {
            if (Serial.available()) {
                // cpm_ansi_txt_color(ANSI_TXT_COLOR_GREEN);
                char ch = Serial.read();
                ch = app_util_eng_to_upper_case(ch);
                if (ch == '\n') { // エンターキーが押された
                    command[idx] = '\0'; // 文字列の終端
                    break; // 入力完了
                }
                else if (idx < MAX_CMD_LEN - 1) { // バッファオーバーフローを防ぐ
                    command[idx++] = ch; // 文字をコマンドに追加
                }
            }
            WDT_TOGGLE;
        }

        if (strcmp(command, "HELP") == 0) {
            cpm_op_msg();
            rp2xxx_develop_info_print();
            help();
        } else if (strcmp(command, "CLS") == 0) {
            cls();
        } else if (strcmp(command, "DIR") == 0) {
            dir();
        } else if (strstr(command, "CALC") == command) {
            char *p_cmd = command + CALC_CMD_ARG;
            while (*p_cmd == ' '){
                p_cmd++;
                WDT_TOGGLE;
            }
            // DEBUG_PRINTF("Debug: Expression = '%s'\n", p_cmd);
            calculate(p_cmd);
        } else if (strstr(command, "FIB") == command) {
            int n = atoi(command + 4);
            math_uc_fibonacci(n);
        } else if (strstr(command, "PRIME") == command) {
            int n = atoi(command + 6);
            math_uc_prime(n);
        } else if (strstr(command, "PI") == command) {
            uint32_t num = atoi(command + 3);
            math_uc_calc_pi(num);
        } else if (strcmp(command, "MANDEL") == 0) {
            cls();
            math_uc_mandelbrot();
        } else if (strcmp(command, "TIMER") == 0) {
            timer_test();
        } else if (strcmp(command, "TEST") == 0) {
#ifdef __BENCHMARK_TEST__
            benchmark_test();
#endif /* __BENCHMARK_TEST__ */
            math_uc_math_test();
        }
#ifdef DEBUG_CMD
        else if (strstr(command, "DBG") == command)
        {
            char *p_cmd = command + DBG_CMD_ARG;
            while (*p_cmd == ' ')
            {
                p_cmd++;
                WDT_TOGGLE;
            }
            // DEBUG_PRINTF("Debug: Expression = '%s'\n", p_cmd);
            dbg_cmd(p_cmd);
        }
#endif
        else {
            DEBUG_PRINTF("Bad command: %s\n", command);
        }
        WDT_TOGGLE;
    }

    DEBUG_PRINTF("rebooting ...\n");
    while (1)
    {
        // WDTが泣くのを待つ
        NOP;
    }
}