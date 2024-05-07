#include "headfile.h"
int encoder_L_get(void)
{
	int temp;
	   if(DIR_Encoder_L == 1)
	   {
			temp = ctimer_count_read(Encoder_L);
	   }	   // 左右轮当前速度
	   else
	   {
			temp = 0-ctimer_count_read(Encoder_L);
	   }
	ctimer_count_clean(Encoder_L); // 编码器清零

	return temp;
}


//采集右编码器值


int encoder_R_get(void)
{
int temp;
if(DIR_Encoder_R == 0)
{
    temp = ctimer_count_read(Encoder_R) ; }// 左右轮当前速度
else
{
	temp = 0-ctimer_count_read(Encoder_R);
}
//printf("%d\r\n",temp);
	ctimer_count_clean(Encoder_R); // 编码器清零

	return temp;
}