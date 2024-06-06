#include "headfile.h"
#include "speed.h"
int duty_L=800,duty_R=800;
float speed_section(float error,char i)
{
	return 240;
}

void Get_Actual_Speed()
{
	motor_L_pid.ActValue=((float)encoder_L_get()*ActSpeed_Rate*200);
	motor_R_pid.ActValue=((float)encoder_R_get()*ActSpeed_Rate*200);
}

void Speed_Loop()
{     
  float inc_L, inc_R;

		Get_Actual_Speed();
    // 外轮速度限制
    if(motor_L_pid.SetValue > 2*speed_goal)
        motor_L_pid.SetValue =2*speed_goal;
    if(motor_R_pid.SetValue >2*speed_goal)
        motor_R_pid.SetValue = 2*speed_goal;
		if(motor_L_pid.SetValue <-1*speed_goal)
				motor_L_pid.SetValue =-1*speed_goal;
    if(motor_R_pid.SetValue <-1*speed_goal)
				motor_R_pid.SetValue =-1*speed_goal;
		
		motor_L_pid.SetValueTmp = motor_L_pid.SetValue;
		motor_R_pid.SetValueTmp = motor_R_pid.SetValue;

    inc_L = PID_Control_Inc(&motor_L_pid,0);
    inc_R = PID_Control_Inc(&motor_R_pid,0);
		
    duty_L += inc_L;			//增量式pid输出的是增量，要累加
    duty_R += inc_R;			//增量式pid输出的是增量，要累加

    if(duty_L < duty_min)	//pwm限幅
        duty_L = duty_min;
    if(duty_R< duty_min)
        duty_R = duty_min;

    if(duty_L> duty_max)
        duty_L = duty_max;
    if(duty_R > duty_max)
        duty_R = duty_max;
		duty_set(duty_L,duty_R);
//		duty_set(0,-2000);

}

void duty_set(int left_duty,int right_duty)
{
	    if(left_duty< 0)
    {
        pwm_duty(PWM_1, 0);
        pwm_duty(PWM_2, -left_duty);
    }
    else 
    {
        pwm_duty(PWM_1, left_duty);
        pwm_duty(PWM_2, 0);
    }
    if(right_duty < 0)
    {
        pwm_duty(PWM_3, 0);
        pwm_duty(PWM_4,-right_duty);
    }
    else 
    {
        pwm_duty(PWM_3, right_duty);
        pwm_duty(PWM_4, 0);
    }
}

