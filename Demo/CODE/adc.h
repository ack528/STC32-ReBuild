#ifndef DATA_H
#define DATA_H

extern int flag_turn;


void adc_get(int* temp);
int MeanFilter(int *arr, int n);
float error_get(int*temp,int flag);

#endif