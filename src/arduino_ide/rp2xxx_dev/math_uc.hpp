/**
 * @file math_uc.hpp
 * @author ちみ/Chimi(https://github.com/Chimipupu)
 * @brief 数学計算アプリ
 * @version 0.1
 * @date 2024-10-16
 * 
 * @copyright Copyright (c) 2024 ちみ/Chimi(https://github.com/Chimipupu)
 * 
 */
#ifndef MATH_UC_H
#define MATH_UC_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <math.h>

#ifndef M_PI
#define MATH_PI      M_PI
#else
#define MATH_PI      3.14159265358979323846
#endif

#ifndef M_E
#define MATH_E      2.7182818284590452354
#else
#define MATH_E      M_E
#endif

#define UNKNOWN_VAL 0

#define MATH_DEG_TO_RAD(deg)    (deg * M_PI) / 180.0f      // 度からラジアン
#define MATH_RAD_TO_DEG(rad)    ((rad) * 180.0f / M_PI)    // ラジアンから度

double math_calc_accuracy(void);
bool math_is_prime_num(uint32_t n);
double math_pythagoras(double a, double b);
double math_pi_calc(uint32_t cnt);
uint32_t math_fibonacci_calc(uint32_t cnt);
double math_goldenratio_calc(void);
double math_napier_calc(void);
float math_fast_inv_sqrt(float num);
void math_uc_fibonacci(uint32_t n);
void math_uc_prime(uint32_t n);
void math_uc_calc_pi(uint32_t n);
void math_uc_mandelbrot(void);
void math_uc_math_test(void);

#endif /* MATH_UC_H */