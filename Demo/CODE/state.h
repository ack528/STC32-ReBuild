#ifndef _STATE_H
#define _STATE_H
extern char state[30];
extern int state_lead;
extern int Flag_Circ;
extern int Flag_Obstacle;
extern int flag_turn;
extern int Flag_Right_Angle;       //直角不同阶段的指针


void state_detect(int* temp);
int Track_Jump(int* adc_value);
int Big_Circ_Left_Jump(int* Flag);
int Small_Circ_Left_Jump(int* Flag);
int Big_Circ_Right_Jump(int* Flag);
int Small_Circ_Right_Jump(int* Flag);
int Obstacle_Jump(int *flag);
int Ramp_jump(void);
uint8 stop_jump(void);

enum element
{
	Stop=0,
	Start=1,
	Track=2,
	Bend=3,
	Big_Circ_Left=4,
	Big_Circ_Right=5,
	Small_Circ_Left=6,
	Small_Circ_Right=7,
	Obstacle=8,
	Ramp=9,
	Garage_Out=10,
	Garage_In=11,
};
enum Track
{
	cross=1,
	right_angle=2,
	normal=3,
};
#endif