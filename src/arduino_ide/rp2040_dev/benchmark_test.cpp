/**
 * @file benchmark_test.cpp
 * @author ちみ/Chimi(https://github.com/Chimipupu)
 * @brief ベンチマークテスト アプリ
 * @version 0.1
 * @date 2024-11-24
 * 
 * @copyright Copyright (c) 2024 ちみ/Chimi(https://github.com/Chimipupu)
 * 
 */

#include "benchmark_test.hpp"

#ifdef __BENCHMARK_TEST__

#define FUNC_SYMBOL(func) #func

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
static uint32_t test_run(void (*p_func)());
static void benchmark(uint32_t n, void (*p_func)(), const char *p_func_name);

void (*p_func)(void);

static void add_test_int(void)
{
    volatile uint32_t val = 0;
    val = val + 1;
}

static void sub_test_int(void)
{
    volatile uint32_t val = 1;
    val = val - 1;
}

static void mul_test_int(void)
{
    volatile uint32_t val = 2;
    val = val * 2;
}

static void div_test_int(void)
{
    volatile uint32_t val = 2;
    val = val / 2;
}

static void add_test_float(void)
{
    volatile double val = 0.0f;
    val = val + 1.0f;
}

static void sub_test_float(void)
{
    volatile double val = 1.0f;
    val = val - 1.0f;
}

static void mul_test_float(void)
{
    volatile double val = 2.0f;
    val = val * 2.0f;
}

static void div_test_float(void)
{
    volatile double val = 2.0f;
    val = val / 2.0f;
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
    benchmark(TEST_N, add_test_int, FUNC_SYMBOL(add_test_int));
    benchmark(TEST_N, sub_test_int, FUNC_SYMBOL(sub_test_int));
    benchmark(TEST_N, mul_test_int, FUNC_SYMBOL(mul_test_int));
    benchmark(TEST_N, div_test_int, FUNC_SYMBOL(div_test_int));
}

/**
 * @brief 四則演算（浮動小数）テスト
 * 
 */
static void calc_test_float(void)
{
    benchmark(TEST_N, add_test_float, FUNC_SYMBOL(add_test_float));
    benchmark(TEST_N, sub_test_float, FUNC_SYMBOL(sub_test_float));
    benchmark(TEST_N, mul_test_float, FUNC_SYMBOL(mul_test_float));
    benchmark(TEST_N, div_test_float, FUNC_SYMBOL(div_test_float));
}
#endif /* __BENCHMARK_TEST__ */

static uint32_t test_run(void (*p_func)())
{
    uint32_t start_time = time_us_32();
    ((void (*)(void))p_func)();
    uint32_t end_time = time_us_32();

    return (end_time - start_time);
}

static void benchmark(uint32_t n, void (*p_func)(), const char *p_func_name)
{
    uint32_t proc_time_buf[n] = {0};
    uint32_t proc_time_avg = 0;

    DEBUG_PRINTF("%s() Func (n = %d)\n", p_func_name, TEST_N);
    memset(&proc_time_buf[0], 0x00, sizeof(proc_time_buf));

    for(uint32_t i = 0; i < n; i++)
    {
        proc_time_buf[i] = test_run(p_func);
        proc_time_avg += proc_time_buf[i];
    }

    proc_time_avg = proc_time_avg / n;
    DEBUG_PRINTF("Proc Time Avg = %d [usec]\n", proc_time_avg);
}
/**
 * @brief ベンチマークテスト関数
 * 
 */
void benchmark_test(void)
{
    DEBUG_PRINTF("[BenchMark Test Start]\n");
#ifdef __BENCHMARK_TEST__
    // 四則演算（整数）
    calc_test_int();

    // 四則演算（浮動小数）
    calc_test_float();
#if 0
    // sin, cos, atan2, sqrt
    sin_test();
    cos_test();
    atan2_test();
    sqrt_test();

    // メモリ
    mem_test();

    // GPIOのトグル
    gpio_tgl_test();
#endif
#endif /* __BENCHMARK_TEST__ */
    DEBUG_PRINTF("[BenchMark Test END]\n");
}