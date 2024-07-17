#include "headfile.h"
#include "dir.h"
float temp = 0;
extern char state[30];
int pid_lead = 0;
int Kp1[5]={400,500,  0,  0,  450};
int Kp2[5]={180,250,  0,  0,  220};
int Kd1[5]={	1,	1,	1,	1,	1};
int Kd2[5]={	0,	0,	0,	0,	0};
void Dir_Loop(float error, float speed_goal, int flag)
{

		if((state[state_lead]==Big_Circ_Left)||(state[state_lead]==Big_Circ_Right)||
			(state[state_lead]==Small_Circ_Left)||(state[state_lead]==Small_Circ_Right))
		{
				pid_lead = 1;
		}
		else if((state[state_lead]==Ramp))
		{
				pid_lead = 0;
		}
		else if((state[state_lead]==Obstacle))
		{
				pid_lead = 0;
		}
		else
				pid_lead = 4;
		
		dir_loop_pid.ek =  error;
		temp =  fabs(error) * Kp1[pid_lead]* dir_loop_pid.ek //800 250  /600 300
						+ Kp2[pid_lead] * dir_loop_pid.ek
						- Kd1[pid_lead] * imu660ra_gyro_z / 65.6
						+ Kd2[pid_lead] * (dir_loop_pid.ek - dir_loop_pid.ek_1);

		dir_loop_pid.ek_1 = dir_loop_pid.ek;
		
	
    motor_L_pid.SetValue = speed_goal - temp;
    motor_R_pid.SetValue = speed_goal + temp;
}


float  Kp_Select(float error)
{
    return fabs(error) * 50;
}