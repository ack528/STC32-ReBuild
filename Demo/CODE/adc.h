#ifndef DATA_H
#define DATA_H
//int adc_value[4];
//unsigned int sqrt_16(unsigned long M) ;
//extern float error;
extern int flag_turn;
void adc_get(int* temp);
int MeanFilter(int *arr, int n);
float error_get(int*temp,int flag);
int max_count(int a,int b);
int min_count(int a,int b);
#endif