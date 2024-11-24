/**
 * @file benchmark_test.cpp
 * @author ちみ/Chimi(https://github.com/Chimipupu)
 * @brief マイコン評価用ベンチテストのアプリ
 * @version 0.1
 * @date 2024-11-24
 * 
 * @copyright Copyright (c) 2024 ちみ/Chimi(https://github.com/Chimipupu)
 * 
 */

#include "benchmark_test.hpp"

#ifdef __BENCHMARK_TEST__
#define BECHTEST_PROC(n, func)

static void add_test_int(void);
static void sub_test_int(void);
static void mul_test_int(void);
static void div_test_int(void);
static void calc_test_int(void);
static void add_test_float(void);
static void sub_test_float(void);
static void mul_test_float(void);
static void div_test_float(void);
static void calc_test_float(void);
static void sin_test(void);
static void cos_test(void);
static void atan2_test(void);
static void sqrt_test(void);
static void mem_test(void);
static void gpio_tgl_test(void);

static void add_test_int(void)
{
    // TODO:
}

static void sub_test_int(void)
{
    // TODO:
}

static void mul_test_int(void)
{
    // TODO:
}

static void div_test_int(void)
{
    // TODO:
}

static void add_test_float(void)
{
    // TODO:
}

static void sub_test_float(void)
{
    // TODO:
}

static void mul_test_float(void)
{
    // TODO:
}

static void div_test_float(void)
{
    // TODO:
}

static void sin_test(void)
{
    // TODO:
}

static void cos_test(void)
{
    // TODO:
}

static void atan2_test(void)
{
    // TODO:
}

static void sqrt_test(void)
{
    // TODO:
}

static void mem_test(void)
{
    // TODO:
}

static void gpio_tgl_test(void)
{
    // TODO:
}

/**
 * @brief 四則演算（整数）テスト
 * 
 */
static void calc_test_int(void)
{
    add_test_int();
    sub_test_int();
    mul_test_int();
    div_test_int();
}

/**
 * @brief 四則演算（浮動小数）テスト
 * 
 */
static void calc_test_float(void)
{
    add_test_float();
    sub_test_float();
    mul_test_float();
    div_test_float();
}
#endif /* __BENCHMARK_TEST__ */

/**
 * @brief ベンチマークテスト関数
 * 
 */
void benchmark_test(void)
{
    DEBUG_PRINTF("[BenchMark Test Start]");
#ifdef __BENCHMARK_TEST__
    // 四則演算（整数）
    calc_test_int();

    // 四則演算（浮動小数）
    calc_test_float();

    // sin, cos, atan2, sqrt
    sin_test();
    cos_test();
    atan2_test();
    sqrt_test();

    // メモリ
    mem_test();

    // GPIOのトグル
    gpio_tgl_test();
#endif /* __BENCHMARK_TEST__ */
    DEBUG_PRINTF("[BenchMark Test END]");
}