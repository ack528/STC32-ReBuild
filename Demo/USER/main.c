#include "headfile.h"
#define BEEP P67
#define LED  P52

extern int duty_L,duty_R;

float speed_goal = 280;
int main()
{
    board_init();
		InitPID();
    EnableGlobalIRQ();
    motor_L_pid.SetValue = 220; 
    motor_R_pid.SetValue = 220;
    printf("Start\r\n");
    while (1)
    {
        if (TIM1_Flag)
        {
            LED = 0;
//						dl1b_get_distance();
            imu660ra_get_gyro();
						state_detect(adc_value); //ÔªËØÅÐ¶Ï
            if (stop_jump() == 1)
            {
                state_lead = 6;
                Stop_Action();
            }
            else
            {
									Action();
//									Pid_Test_1();
						}
	
						Lcd_Show_Para();
            TIM1_Flag = 0;
            LED = 1;
				}
    }
}


uint8 uart_delay = 0;
void Lcd_Show_Para(void)
{
//		lcd_showint32(0,0,(int)imu660_init,4);
//		lcd_showint32(0,1,(int)motor_R_pid.ActValue,4);
//			
//		lcd_showint32(0,0,(int)adc_value[0],4);
//		lcd_showint32(0,1,(int)adc_value[1],4);
//		lcd_showint32(0,2,(int)adc_value[2],4);
//		lcd_showint32(0,3,(int)adc_value[3],4);
//		lcd_showint32(0,4,(int)adc_value[4],4);

		uart_delay++;
		if (uart_delay > 2)
		{
				uart_delay = 0;
//				printf("%f,%f,%f,%f,%f,%f\r\n", motor_L_pid.ActValue, motor_R_pid.ActValue,
//																	motor_L_pid.SetValueTmp, motor_R_pid.SetValueTmp,
//																		(float)(duty_L/10),(float)(duty_R/10));
				
				printf("%f,%f,%f,%f\r\n", motor_L_pid.ActValue, motor_R_pid.ActValue,
														motor_L_pid.SetValueTmp, motor_R_pid.SetValueTmp);

//				printf("%d,%d,%d,%d,%d\r\n", adc_value[0], adc_value[1],adc_value[2],
//		    														adc_value[3], adc_value[4]);
//				printf("%d,%d,%d,%d\r\n", adc_value[0], adc_value[1],
//																	adc_value[3], adc_value[4]);

		}
}

int adc_value[8] = {0};
void Action(void)
{
		switch (state[state_lead])
		{
				case Track:
							BEEP = 0;
							Track_Action(adc_value);
							break;
				case Right_Angle:
							BEEP = 0;
							Track_Action(adc_value);
							break;
				case Big_Circ_Left:
							Circ_Left_Action(adc_value);
							break;
				case Small_Circ_Left:
							Circ_Left_Action(adc_value);
							break;
				case Big_Circ_Right:
							P67 = 0;
							Circ_Right_Action(adc_value);
							break;
				case Small_Circ_Right:
							Circ_Right_Action(adc_value);
							break;
				case Obstacle:
							Obstacle_Action();
							break;
				case Stop:
							Stop_Action();
		}
}

uint32 pid_t = 0;
void Pid_Test_1(void)
{
	pid_t++;
	if(pid_t==1)
	{
		motor_L_pid.SetValue = 0; 
    motor_R_pid.SetValue = 0;
	}
	else if(pid_t==200)
	{
		motor_L_pid.SetValue = 80; 
    motor_R_pid.SetValue = 80;
	}
	else if(pid_t==400)
	{
		motor_L_pid.SetValue = 160; 
    motor_R_pid.SetValue = 160;
	}
		else if(pid_t==600)
	{
		motor_L_pid.SetValue = 240; 
    motor_R_pid.SetValue = 240;
	}
		else if(pid_t==800)
	{
		motor_L_pid.SetValue = 160; 
    motor_R_pid.SetValue = 160;
	}
		else if(pid_t==1000)
	{
		motor_L_pid.SetValue = 80; 
    motor_R_pid.SetValue = 80;
	}
		else if(pid_t>1200)
	{
		pid_t= 0;
	}
}