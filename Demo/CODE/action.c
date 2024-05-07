#include "headfile.h"
float speed_goal=200;
float error=0;
float error_rate=0;
int count=0;
void Track_Action(int *temp)
{
//	static float angle=0;
//  error_rate=error_rate_count1(temp[1],temp[2]);
	if(flag_turn==cross)
	{
		beep_on();

	}
	else
	{
		beep_off();
	}
	error=error_get(temp,flag_turn);
	speed_goal=speed_section(error,state[state_lead]);
	Dir_Loop(error,speed_goal,flag_turn);
//	printf("%d,%d,%d,%d,\r\n",temp[0],temp[1],temp[2],temp[3]);
//	printf("%f,%f,%f,%f,%f\r\n",error,motor_L_pid.SetValue,motor_R_pid.SetValue,motor_L_pid.ActValue,motor_R_pid.ActValue);
}

	
void Circ_Left_Action(int *temp)
{
 error=error_get(temp,flag_turn);
	switch (Flag_Circ)
	{
		case 1:
		speed_goal=speed_section(error,state[state_lead]);
		Dir_Loop(error,speed_goal,flag_turn);
		break;
		case 2:
		motor_L_pid.SetValue=0;
		motor_R_pid.SetValue=speed_goal*2;
		break;
		case 3:
		speed_goal=speed_section(error,state[state_lead]);
		break;
		case 4:
		motor_L_pid.SetValue=speed_goal;
		motor_R_pid.SetValue=speed_goal;
		break;
	}
}
void Circ_Right_Action(int* temp)
{
  error=error_get(temp,flag_turn);
	speed_goal=speed_section(error,state[state_lead]);
	switch (Flag_Circ)
	{
		case 1:
		Dir_Loop(error,speed_goal,flag_turn);
		break;
		case 2:
		motor_L_pid.SetValue=speed_goal*2;
		motor_R_pid.SetValue=0;
		break;
		case 3:
		speed_goal=speed_section(error,state[state_lead]);
		Dir_Loop(error,speed_goal,flag_turn);
		break;
		case 4:
		motor_L_pid.SetValue=speed_goal;
		motor_R_pid.SetValue=speed_goal;
		break;
	}
}
void Obstacle_Action(void)
{
//	printf("in\r\n");
	switch(Flag_Obstacle)
	{
//		

		case 1:
//			error=0.3;
			speed_goal=speed_section(error,state[state_lead]);
//			Dir_Loop(error,speed_goal,flag_turn);
				motor_L_pid.SetValue=speed_goal*0;
		motor_R_pid.SetValue=speed_goal*2;break;
		case 2:
//			error=-0.3;
		speed_goal=speed_section(error,state[state_lead]);
//			Dir_Loop(error,speed_goal,flag_turn);
		motor_L_pid.SetValue=speed_goal*1;
		motor_R_pid.SetValue=speed_goal*1;break;
		case 3:
		speed_goal=speed_section(error,state[state_lead]);
		motor_L_pid.SetValue=speed_goal*2;
		motor_R_pid.SetValue=speed_goal*0;break;
		case 4:
		speed_goal=speed_section(error,state[state_lead]);
		motor_L_pid.SetValue=speed_goal*1;
		motor_R_pid.SetValue=speed_goal*1;break;
		case 5:
		speed_goal=speed_section(error,state[state_lead]);
		motor_L_pid.SetValue=speed_goal*2;
		motor_R_pid.SetValue=speed_goal*0;break;
		case 6:
			P32=0;
		speed_goal=speed_section(error,state[state_lead]);
		motor_L_pid.SetValue=speed_goal*1;
		motor_R_pid.SetValue=speed_goal*1;break;
	}
//	printf("%d\r\n",Flag_Obstacle);
}
void Stop_Action()
{
		motor_L_pid.SetValue=0;
		motor_R_pid.SetValue=0;
	  motor_L_pid.KP=50;
		motor_R_pid.KP=50;
		motor_L_pid.KI=4;
		motor_R_pid.KI=4;
	  motor_L_pid.KD=30;
		motor_R_pid.KD=30;
	
}
void beep_on()
{

	{
			P67=1;
	}

}
void beep_off()
{
	P67=0;
	count=0;
}