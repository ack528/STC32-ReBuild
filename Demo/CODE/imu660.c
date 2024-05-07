#include "headfile.h"
//float Single_Angle=0;
float Single_Angle_Get(void)
{
//	imu660ra_get_gyro();
	return imu660ra_gyro_z * isr_time/ 65.6;
}