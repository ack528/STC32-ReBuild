#ifndef _PID_H
#define _PID_H
#define duty_max  9999
#define duty_min  -9999

typedef struct
{
    float SetValue; // ����ֵ �ο�ֵ
    float ActValue; // ʵ��ֵ
    float KP; // ��������
    float KI; // ��������
    float KD; // ΢������
    float ek; // �������
    float ek_1; // ��һ��
    float ek_2; // ���ϴ�
    float ek_sum; // ����ۻ�
    float Sum_max; // ����ۺ�����
    float Sum_min; // ����ۺ�����
    float PIDmax; // max limit
    float PIDmin; // min limit
    float PIDout; // output
}PID;
extern PID motor_L_pid;
extern PID motor_R_pid;
extern PID speed_ctrl_pid;
extern PID dir_loop_pid;
void pid_set(float *arr,PID *pid);
float PID_Control_Inc(PID* pid,int flag);
float PID_Control_Pos(PID* pid,int flag);
void InitPID(void);
#endif