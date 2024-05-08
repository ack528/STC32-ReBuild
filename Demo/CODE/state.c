#include "headfile.h"
int state_lead = 0;
int Flag_Circ = 0;				//圆环不同阶段的指针
int Flag_Obstacle = 0;
int flag_turn = 0;				//直路元素的指针
float Sum_Distance = 0, Sum_Angle = 0;
char state[30] = {Track, Small_Circ_Right, Track, Track, Track, Track, Stop};	//赛道元素顺序
void state_detect(int *temp)
{
    adc_get(temp);
    switch (state[state_lead])		//默认值为0 进track 
    {
				case Track:
						if (Track_Jump(temp))							 		state_lead++;
						break;
				case Big_Circ_Left:
						if (Big_Circ_Left_Jump(&Flag_Circ)) 	state_lead++;
						break;
				case Big_Circ_Right:
						if (Big_Circ_Right_Jump(&Flag_Circ))	state_lead++;
						break;
				case Small_Circ_Left:
						if (Small_Circ_Left_Jump(&Flag_Circ))	state_lead++;
						break;
				case Small_Circ_Right:
						if (Small_Circ_Right_Jump(&Flag_Circ))state_lead++;
						break;
				case Obstacle:
						if (Obstacle_Jump(&Flag_Obstacle))		state_lead++;
						break;

				default:
						break;
    }
}
int Track_Jump(int *temp)	//只要检测到元素就返回1
{
    switch (state[state_lead + 1])	//检测第二个元素
    {
				case Big_Circ_Left:														//检测到圆环就置位，然后返回
						if (temp[0] > 1200 && temp[3] > 1000)
						{
								Flag_Circ = 1;
								return 1;
						}
						break;
				case Small_Circ_Left:
						if (temp[0] > 1200 && temp[3] > 1000)
						{
								Flag_Circ = 1;
								return 1;
						}
						break;
				case Big_Circ_Right:
						if (temp[3] > 1200 && temp[0] > 1000)
						{
								Flag_Circ = 1;
								return 1;
						}
						break;
				case Small_Circ_Right:
		//      if((temp[0]+temp[3]>3000)&&(temp[1]+temp[2]>2000))
						if (temp[3] > 1200 && temp[0] > 1000)
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
		
//    switch (flag_turn)				//没检测到元素，就根据直道元素指针执行操作							
//    {
//				case cross:						//十字
//						Sum_Distance += (motor_L_pid.ActValue + motor_R_pid.ActValue) * isr_time * 0.5;
//						if (Sum_Distance > 40)
//						{
//								Sum_Distance = 0;
//								flag_turn = 0;
//						}
//						return 0;
//						break;
//				case right_angle:
//						break;
//				case normal:
//						break;
//				default :
//						break;
//    }

//  if(max_count(temp[5],temp[6])>600&&min_count(temp[5],temp[6])>600&&temp[4]>800&&temp[7]>800)
//  {
//      flag_turn=cross;
//      printf("%d,%d,%d,%d,%d,%d,%d,%d\r\n",adc_value[0],adc_value[1],adc_value[2],
//									adc_value[3],adc_value[4],adc_value[5],adc_value[6],adc_value[7]);
//  }
		
//    if (abs(temp[5] - temp[6]) > 400)
//    {
//        flag_turn = right_angle;
//    }
//    else
//    {
//        flag_turn = normal;
//    }
//    return 0;
}
int Big_Circ_Left_Jump(int *Flag)		//走完所有阶段才会返回1，才会继续检测下一个元素
{
    switch (*Flag)
    {
    case 1:
        Sum_Distance += (motor_L_pid.ActValue + motor_R_pid.ActValue) * isr_time * 0.5;//计算实例里程数
        if (Sum_Distance > 50)
        {

            Sum_Distance = 0;
            (*Flag)++;
        }
        break;
    case 2:
        Sum_Angle += Single_Angle_Get();
        if (Sum_Angle > 35)
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

int Big_Circ_Right_Jump(int *Flag)
{
    switch (*Flag)
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
        if (Sum_Angle < -35)
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
//      printf("00000000000000000000\r\n");
        Sum_Distance += (motor_L_pid.ActValue + motor_R_pid.ActValue) * isr_time * 0.5;
        if (Sum_Distance > 50)
        {
            Sum_Distance = 0;
            (*Flag)++;
        }

        break;
    case 2:

        Sum_Angle += Single_Angle_Get();
//      printf("%f\r\n",Sum_Angle);
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
//  printf("%d\r\n",(*Flag));
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
//      printf("%f\r\n",Sum_Distance);
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
//      printf("%f\r\n",Sum_Distance);
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
//int Ramp_Jump(int *Flag)
//{
//
//}