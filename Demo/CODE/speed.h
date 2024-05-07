#ifndef SPEED_H
#define SPEED_H
//extern float speed_goal;
void duty_set(int left_duty,int right_duty);
void Speed_Loop();
void Get_Actual_Speed();
float speed_section(float error,char i);
extern float error;
extern int duty_L,duty_R;
#endif