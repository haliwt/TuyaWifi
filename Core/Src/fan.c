#include "fan.h"
#include "main.h"
#include "tim.h"
#include "run.h"
#include "delay.h"


void Buzzer_KeySound(void)
{

  unsigned int m=200;//80
	while(m--){

    HAL_GPIO_TogglePin(BUZZER_GPIO,BUZZER_PIN);//BEEP=!BEEP;
    //delay_us(600);
    delay_us(500);//460//__delay_us(300);;//__delay_us(800);//delayUS(300);
   
    }
       
}




void FAN_CCW_RUN(void)
{
   FAN_CW_SetLow();
   FAN_CCW_SetHigh();
  
}

void FAN_Stop(void)
{
    FAN_CCW_SetLow(); //brake
    FAN_CW_SetLow(); //brake
}

void ShutDown_AllFunction(void)
{
	
	PLASMA_SetLow(); //
	HAL_TIM_PWM_Stop(&htim1, TIM_CHANNEL_1);//ultrasnoic ON 
	PTC_SetLow();
	FAN_Stop();



}

void Rat_Control_Function(uint8_t sel)
{
    if(sel==0){//open 
		 FAN_CCW_RUN();
		// PLASMA_SetHigh();
		 HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);//ultrasnoic ON 

	}
	else{ //close

			
		HAL_TIM_PWM_Stop(&htim1, TIM_CHANNEL_1);//ultrasnoic off
		

	}



}

void UV_Function(uint8_t sel)
{

	if(sel==0){//open 
			 FAN_CCW_RUN();
			 PLASMA_SetHigh();
			
	
		}
		else{ //close
	
				
			PLASMA_SetLow();
			
	
		}



}

void Dry_Function(uint8_t sel)
{
   if(sel ==0){

  
		FAN_CCW_RUN();
		PTC_SetHigh();

   }
   else{

       PTC_SetLow();

   }

}

void Fan_Slowly_Speed(void)
{
    static uint16_t fan_speed;
	fan_speed ++ ;
	FAN_CW_SetLow();
	
	if(fan_speed < 100){
	   FAN_CCW_SetHigh(); //Run fan
    }

	if(fan_speed > 99  && fan_speed <  106){
  
	  FAN_CCW_SetLow(); //brake

	}

	if(fan_speed > 106|| fan_speed==106) fan_speed =0;
	
}


