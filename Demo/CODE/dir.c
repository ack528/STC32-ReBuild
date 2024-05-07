#include "headfile.h"
	float temp=0;
//void Dir_Loop(float error,float speed_goal,int flag)
//{

//if(flag==0)
//{
//	count++;
//	if(count<60)
//	{
//		P67=1;
//	}
//	else
//	{
//		P67=0;
//		count=0;
//	}
//	
//	dir_loop_pid.KP=Kp_Select_1(error);
//}
//else
//{
//	count=0;
//	P67=0;
//		dir_loop_pid.KP=Kp_Select(error);
//}

//  dir_loop_pid.ek =  error;
//   temp= dir_loop_pid.KP* dir_loop_pid.ek  
////	-imu660ra_gyro_z / 65.6
//	+ dir_loop_pid.KD * (dir_loop_pid.ek - dir_loop_pid.ek_1)
//	;
//	dir_loop_pid.ek_1=dir_loop_pid.ek;
//	motor_L_pid.SetValue=speed_goal-temp;
//	motor_R_pid.SetValue=speed_goal+temp;
//}







float  Kp_Select(float error)
{
	return fabs(error)*50;
//    if(error < 0.05 && error > -0.05) // section1
//      return 150;
//    else if(error < 0.1 && error > -0.1) // section2
//      return 150;
//    else if(error < 0.15 && error > -0.15) //3
//			return 150;
//    else if(error <0.2 && error > -0.2)
//      return  150;
//    else if(error < 0.25 && error > -0.25)
//      return  150;
//    else if(error <0.3 && error > -0.3)
//      return 180;
//    else if(error < 0.35 && error > -0.35)
//			return 210;
//    else if(error < 0.4 && error > -0.4)
//      return 240;
//    else if(error < 0.45 && error > -0.45)
//      return 270;
//    else if(error < 0.5 && error > -0.5)
//      return 300;
//    else if(error < 0.55 && error > -0.55)
//      return 330;
//    else 
//		{ return 400;}
}
void Dir_Loop(float error,float speed_goal,int flag)
{
//	if(flag==0)
//	{
//		
//	dir_loop_pid.KP=Kp_Select(error);
//		dir_loop_pid.ek =  error;
//   temp= dir_loop_pid.KP * dir_loop_pid.ek  +100*dir_loop_pid.ek
//	- imu660ra_gyro_z / 65.6
//	+ dir_loop_pid.KD * (dir_loop_pid.ek - dir_loop_pid.ek_1)
//	;
//	dir_loop_pid.ek_1=dir_loop_pid.ek;
// ;
//	}
//	else
//	printf("%f\r\n",error);
	{
	dir_loop_pid.KP=Kp_Select(error);
  dir_loop_pid.ek =  error;
   temp= 
		fabs(error)*800* dir_loop_pid.ek+
		150*dir_loop_pid.ek
	- imu660ra_gyro_z/65.6
	+ dir_loop_pid.KD * (dir_loop_pid.ek - dir_loop_pid.ek_1)
	;
//		printf("%f\r\n",error);
	dir_loop_pid.ek_1=dir_loop_pid.ek;
//  temp=temp;
	}
//	printf("%f\r\n",temp);
	motor_L_pid.SetValue=speed_goal-temp;
	motor_R_pid.SetValue=speed_goal+temp;
}
//void angle_loop()
//{
//	float angle_speed=0;
//	angle_speed=(motor_R_pid.SetValue-motor_L_pid.SetValue)/15.5;
//	
//}


































//void Dir_Loop(float error,float speed_goal)
//{

//	float inc=0;
////	dir_loop_pid.KP=Kp_Select(error)*0.6;
//		dir_loop_pid.ActValue =  error;

//		inc=PID_Control_Inc(&dir_loop_pid,1);
//	if(inc>-3&&inc<3)
//	{inc=0;}
//		temp+=inc;
//	dir_loop_pid.ek_1=dir_loop_pid.ek;
////temp=temp*0.6;
////	printf("%f\r\n",temp);
////	temp=temp>speed_goal?speed_goal:temp;
////	temp=temp<(0-speed_goal)?(0-speed_goal):temp;
//  temp=temp>100?100:temp;
//	temp=temp<(-100)?(-100):temp;
//	motor_L_pid.SetValue=speed_goal+temp;
//	motor_R_pid.SetValue=speed_goal-temp;
//}