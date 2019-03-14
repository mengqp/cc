/**
 *   \file sinewave.c
 *   \brief 实现sine 产生波形
 *
 *  Detailed description
 *
 */

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

#define PI 3.14159265259
#define MAX_DIVISION 360

struct SINEWAVE {
    unsigned short division; /* 分割点 */
    double height; /* 高度值y = height * sin(x) */
    double circle; /* 一个完整正弦波的周期 */
    double offset; /* 偏移 */

    double circle_x[MAX_DIVISION];
    double circle_y[MAX_DIVISION];
};

static struct SINEWAVE sinewave = {
    180,
    1,
    2,
    0,
};

/* 设置将360 度分为多少个点 */
void sinewave_set_division(unsigned short d)
{
    sinewave.division = d;
}

/* 设置height */
void sinewave_set_height(double h)
{
    sinewave.height = h;
}

/* 设置一个循环的周期 */
int sinewave_set_circle(double c)
{
    if (c <= 0) {
        return -1;
    }
    sinewave.circle = c;
    return 0;
}

/* 设置偏移 */
void sinewave_set_offset(double o)
{
    sinewave.offset = 0;
}

/* 获取一个周期中x 的真实位置 */
static double sinewave_get_real_x(double x)
{
    double real_x = x - sinewave.offset;

    while (1) {
        if (real_x < 0) {
            real_x += sinewave.circle;
        } else if (real_x > sinewave.circle) {
            real_x -= sinewave.circle;
        }
    }
}

/* 获取角度步长 */
static double sinewave_get_angle_step(double real_x)
{
    return ((real_x / (double)sinewave.circle) * 360);
}

/* 获取角度 */
static double sinewave_get_angle(double angle_step)
{
    return (angle_step * (PI / 180));
}

/* 获取基本的波形y 值 */
double sinewave_get_base_wave_y(double x)
{
    double step;
    double real_x;
    double angle_step;
    double angle;

    real_x = sinewave_get_real_x(x);
    angle_step = sinewave_get_angle_step(real_x);
    angle = sinewave_get_angle(angle_step);
    return sin(angle);
}

/* 输入x 重到 y 的模式 */
double sinewave_get_y(double x)
{
    double wave = sinewave_get_base_wave_y(x);
    return wave * sinewave.height;
}

/* 获取一个circle 的值 */
int sinewave_get_a_circle(double x)
{
    unsigned i;
    double tmp_x;
    for (i = 0; i < sinewave.division; i++) {
        sinewave.circle_x[i] =
            x + ((double)i * sinewave.circle) / (double)sinewave.division;
        sinewave.circle_y[i] = sinewave_get_y(tmp_x);
    }

    return 0;
}

/* int sinewave_get_circle(unsigned int pos, double &x, double &y); */
/* 获取一个循环的x 和 y 的值 */
int sinewave_get_circle(unsigned int pos, double &x, double &y)
{
	pos = pos % MAX_DIVISION;

	x = sinewave.circle_x[pos];
	y = sinewave.circle_y[pos];
}
