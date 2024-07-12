#include "headfile.h"
#include "state.h"
int state_lead = 0;
int Flag_Circ = 0;              //圆环不同阶段的指针
int Flag_Right_Angle = 1;       //直角不同阶段的指针
int Flag_Obstacle = 0;
int flag_turn = 0;              //直路元素的指针
float Sum_Distance = 0, Sum_Angle = 0;

char state[30] = {Right_Angle, Track, Track, Track, Track, Track, Stop};  //赛道元素顺序

void state_detect(int *temp)
{
    adc_get(temp);
    switch (state[state_lead]) 
    {
				case Track:
						if (Track_Jump(temp))                   state_lead++;
						break;
				case Right_Angle:
						if (Right_Angle_Jump(&Flag_Right_Angle)) state_lead++;
						break;
				case Big_Circ_Left:
						if (Big_Circ_Left_Jump(&Flag_Circ))     state_lead++;
						break;
				case Big_Circ_Right:
						if (Big_Circ_Right_Jump(&Flag_Circ))    state_lead++;
						break;
				case Small_Circ_Left:
						if (Small_Circ_Left_Jump(&Flag_Circ))   state_lead++;
						break;
				case Small_Circ_Right:
						if (Small_Circ_Right_Jump(&Flag_Circ))  state_lead++;
						break;
				case Obstacle:
						if (Obstacle_Jump(&Flag_Obstacle))      state_lead++;
						break;

				default:
						break;
    }
}
int Track_Jump(int *temp) 
{
    switch (state[state_lead + 1])
    {
				case Big_Circ_Left:
						if (temp[0] > 1200 && temp[4] > 1000)
						{
								Flag_Circ = 1;
								return 1;
						}
						break;
				case Small_Circ_Left:
						if (temp[0] > 1200 && temp[4] > 1000)
						{
								Flag_Circ = 1;
								return 1;
						}
						break;
				case Big_Circ_Right:
						if (temp[4] > 1200 && temp[0] > 1000)
						{
								Flag_Circ = 1;
								return 1;
						}
						break;
				case Small_Circ_Right:
						if (temp[4] > 1200 && temp[0] > 1000)
						{
								Flag_Circ = 1;
								return 1;
						}
						break;
				case Obstacle:
						if (dl1b_distance_mm < 600)
						{
								Flag_Obstacle = 1;
								return 1;
						}
						break;
				case Stop:
						return 1;
						break;
				case Garage_In:
						if (P26 == 0)
						{
								return 1;
						}
						break;
				default:
						break;
    }
		
    return 0;
}
int Right_Angle_Jump(int *Flag)   //直角
{
		switch (*Flag)
    {
    case 1:
        Sum_Distance += (motor_L_pid.ActValue + motor_R_pid.ActValue) * isr_time * 0.5;//计算实例里程数
		
        if (Sum_Distance > 300)
        {
            Sum_Distance = 0;
            (*Flag)++;
					  state_lead = 6;
        }
        break;
//    case 2:
//        Sum_Angle += Single_Angle_Get();
//        if (Sum_Angle > 20)
//        {
//            Sum_Angle = 0;
//            (*Flag)++;
//        }
//        break;
//    case 3:
//        Sum_Angle += Single_Angle_Get();
//        if (Sum_Angle > 295)
//        {
//            Sum_Angle = 0;
//            (*Flag)++;
//						return 1;
//        }
//        break;
//    case 4:
//        Sum_Distance += (motor_L_pid.ActValue + motor_R_pid.ActValue) * isr_time * 0.5;
//        if (Sum_Distance > 40)
//        {
//            Sum_Distance = 0;
//            (*Flag) = 0;
//            return 1;
//        }
    default:
        break;
    }
    return 0;
}
uint32 stop_flag = 0;
uint8 stop_jump(void)
{
    if (adc_value[0] < 50 && adc_value[1] < 50 && adc_value[3] < 50 & adc_value[4] < 50)
    {
        stop_flag++;
        if (stop_flag > 100)
        {
            return 1;
        }
        return 0;
    }
    else
    {
        stop_flag = 0;
        return 0;
    }
}

int Big_Circ_Left_Jump(int *Flag)
{
    switch (*Flag)
    {
    case 1:
        Sum_Distance += (motor_L_pid.ActValue + motor_R_pid.ActValue) * isr_time * 0.5;//计算实例里程数
        if (Sum_Distance > 65)
        {

            Sum_Distance = 0;
            (*Flag)++;
        }
        break;
    case 2:
        Sum_Angle += Single_Angle_Get();
        if (Sum_Angle > 20)
        {
            Sum_Angle = 0;
            (*Flag)++;
        }
        break;
    case 3:
        Sum_Angle += Single_Angle_Get();
        if (Sum_Angle > 295)
        {
            Sum_Angle = 0;
            (*Flag)++;
        }
        break;
    case 4:
        Sum_Distance += (motor_L_pid.ActValue + motor_R_pid.ActValue) * isr_time * 0.5;
        if (Sum_Distance > 40)
        {
            Sum_Distance = 0;
            (*Flag) = 0;
            return 1;
        }
    default:
        break;
    }
    return 0;
}

