	#include "headfile.h"
//float cs_motor_l_pid[3]={50,10.5,15};//float cs_motor_r_pid[3]={50,10,0};
//float cs_motor_r_pid[3]={50,10.5,15};
//float cs_dir_loop_pid[3]={160,0,300};
int adc_value[8] = {0};

int i = 0;
float sum = 0;
uint8 uart_delay = 0;
int main()
{
    board_init();
    pit_timer_ms(TIM_1, 5);
    printf("pit init\r\n");
    pit_timer_ms(TIM_4, 2);
    NVIC_SetPriority(TIMER1_IRQn, 2);
    NVIC_SetPriority(UART4_IRQn, 3);
    InitPID();
    for (i = 0; i < 10; i++)
    {
        delay_ms(200);
    }
    EnableGlobalIRQ(); // 开启总中断
    printf("all init\r\n");
    motor_L_pid.SetValue = 160; //还需要更改speed.c中的速度和speed_goal
    motor_R_pid.SetValue = 160;
    printf("motor pid set value\r\n");
    while (1)
    {
        if (TIM1_Flag)
        {
            P52 = 0;
//          dl1b_get_distance();
            imu660ra_get_gyro();
//            if (dl1b_distance_mm < 300 && Flag_Obstacle == 0)
//            {
//                state_lead = 12;
//                Stop_Action();
//            }
//            else
//            {
//                state_detect(adc_value);
//                switch (state[state_lead])
//                {
//										case Track:
//													P67 = 0;
//													Track_Action(adc_value);
//													break;
//										case Big_Circ_Left:
//													P67 = 1;
//													Circ_Left_Action(adc_value);
//													break;
//										case Small_Circ_Left:
//													Circ_Left_Action(adc_value);
//													break;
//										case Big_Circ_Right:
//													Circ_Right_Action(adc_value);
//													break;
//										case Small_Circ_Right:
//													Circ_Right_Action(adc_value);
//													break;
//										case Obstacle:
//													printf(".....\r\n");
//													Obstacle_Action();
//													break;
//										case Stop:
//													Stop_Action();
//                }
									adc_get(adc_value);
//            }
            //i+=1;
            ////if(i%400==0)
            ////{
            ////motor_R_pid.SetValue=0;
            ////motor_L_pid.SetValue=0;
            ////}
            ////else
            //  if(i%200==0)
            //{
            //  motor_L_pid.SetValue+=15;
            //  motor_R_pid.SetValue+=15;
            //}
            //else if(i>1800)
            //{
            //motor_R_pid.SetValue=0;
            //motor_L_pid.SetValue=0;
            //}
//					lcd_showint32(0,0,(int)state_lead,4);
            uart_delay++;
            if (uart_delay > 4)
            {
                uart_delay = 0;
                printf("%f,%f,%f,%f\r\n", motor_L_pid.ActValue, motor_R_pid.ActValue,
																					motor_L_pid.SetValue, motor_R_pid.SetValue);
//								printf("%d,%d,%d,%d\r\n", adc_value[0], adc_value[1],
//																					adc_value[2], adc_value[3]);
            }
//					printf("%d\r\n",flag_turn);
            TIM1_Flag = 0;
            P52 = 1;
        }

    }
}
