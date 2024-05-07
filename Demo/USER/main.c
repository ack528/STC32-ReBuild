#include "headfile.h"
//float cs_motor_l_pid[3]={50,10.5,15};//float cs_motor_r_pid[3]={50,10,0};
//float cs_motor_r_pid[3]={50,10.5,15};
//float cs_dir_loop_pid[3]={160,0,300};
int adc_value[8] = {0};
int i = 0;
float sum = 0;
uint8 uart_delay=0;
int main()
{
    board_init();
    pit_timer_ms(TIM_1, 5);
    printf("1111\r\n");
    pit_timer_ms(TIM_4, 2);
    NVIC_SetPriority(TIMER1_IRQn, 2);
    NVIC_SetPriority(UART4_IRQn, 3);
    InitPID();
    for (i = 0; i < 10; i++)
    {
        delay_ms(200);
    }
    EnableGlobalIRQ(); // ¿ªÆô×ÜÖÐ¶Ï
    printf("3\r\n");
    motor_L_pid.SetValue = 30;
    motor_R_pid.SetValue = 30;
    printf("4\r\n");
    while (1)
    {
        if (TIM1_Flag)
        {

            P72 = 1;
            P52 = 0;
//            dl1b_get_distance();
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
////              printf("*****\r\n");
//                case Track:
//                    P67 = 0;
//                    Track_Action(adc_value);

//                    break;
//                case Big_Circ_Left:
//                case Small_Circ_Left:
//                    Circ_Left_Action(adc_value);
//                    break;
//                case Big_Circ_Right:
//                case Small_Circ_Right:
//                    P67 = 1;
//                    Circ_Right_Action(adc_value);
//                    break;
//                case Obstacle:
////            	 printf(".....\r\n");
//                    Obstacle_Action();
//                    break;
//                case Stop:
//                    Stop_Action();
//                }
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

						uart_delay++;
						if(uart_delay>4)
						{
							uart_delay = 0;
							printf("%f,%f,%f,%f\r\n", motor_L_pid.ActValue, motor_R_pid.ActValue, 
											motor_L_pid.SetValue, motor_R_pid.SetValue);
						}
//printf("%d\r\n",flag_turn);
            TIM1_Flag = 0;
            P72 = 0;
        }

    }
}
