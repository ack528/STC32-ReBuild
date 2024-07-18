#include "headfile.h"
#include "state.h"
int state_lead = 0;
int Flag_Long_Track = 1; 				//长直道
int Flag_Slow_Track = 1;				//慢速路
int Flag_Circ = 0;              //圆环
int Flag_Obstacle = 0;					//障碍
int flag_turn = 0;             
float Sum_Distance = 0, Sum_Angle = 0;

//char state[30] = {Track, Obstacle, Track, Big_Circ_Right, Track, Small_Circ_Left ,
//									Track, Ramp, Track, Track, Stop};  //赛道元素顺序

char state[30] = {Long_Track, Track, Small_Circ_Left,
									Long_Track, Track, Ramp,
									Long_Track,	Slow_Track, Long_Track, Track, Obstacle,
															Track, Big_Circ_Right,
															Track, Track, 
									Stop};  //赛道元素顺序

void state_detect(int *temp)
{
    adc_get(temp);
    switch (state[state_lead]) 
    {
				case Track:
						if (Track_Jump(temp))                   state_lead++;
						break;
				case Long_Track:
						if(Long_Track_Jump())										state_lead++;
						break;
				case Slow_Track:
						if(Slow_Track_Jump())										state_lead++;
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
				case Ramp:
						if (Ramp_Jump())      									state_lead++;
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
						if (temp[0] > 1300 && temp[4] > 1100)
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
						if (temp[4] > 1300 && temp[0] > 1100)
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
						if (dl1b_distance_mm < 1000)
						{
								Flag_Obstacle = 1;
								return 1;
						}
						break;
				case Ramp:
						if (temp[2] > 1700)
						{
								return 1;
						}
						break;
				case Stop:
						return 1;
						break;
				default:
						break;
    }
    return 0;
}
int Long_Track_Jump(void)
{
	 switch (Flag_Long_Track)
    {
			case 1:
					Sum_Distance += (motor_L_pid.ActValue + motor_R_pid.ActValue) * isr_time * 0.5;
					if (Sum_Distance > 200)
					{
							Sum_Distance = 0;
							Flag_Long_Track++;
							return 1;
					}
					break;
			case 2:
					Sum_Distance += (motor_L_pid.ActValue + motor_R_pid.ActValue) * isr_time * 0.5;
					if (Sum_Distance > 200)
					{
							Sum_Distance = 0;
							Flag_Long_Track++;
							return 1;
					}
					break;
			case 3:
					Sum_Distance += (motor_L_pid.ActValue + motor_R_pid.ActValue) * isr_time * 0.5;
					if (Sum_Distance > 800)
					{
							Sum_Distance = 0;
							Flag_Long_Track++;
							return 1;
					}
					break;
			case 4:
					BEEP = 1;
					Sum_Distance += (motor_L_pid.ActValue + motor_R_pid.ActValue) * isr_time * 0.5;
					if (Sum_Distance > 650)
					{		
							BEEP = 0;
							Sum_Distance = 0;
							Flag_Long_Track++;
							return 1;
					}
					break;
			default:
					break;
    }
	return 0;
}

int Slow_Track_Jump(void)
{
	 switch (Flag_Slow_Track)
    {
			case 1:
					Sum_Distance += (motor_L_pid.ActValue + motor_R_pid.ActValue) * isr_time * 0.5;
					if (Sum_Distance > 600)
					{
							Sum_Distance = 0;
							Flag_Slow_Track++;
							return 1;
					}
					break;
			case 2:
					Sum_Distance += (motor_L_pid.ActValue + motor_R_pid.ActValue) * isr_time * 0.5;
					if (Sum_Distance > 200)
					{
							Sum_Distance = 0;
							Flag_Slow_Track++;
							return 1;
					}
					break;
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
    switch ((*Flag))
    {
    case 1:
				BEEP = 1;
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
        if (Sum_Angle > 285)
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
            (*Flag)++;
        }
				break;
		case 5:
				Sum_Distance += (motor_L_pid.ActValue + motor_R_pid.ActValue) * isr_time * 0.5;
				if (Sum_Distance > 100)
				{
						BEEP = 0;
						Sum_Distance = 0;
						(*Flag) = 0;
						return 1;
				}
				break;
    default:
        break;
    }
    return 0;
}

