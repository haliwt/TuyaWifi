#include "bsp_fan.h"
#include "main.h"
#include "tim.h"
#include "run.h"
#include "delay.h"



void Fan_CCW_Run_Max(void)
{
   FAN_CW_SetLow();
   MX_TIM16_Init(9,10); //100KHZ,duty =100%
   HAL_TIM_PWM_Start(&htim16,TIM_CHANNEL_1);
  
  
}

void Fan_CCW_Run_Min(void)
{
    FAN_CW_SetLow();
    MX_TIM16_Init(99,50); //10KHZ,duty =50%
    HAL_TIM_PWM_Start(&htim16,TIM_CHANNEL_1);
   
}

 
void FAN_Stop(void)
{
  FAN_CW_SetLow(); //brake
  
  HAL_TIM_PWM_Stop(&htim16,TIM_CHANNEL_1);
    
}




//void FAN_CCW_RUN(void)
//{
//   FAN_CW_SetLow();
//   FAN_CCW_SetHigh();
//  
//}
//
//void FAN_Stop(void)
//{
//    FAN_CCW_SetLow(); //brake
//    FAN_CW_SetLow(); //brake
//}








void Fan_Slowly_Speed(void)
{
    static uint16_t fan_speed;
	fan_speed ++ ;
	FAN_CW_SetLow();
	
	if(fan_speed < 100){
	   Fan_CCW_Run_Max();//FAN_CCW_SetHigh(); //Run fan
    }

	if(fan_speed > 99  && fan_speed <  106){
  
	  Fan_CCW_Run_Min();///FAN_CCW_SetLow(); //brake

	}

	if(fan_speed > 106|| fan_speed==106) fan_speed =0;
	
}


