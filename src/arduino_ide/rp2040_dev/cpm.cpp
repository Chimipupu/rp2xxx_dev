/**
 * @file cpm.cpp
 * @author ちみ/Chimi（https://github.com/Chimipupu）
 * @brief 評価モニタプログラム
 * @version 0.1
 * @date 2024-10-16
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include "cpm.hpp"
#include "app_timer.hpp"
#include "app_util.hpp"
#include "app_filesystem.hpp"
#include "muc_board.hpp"

extern char g_ssid[16];
extern char g_password[32];

#define DEBUG_CMD
#ifdef DEBUG_CMD
#define DBG_CMD_ARG         4
#endif

#include "math_uc.hpp"
#define MATH_PI_CALC_TIME   3
#define FIBONACCI_N         20
#define INVSQRT_N           7

#define MAX_CMD_LEN         100
#define CALC_CMD_ARG        4
#define WIDTH               80
#define HEIGHT              40
#define MAX_ITER            1000

static void math_test(void);

void help()
{
    DEBUG_PRINTF("Command List:\n");
    DEBUG_PRINTF("  HELP   - This Command. Show Command List\n");
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
}

void dir()
{
    DEBUG_PRINTF("Directory listing:\n");
    DEBUG_PRINTF("File1.txt\nFile2.txt\nFile3.txt\n");
}

void calculate(char *p_cmd)
{
    char op;
    double num1, num2;

    if (sscanf(p_cmd, "%lf %c %lf", &num1, &op, &num2) == 3)
    {
        DEBUG_PRINTF("Debug: num1 = %.2lf, op = %c, num2 = %.2lf\n", num1, op, num2);
        switch (op)
        {
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
            if (num2 != 0)
            {
                DEBUG_PRINTF("Result: %.2lf\n", num1 / num2);
            }
            else
            {
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

void fibonacci(uint32_t n)
{
    uint32_t i,fib;

    DEBUG_PRINTF("Fibonacci : ");
    for(uint8_t i = 1; i < n; i++)
    {
        fib = math_fibonacci_calc(i);
        DEBUG_PRINTF("%d ", fib);
    }
    DEBUG_PRINTF("\n");
}

void prime(uint32_t n)
{
    DEBUG_PRINTF("Prime Numbers: ");
    uint32_t count = 0;
    for (int i = 2; count < n; i++)
    {
        if (math_is_prime_num(i))
        {
            DEBUG_PRINTF("%d ", i);
            count++;
        }
    }
    DEBUG_PRINTF("\n");
}

void calculatePi(uint32_t n)
{
    // ガウス・ルジャンドル法で円周率を計算
    __DI();
    uint32_t start_time = time_us_32();
    double pi = math_pi_calc(n);
    uint32_t end_time = time_us_32();
    __EI();
    DEBUG_PRINTF("pi = %.15f\n", pi);
    DEBUG_PRINTF("proc time : %d usec\n", end_time - start_time);
}

void mandelbrot()
{
    DEBUG_PRINTF("Mandelbrot Set:\n");

    for (int y = 0; y < HEIGHT; y++)
    {
        for (int x = 0; x < WIDTH; x++)
        {
            double c_re = (x - WIDTH / 2.0) * 4.0 / WIDTH;   // xのスケーリング
            double c_im = (y - HEIGHT / 2.0) * 4.0 / HEIGHT; // yのスケーリング
            double z_re = c_re, z_im = c_im;
            int iteration;

            for (iteration = 0; iteration < MAX_ITER; iteration++)
            {
                if (z_re * z_re + z_im * z_im > 4.0)
                    break; // 発散判定

                double z_re_new = z_re * z_re - z_im * z_im + c_re;
                z_im = 2.0 * z_re * z_im + c_im;
                z_re = z_re_new;
            }

            char symbol = (iteration == MAX_ITER) ? '#' : ' ';
            DEBUG_PRINTF("%c", symbol);
        }
        DEBUG_PRINTF("\n");
    }
}

static void math_test(void)
{
    uint32_t i,fib;
    volatile double pi;
    volatile double phi;
    volatile double napier;
    volatile double invsqrt;
    volatile double result;

    // tan(355/226)の計算（※期待値:-7497258.185...）
    __DI();
    uint32_t start_time = time_us_32();
    result = math_calc_accuracy();
    uint32_t end_time = time_us_32();
    __EI();
    DEBUG_PRINTF("tan(355/226) = %.3f\n", result);
    DEBUG_PRINTF("proc time : %d usec\n", end_time - start_time);

    // 円周率π
    calculatePi(MATH_PI_CALC_TIME);

    // ネイピアe
    napier = math_napier_calc();
    DEBUG_PRINTF("e = %.15f\n", napier);

    // 黄金比φ
    __DI();
    start_time = time_us_32();
    phi = math_goldenratio_calc();
    end_time = time_us_32();
    __EI();
    DEBUG_PRINTF("phi = %.15f\n", phi);

    // フィボナッチ数列
    fibonacci(FIBONACCI_N);

    // 高速逆平方根
    for(i = 1; i < INVSQRT_N; i++)
    {
        invsqrt = math_fast_inv_sqrt(i);
        DEBUG_PRINTF("%d's inv sqrt = %.15f\n", i, invsqrt);
    }
}

void timer_test(void)
{
    __DI();
    uint32_t start_time = time_us_32();

    for (uint32_t i = 0; i < 2325000; i++) {
        asm volatile("nop");
    }

    uint32_t end_time = time_us_32();
    __EI();

    // 処理時間 約97.38ms
    DEBUG_PRINTF("proc time : %d usec\n", end_time - start_time);
}

#ifdef DEBUG_CMD
void dbg_cmd(char *p_cmd)
{
    DEBUG_PRINTF("DEBUG Command\n");
    app_util_system_reg_read();

    // FileSystem Test
    app_fs_test();
    memset(&g_ssid[0], 0x00, sizeof(g_ssid));
    memset(&g_password[0], 0x00, sizeof(g_password));
    app_fs_wifi_config_read(&g_ssid[0], &g_password[0]);
}
#endif

void cpm_op_msg(void)
{
    DEBUG_PRINTF("RP2040 Monitor Program Ver1.0.0\n");
    DEBUG_PRINTF("Copyright(C) 2024, Chimi（https://github.com/Chimipupu）\n");
}

void cpm_main(void)
{
    char command[MAX_CMD_LEN];
    uint32_t idx = 0;

    while (!Serial) {
        WDT_TOGGLE;
    }

    cpm_op_msg();
    help();

    while (1)
    {
        DEBUG_PRINTF("\n> ");

        idx = 0; // 入力インデックスの初期化

        while (true)
        {
            if (Serial.available())
            {
                char ch = Serial.read();

                if (ch == '\n') // エンターキーが押された
                {
                    command[idx] = '\0'; // 文字列の終端
                    break; // 入力完了
                }
                else if (idx < MAX_CMD_LEN - 1) // バッファオーバーフローを防ぐ
                {
                    command[idx++] = ch; // 文字をコマンドに追加
                }
            }
            WDT_TOGGLE;
        }

        // コマンドの処理
        if (strcmp(command, "HELP") == 0)
        {
            help();
        }
        else if (strcmp(command, "DIR") == 0)
        {
            dir();
        }
        else if (strstr(command, "CALC") == command)
        {
            char *p_cmd = command + CALC_CMD_ARG;
            while (*p_cmd == ' '){
                p_cmd++;
                WDT_TOGGLE;
            }
            // DEBUG_PRINTF("Debug: Expression = '%s'\n", p_cmd);
            calculate(p_cmd);
        }
        else if (strstr(command, "FIB") == command)
        {
            int n = atoi(command + 4);
            fibonacci(n);
        }
        else if (strstr(command, "PRIME") == command)
        {
            int n = atoi(command + 6);
            prime(n);
        }
        else if (strstr(command, "PI") == command)
        {
            uint32_t num = atoi(command + 3);
            calculatePi(num);
        }
        else if (strcmp(command, "MANDEL") == 0)
        {
            mandelbrot();
        }
        else if (strcmp(command, "TIMER") == 0)
        {
            timer_test();
        }
        else if (strcmp(command, "TEST") == 0)
        {
            math_test();
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
        else
        {
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