int Big_Circ_Right_Jump(int *Flag)
{
    switch ((*Flag))
    {
    case 1:
				BEEP = 1;
        Sum_Distance += (motor_L_pid.ActValue + motor_R_pid.ActValue) * isr_time * 0.5;
        if (Sum_Distance > 60)
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
        if (Sum_Distance > 80)
        {
            Sum_Distance = 0;
            (*Flag)++;
        }
				break;
		case 5:
				Sum_Distance += (motor_L_pid.ActValue + motor_R_pid.ActValue) * isr_time * 0.5;
				if (Sum_Distance > 100)
				{
						BEEP = 0;
						Sum_Distance = 0;
						(*Flag) = 0;
						return 1;
				}
				break;
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
				BEEP = 1;
        Sum_Distance += (motor_L_pid.ActValue + motor_R_pid.ActValue) * isr_time * 0.5;
        if (Sum_Distance > 50)
        {
            Sum_Distance = 0;
            (*Flag)++;
						
        }
        break;
    case 2:
        Sum_Angle += Single_Angle_Get();
        if (Sum_Angle > 24)
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
				if (Sum_Distance > 65)
				{
						BEEP = 0;
						Sum_Distance = 0;
						(*Flag) = 0;
//						state_lead = 10;
						return 1;
				}
				break;
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
				BEEP = 1;
        Sum_Distance += (motor_L_pid.ActValue + motor_R_pid.ActValue) * isr_time * 0.5;
        if (Sum_Distance > 50)
        {
            Sum_Distance = 0;
            (*Flag)++;
						
        }
        break;
    case 2:
        Sum_Angle += Single_Angle_Get();
        if (Sum_Angle <-24)
        {
            Sum_Angle = 0;
            (*Flag)++;
						
        }
        break;
    case 3:
        Sum_Angle += Single_Angle_Get();
        if (Sum_Angle <-295)
        {
            Sum_Angle = 0;
            (*Flag)++;
//						state_lead = 10;
        }
        break;
		case 4:
				Sum_Distance += (motor_L_pid.ActValue + motor_R_pid.ActValue) * isr_time * 0.5;
				if (Sum_Distance > 65)
				{
						BEEP = 0;
						Sum_Distance = 0;
						(*Flag) = 0;
//						state_lead = 10;
						return 1;
				}
				break;
    default:
        break;
    }
    return 0;
}

// 30 15 -50 100 30
int Obstacle_Jump(int *Flag)
{
    switch (*Flag)
    {
    case 1:
				BEEP = 1;
        Sum_Angle += Single_Angle_Get();
        if (Sum_Angle > 30)
        {
            Sum_Angle = 0;
            (*Flag)++;
//						state_lead = 10;
        }
				
        break;
    case 2:
        Sum_Distance += (motor_L_pid.ActValue + motor_R_pid.ActValue) * isr_time * 0.5;
        if (Sum_Distance > 20)
        {
            Sum_Distance = 0;
            (*Flag)++;
//						state_lead = 10;
        }
        break;
    case 3:
        Sum_Angle += Single_Angle_Get();
        if (Sum_Angle < -50)
        {
            P32 = 1;
            Sum_Angle = 0;
            (*Flag)++;
//						state_lead = 10;
        }
        break;
    case 4:
        Sum_Distance += (motor_L_pid.ActValue + motor_R_pid.ActValue) * isr_time * 0.5;
        if (Sum_Distance > 90)
        {
            Sum_Distance = 0;
            (*Flag)++;
//						state_lead = 10;
        }
        break;
    case 5:
        Sum_Angle += Single_Angle_Get();
        if (Sum_Angle > 10)							
        {
						BEEP = 0;
            Sum_Angle = 0;
            (*Flag)++;
						state_lead = 10;
						return 1 ;
        }
        break;
    case 6:
        Sum_Distance += (motor_L_pid.ActValue + motor_R_pid.ActValue) * isr_time * 0.5;
        if (Sum_Distance > 30)
        {
            Sum_Distance = 0;
            (*Flag) = 0;
        }
		default:
        break;
    }
    return 0;
}
int Ramp_Jump(void)
{
	Sum_Distance += (motor_L_pid.ActValue + motor_R_pid.ActValue) * isr_time * 0.5;
	BEEP = 1;
	if (Sum_Distance > 180)
	{
			BEEP = 0;
//			state_lead = 10;
			return 1;	
	}
	else 
			return 0;
}