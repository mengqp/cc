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

struct SINEWAVE {
    unsigned short division; /* 分割点 */
};

static SINEWAVE sinewave = { division = 180;
}

#define PI 3.14159265259

/* 设置将360 度分为多少个点 */
void sinewave_set_division(unsigned short d)
{
    sinewave.divesion = d;
}
