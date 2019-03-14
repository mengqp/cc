/**
 *   \file main.c
 *   \brief 正弦波测试函数
 *
 */
#include <stdio.h>
#include <unistd.h>
#include "sinewave.h"

int main(int argc, char *argv[])
{
    double y = 0;
    double x = 0.5;

    y = sinewave_get_y(x);
    printf("y=%f", y);

    if (0 == sinewave_get_a_circle(0)) {
        unsigned int i;
        for (i = 0; i < 180; i++) {
            sinewave_get_circle(i, &x, &y);
            printf("pos=%d x=%f y=%f \n", i, x, y);
            usleep(10);
        }
    }

    return 0;
}
