#ifndef __MAIN_H_
#define __MAIN_H_

#define BEEP P67
#define LED  P52

extern float ADC_error;

extern int adc_value[8];
void Test_Func(void);
void Action(void);
void Lcd_Show_Para(void);
void Pid_Test_1(void);
#endif
