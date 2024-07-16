#include "headfile.h"
extern float speed_goal;
float error = 0;
int count = 0;
void Track_Action(int *temp)//ֱ��
{
    error = error_get(temp, flag_turn);
    speed_goal = speed_section(error, state[state_lead]);
    Dir_Loop(error, speed_goal, flag_turn);
}

void Circ_Left_Action(int *temp)//��
{
    error = error_get(temp, flag_turn);
    switch (Flag_Circ)
    {
    case 1:
        speed_goal = speed_section(error, state[state_lead]);		//�޸�Ŀ���ٶȣ�ûд�꣬Ĭ�Ϸ���ֵ�̶�
        Dir_Loop(error, speed_goal, flag_turn);
        break;
    case 2:
        motor_L_pid.SetValue = 0;
        motor_R_pid.SetValue = speed_goal * 1.2;
        break;
    case 3:
        speed_goal = speed_section(error, state[state_lead]);		//�޸�Ŀ���ٶȣ�ûд�꣬Ĭ�Ϸ���ֵ�̶�
        Dir_Loop(error, speed_goal, flag_turn);
        break;
    case 4:
        motor_L_pid.SetValue = speed_goal;
        motor_R_pid.SetValue = speed_goal;
        break;
		case 5:
				Dir_Loop(error, speed_goal, flag_turn);
        break;
    }
}


void Circ_Right_Action(int *temp)//�һ�
{
    error = error_get(temp, flag_turn);
    speed_goal = speed_section(error, state[state_lead]);
    switch (Flag_Circ)
    {
    case 1:
        Dir_Loop(error, speed_goal, flag_turn);
        break;
    case 2:
        motor_L_pid.SetValue = speed_goal * 2;
        motor_R_pid.SetValue = 0;
        break;
    case 3:
        speed_goal = speed_section(error, state[state_lead]);
        Dir_Loop(error, speed_goal, flag_turn);
        break;
    case 4:
        motor_L_pid.SetValue = speed_goal;
        motor_R_pid.SetValue = speed_goal;
        break;
		case 5:
				Dir_Loop(error, speed_goal, flag_turn);
        break;
    }
}


void Obstacle_Action(void)
{
//  printf("in\r\n");
    switch (Flag_Obstacle)
    {
    case 1:
//  		error=0.3;
        speed_goal = speed_section(error, state[state_lead]);
//  		Dir_Loop(error,speed_goal,flag_turn);
        motor_L_pid.SetValue = speed_goal * 0;
        motor_R_pid.SetValue = speed_goal * 2;
        break;
    case 2:
//  		error=-0.3;
        speed_goal = speed_section(error, state[state_lead]);
//  		Dir_Loop(error,speed_goal,flag_turn);
        motor_L_pid.SetValue = speed_goal * 1;
        motor_R_pid.SetValue = speed_goal * 1;
        break;
    case 3:
        speed_goal = speed_section(error, state[state_lead]);
        motor_L_pid.SetValue = speed_goal * 2;
        motor_R_pid.SetValue = speed_goal * 0;
        break;
    case 4:
        speed_goal = speed_section(error, state[state_lead]);
        motor_L_pid.SetValue = speed_goal * 1;
        motor_R_pid.SetValue = speed_goal * 1;
        break;
    case 5:
        speed_goal = speed_section(error, state[state_lead]);
        motor_L_pid.SetValue = speed_goal * 0;
        motor_R_pid.SetValue = speed_goal * 2;
        break;
    case 6:
        P32 = 0;
        speed_goal = speed_section(error, state[state_lead]);
        motor_L_pid.SetValue = speed_goal * 1;
        motor_R_pid.SetValue = speed_goal * 1;
        break;
    }
//  		printf("%d\r\n",Flag_Obstacle);
}


void Stop_Action()//ͣ��
{
    motor_L_pid.SetValue = 0;
    motor_R_pid.SetValue = 0;
}


void beep_on()//��������
{
    P67 = 1;
}
void beep_off()//��������
{
    P67 	= 0;
    count = 0;
}