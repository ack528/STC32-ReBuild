#include "headfile.h"
#include "dir.h"
float temp = 0;

void Dir_Loop(float error, float speed_goal, int flag)
{
    {
//      dir_loop_pid.KP = Kp_Select(error);
			
        dir_loop_pid.ek =  error;
				temp =  fabs(error) * 650* dir_loop_pid.ek //800 250  /600 300
								+ 210 * dir_loop_pid.ek
								- 1 * imu660ra_gyro_z / 65.6
								+ 400 * (dir_loop_pid.ek - dir_loop_pid.ek_1);

        dir_loop_pid.ek_1 = dir_loop_pid.ek;

    }
    motor_L_pid.SetValue = speed_goal - temp;
    motor_R_pid.SetValue = speed_goal + temp;
}


float  Kp_Select(float error)
{
    return fabs(error) * 50;
//    if(error < 0.05 && error > -0.05) // section1
//      return 150;
//    else if(error < 0.1 && error > -0.1) // section2
//      return 150;
//    else if(error < 0.15 && error > -0.15) //3
//          return 150;
//    else if(error <0.2 && error > -0.2)
//      return  150;
//    else if(error < 0.25 && error > -0.25)
//      return  150;
//    else if(error <0.3 && error > -0.3)
//      return 180;
//    else if(error < 0.35 && error > -0.35)
//          return 210;
//    else if(error < 0.4 && error > -0.4)
//      return 240;
//    else if(error < 0.45 && error > -0.45)
//      return 270;
//    else if(error < 0.5 && error > -0.5)
//      return 300;
//    else if(error < 0.55 && error > -0.55)
//      return 330;
//    else
//      { return 400;}
}