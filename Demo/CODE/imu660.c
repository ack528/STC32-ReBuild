#include "headfile.h"

float Single_Angle_Get(void)
{
	return imu660ra_gyro_z * isr_time/ 65.6;
}