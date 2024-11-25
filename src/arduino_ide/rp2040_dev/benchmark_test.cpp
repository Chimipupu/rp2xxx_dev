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

#include <math.h>
#include "benchmark_test.hpp"
#include "math_uc.hpp"
#include "rp2040_reg.hpp"
#include "cpm.hpp"

#ifdef __BENCHMARK_TEST__
#include <float.h>
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
static void add_test_double(void);
static void sub_test_double(void);
static void mul_test_double(void);
static void div_test_double(void);
static void calc_test_double(void);
static void sin_test(void);
static void cos_test(void);
static void tan_test(void);
static void atan2_test(void);
static void sqrt_test(void);
static void mem_test(void);
static void gpio_tgl_test(void);
static uint32_t test_run(void (*p_func)());
static void benchmark(uint32_t n, void (*p_func)(), const char *p_func_name);
volatile double g_ang = MATH_DEG_TO_RAD(30); // 30度のラジアン π/6

void (*p_func)(void);

static void add_test_int(void)
{
    volatile uint32_t val = 0;
    volatile uint32_t cnt = 0;

    for(cnt; cnt < TEST_LOOP; cnt++)
    {
        val = val + 1;
    }
}

static void sub_test_int(void)
{
    volatile uint32_t val = UINT32_MAX;
    volatile uint32_t cnt = 0;

    for(cnt; cnt < TEST_LOOP; cnt++)
    {
        val = val - 1;
    }
}

static void mul_test_int(void)
{
    volatile uint32_t val = 2;
    volatile uint32_t cnt = 0;

    for(cnt; cnt < TEST_LOOP; cnt++)
    {
        val = val * 2;
    }
}

static void div_test_int(void)
{
    volatile uint32_t val = UINT32_MAX;
    volatile uint32_t cnt = 0;

    for(cnt; cnt < TEST_LOOP; cnt++)
    {
        val = val / 2;
    }
}

static void add_test_float(void)
{
    volatile float val = 0.0f;
    volatile float cnt = 0.0f;

    for(cnt; cnt < TEST_LOOP; cnt++)
    {
        val = val + 0.1f;
    }
}

static void sub_test_float(void)
{
    volatile float val = DBL_MAX;
    volatile float cnt = 0.0f;

    for(cnt; cnt < TEST_LOOP; cnt++)
    {
        val = val - 0.1f;
    }
}

static void mul_test_float(void)
{
    volatile float val = 0.0f;
    volatile float cnt = 0.0f;

    for(cnt; cnt < TEST_LOOP; cnt++)
    {
        val = val * 2.0f;
    }
}

static void div_test_float(void)
{
    volatile float val = DBL_MAX;
    volatile float cnt = 0.0f;

    for(cnt; cnt < TEST_LOOP; cnt++)
    {
        val = val / 2.0f;
    }
}

static void add_test_double(void)
{
    volatile double val = 0.0f;
    volatile double cnt = 0.0f;

    for(cnt; cnt < TEST_LOOP; cnt++)
    {
        val = val + 0.1f;
    }
}

static void sub_test_double(void)
{
    volatile double val = DBL_MAX;
    volatile double cnt = 0.0f;

    for(cnt; cnt < TEST_LOOP; cnt++)
    {
        val = val - 0.1f;
    }
}

static void mul_test_double(void)
{
    volatile double val = 0.0f;
    volatile double cnt = 0.0f;

    for(cnt; cnt < TEST_LOOP; cnt++)
    {
        val = val * 2.0f;
    }
}

static void div_test_double(void)
{
    volatile double val = DBL_MAX;
    volatile double cnt = 0.0f;

    for(cnt; cnt < TEST_LOOP; cnt++)
    {
        val = val / 2.0f;
    }
}

static void sin_test(void)
{
    volatile double cnt = 0.0f;
    volatile double sin_val = 0.0f;

    for(cnt; cnt < TEST_LOOP; cnt++)
    {
        sin_val = sin(g_ang);
    }
}

static void cos_test(void)
{
    volatile double cnt = 0.0f;
    volatile double cos_val = 0.0f;

    for(cnt; cnt < TEST_LOOP; cnt++)
    {
        cos_val = cos(g_ang);
    }
}

static void tan_test(void)
{
    volatile double cnt = 0.0f;
    volatile double tan_val = 0.0f;

    for(cnt; cnt < TEST_LOOP; cnt++)
    {
        tan_val = tan(g_ang);
    }
}

static void atan2_test(void)
{
    volatile double cnt = 0.0f;
    volatile double x = 1.0;
    volatile double y = 1.0;
    volatile double atan2_val = 0;

    for(cnt; cnt < TEST_LOOP; cnt++)
    {
        atan2_val = atan2(y, x);
    }
}

static void sqrt_test(void)
{
    volatile double cnt = 0.0f;
    volatile double root = 0;

    for(cnt; cnt < TEST_LOOP; cnt++)
    {
        root = sqrt(2.0f);
    }
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
 * @brief 四則演算（浮動小数 float）テスト
 * 
 */
static void calc_test_float(void)
{
    benchmark(TEST_N, add_test_float, FUNC_SYMBOL(add_test_float));
    benchmark(TEST_N, sub_test_float, FUNC_SYMBOL(sub_test_float));
    benchmark(TEST_N, mul_test_float, FUNC_SYMBOL(mul_test_float));
    benchmark(TEST_N, div_test_float, FUNC_SYMBOL(div_test_float));
}

/**
 * @brief 四則演算（浮動小数 double）テスト
 * 
 */
static void calc_test_double(void)
{
    benchmark(TEST_N, add_test_double, FUNC_SYMBOL(add_test_double));
    benchmark(TEST_N, sub_test_double, FUNC_SYMBOL(sub_test_double));
    benchmark(TEST_N, mul_test_double, FUNC_SYMBOL(mul_test_double));
    benchmark(TEST_N, div_test_double, FUNC_SYMBOL(div_test_double));
}
#endif /* __BENCHMARK_TEST__ */

static uint32_t test_run(void (*p_func)())
{
    // __DI;
    uint32_t start_time = time_us_32();
    ((void (*)(void))p_func)();
    uint32_t end_time = time_us_32();
    // __EI;

    return (end_time - start_time);
}

static void benchmark(uint32_t n, void (*p_func)(), const char *p_func_name)
{
    uint32_t proc_time_buf[n] = {0};
    uint32_t proc_time_avg = 0;

    DEBUG_PRINTF("%s() Func (n=%d)\t", p_func_name, TEST_N);
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
    cpm_op_msg();
    rp2040_develop_info_print();
    DEBUG_PRINTF("BenchMark Test [Start]\n");
#ifdef __BENCHMARK_TEST__
    // 四則演算（整数）
    calc_test_int();

    // 四則演算（浮動小数）
    calc_test_float();
    calc_test_double();

    // sin, cos, atan2, sqrt
    benchmark(TEST_N, sin_test, FUNC_SYMBOL(sin_test));
    benchmark(TEST_N, cos_test, FUNC_SYMBOL(cos_test));
    benchmark(TEST_N, tan_test, FUNC_SYMBOL(tan_test));
    benchmark(TEST_N, atan2_test, FUNC_SYMBOL(atan2_test));
    benchmark(TEST_N, sqrt_test, FUNC_SYMBOL(sqrt_test));

#if 0
    // メモリ
    mem_test();

    // GPIOのトグル
    gpio_tgl_test();
#endif
#endif /* __BENCHMARK_TEST__ */
    DEBUG_PRINTF("BenchMark Test [End]\n");
}