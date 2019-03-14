/**
 *   \file sinewave.h
 */

#ifndef SINEWAVE_H
#define SINEWAVE_H


void sinewave_set_division(unsigned short d);
void sinewave_set_height(double h);
int sinewave_set_circle(double c);
void sinewave_set_offset(double o);
double sinewave_get_y(double x);
int sinewave_get_a_circle(double x);
int sinewave_get_circle(unsigned int pos, double *x, double *y);

#endif /* SINEWAVE_H */