int Big_Circ_Right_Jump(int *Flag)
{
    switch (*Flag)
    {
    case 1:
        Sum_Distance += (motor_L_pid.ActValue + motor_R_pid.ActValue) * isr_time * 0.5;
        if (Sum_Distance > 60)
        {
            Sum_Distance = 0;
            (*Flag)++;
            //state_lead = 6;
        }
        break;
    case 2:
        Sum_Angle += Single_Angle_Get();
        if (Sum_Angle < -25)
        {
            Sum_Angle = 0;
            (*Flag)++;
            //state_lead = 6;
        }
        break;
    case 3:
        Sum_Angle += Single_Angle_Get();
        if (Sum_Angle < -310)
        {
            Sum_Angle = 0;
            (*Flag)++;

        }
        break;
    case 4:
        Sum_Distance += (motor_L_pid.ActValue + motor_R_pid.ActValue) * isr_time * 0.5;
        if (Sum_Distance > 60)
        {
            Sum_Distance = 0;
            (*Flag) = 0;
//          state_lead = 6;
            return 1;

        }
    default:
        break;
    }
    return 0;
}

int Small_Circ_Left_Jump(int *Flag)
{
    switch ((*Flag))
    {
    case 1:
        Sum_Distance += (motor_L_pid.ActValue + motor_R_pid.ActValue) * isr_time * 0.5;
        if (Sum_Distance > 60)
        {
            Sum_Distance = 0;
            (*Flag)++;
        }
        break;
    case 2:
        Sum_Angle += Single_Angle_Get();
        if (Sum_Angle > 40)
        {
            Sum_Angle = 0;
            (*Flag)++;
        }
        break;
    case 3:
        Sum_Angle += Single_Angle_Get();
        if (Sum_Angle > 287)
        {
            Sum_Angle = 0;
            (*Flag)++;
        }
        break;
    case 4:
        Sum_Distance += (motor_L_pid.ActValue + motor_R_pid.ActValue) * isr_time * 0.5;
        if (Sum_Distance > 80)
        {
            Sum_Distance = 0;
            (*Flag) = 0;
            return 1;
        }
    default:
        break;
    }
    return 0;
}

int Small_Circ_Right_Jump(int *Flag)
{
    switch ((*Flag))
    {
    case 1:

        Sum_Distance += (motor_L_pid.ActValue + motor_R_pid.ActValue) * isr_time * 0.5;
        if (Sum_Distance > 50)
        {
            Sum_Distance = 0;
            (*Flag)++;
        }
        break;
    case 2:
        Sum_Angle += Single_Angle_Get();
        if (Sum_Angle < -40)
        {
            Sum_Angle = 0;
            (*Flag)++;
        }
        break;
    case 3:
        Sum_Angle += Single_Angle_Get();
        if (Sum_Angle < -285)
        {
            Sum_Angle = 0;
            (*Flag)++;
        }
        break;
    case 4:
        Sum_Distance += (motor_L_pid.ActValue + motor_R_pid.ActValue) * isr_time * 0.5;
        if (Sum_Distance > 60)
        {
            Sum_Distance = 0;
            (*Flag) = 0;
            return 1;
        }
    default:
        break;
    }
    return 0;
}
int Obstacle_Jump(int *Flag)
{
    switch (*Flag)
    {
    case 1:
        Sum_Angle += Single_Angle_Get();
        if (Sum_Angle > 30)
        {
            Sum_Angle = 0;
            (*Flag)++;
        }
        break;
    case 2:
        Sum_Distance += (motor_L_pid.ActValue + motor_R_pid.ActValue) * isr_time * 0.5;
        if (Sum_Distance > 30)
        {
            Sum_Distance = 0;
            (*Flag)++;

        }
        break;
    case 3:
        Sum_Angle += Single_Angle_Get();
        if (Sum_Angle < -30)
        {
            P32 = 1;
            Sum_Angle = 0;
            (*Flag)++;
        }
        break;
    case 4:
        Sum_Distance += (motor_L_pid.ActValue + motor_R_pid.ActValue) * isr_time * 0.5;
        if (Sum_Distance > 30)
        {
            Sum_Distance = 0;
            (*Flag)++;
        }
        break;
    case 5:
        Sum_Angle += Single_Angle_Get();
        if (Sum_Angle < -20)
        {
            Sum_Angle = 0;
            (*Flag)++;
        }
        break;
    default:
        break;
    case 6:
        Sum_Distance += (motor_L_pid.ActValue + motor_R_pid.ActValue) * isr_time * 0.5;
        if (Sum_Distance > 45)
        {
            Sum_Distance = 0;
            (*Flag) = 0;
            return 1 ;
        }

    }
    return 0;
}