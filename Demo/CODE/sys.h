#ifndef SYS_H
#define SYS_H
/***************编码器***************/
//定义脉冲引脚
#define Encoder_L   CTIM3_P04
#define Encoder_R   CTIM0_P34
//定义方向引脚
#define DIR_Encoder_L     P53
#define DIR_Encoder_R     P35

/***************电机***************/
////定义脉冲引脚
//#define PWM_L   PWMA_CH4P_P66
//#define PWM_R   PWMA_CH2P_P62
////定义方向引脚
//#define DIR_L   P64
//#define DIR_R   P60

#define PWM_1 PWMA_CH3P_P64    // 左正
#define PWM_2 PWMA_CH4P_P66		 // 左负
#define PWM_3 PWMA_CH1P_P60    // 右正
#define PWM_4 PWMA_CH2P_P62		 // 右负

/****************中断时间***********/

#define isr_time 0.005
#define ActSpeed_Rate 0.0088
#endif