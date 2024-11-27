/**
 * @file math_uc.cpp
 * @author ちみ/Chimi(https://github.com/Chimipupu)
 * @brief 数学計算アプリ
 * @version 0.1
 * @date 2024-10-16
 * 
 * @copyright Copyright (c) 2024 ちみ/Chimi(https://github.com/Chimipupu)
 * 
 */

#include "math_uc.hpp"
#include "common.hpp"

#define MATH_PI_CALC_TIME   3
#define FIBONACCI_N         20
#define INVSQRT_N           7
#define WIDTH               80
#define HEIGHT              40
#define MAX_ITER            1000

// 計算精度の表示（期待値:-7497258.185...）
double math_calc_accuracy(void)
{
    double angle_a;
    double angle_b;
    double radians;
    double result;

    angle_a = 355.f * MATH_PI / 180;
    angle_b = 226.f * MATH_PI / 180;
    radians = angle_a / angle_b;
    result = tan(radians);

    return result;
}

// エラトステネスのふるいで素数を判定
bool math_is_prime_num(uint32_t n)
{
    uint32_t i;

    if (n <= 1) {
        return false;
    }

    for(i = 2; i * i <= n; ++i)
    {
        if (n % i == 0) {
            return false;
        }
    }

    return true;
}

// ピタゴラスの定理(c = sqrt(a^2 + b^2))
double math_pythagoras(double a, double b)
{
    double c = UNKNOWN_VAL;

    c = sqrt((double)(a * a) + (double)(b * b));

    return c;
}

// ガウス・ルジャンドル法による円周率の計算
double math_pi_calc(uint32_t cnt)
{
    double a = 1.0;
    double b = 1.0 / sqrt(2);
    double t = 1.0 / 4.0;
    double p = 1.0;

    for (uint32_t i = 0; i < cnt; i++)
    {
        double an = (a + b) / 2.0;
        double bn = sqrt(a * b);
        double tn = t - p * pow(a - an, 2);
        double pn = 2.0 * p;

        a = an;
        b = bn;
        t = tn;
        p = pn;
    }

    double pi = pow(a + b, 2) / (4.0 * t);
    return pi;
}

// フィボナッチ数列の計算
uint32_t math_fibonacci_calc(uint32_t cnt)
{
    if (cnt <= 1) {
        return cnt;
    } else {
        return math_fibonacci_calc(cnt - 1) + math_fibonacci_calc(cnt - 2);
    }
}

// 黄金比の計算
double math_goldenratio_calc(void)
{
    double phi = (1 + sqrt(5)) / 2.0; // 黄金比の値

    return phi;
}

// ネイピア(マイコンでの計算は無理やから定数出力)
double math_napier_calc(void)
{
    return MATH_E;
}

// 高速逆平方根
float math_fast_inv_sqrt(float num)
{
    long i;
    float x2, y;
    const float threehalfs = 1.5F;

    x2 = num * 0.5F;
    y = num;
    i = *(long *)&y;                     // 浮動小数点数をビットパターンとして解釈
    i = 0x5f3759df - (i >> 1);           // ビット操作による初期推定値
    y = *(float *)&i;                    // 初期推定値を浮動小数点数に戻す
    y = y * (threehalfs - (x2 * y * y)); // ニュートン法による補正

    return y;
}

void math_uc_fibonacci(uint32_t n)
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

void math_uc_prime(uint32_t n)
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

void math_uc_calc_pi(uint32_t n)
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

void math_uc_mandelbrot(void)
{
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

void math_uc_math_test(void)
{
    uint32_t i,fib;
    volatile double pi;
    volatile double phi;
    volatile double napier;
    volatile double invsqrt;
    volatile double result;

    DEBUG_PRINTF("*************************************\n");
    DEBUG_PRINTF("[Math App Test]\n");
    DEBUG_PRINTF("*************************************\n");

    // tan(355/226)の計算（※期待値:-7497258.185...）
    __DI();
    uint32_t start_time = time_us_32();
    result = math_calc_accuracy();
    uint32_t end_time = time_us_32();
    __EI();
    DEBUG_PRINTF("tan(355/226) = %.3f\n", result);
    DEBUG_PRINTF("proc time : %d usec\n", end_time - start_time);

    // 円周率π
    math_uc_calc_pi(MATH_PI_CALC_TIME);

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
    math_uc_fibonacci(FIBONACCI_N);

    // 高速逆平方根
    for(i = 1; i < INVSQRT_N; i++)
    {
        invsqrt = math_fast_inv_sqrt(i);
        DEBUG_PRINTF("%d's inv sqrt = %.15f\n", i, invsqrt);
    }
    DEBUG_PRINTF("*************************************\n");
}