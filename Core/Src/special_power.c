#include "special_power.h"
#include "bsp.h"



void SetPowerOn_ForDoing(void)
{
    Buzzer_KeySound();
    run_t.gFan_counter=0;
    run_t.gPower_flag = POWER_ON; //turn on power
    run_t.gFan_continueRun =0;
    run_t.gPower_On=POWER_ON;

	run_t.gDry =1;
	run_t.gFan_counter = 100;
	run_t.gPlasma =1;

  
	//FAN_CCW_RUN();
	Fan_CCW_Run_Max();
    PLASMA_SetHigh(); //
    HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);//ultrasnoic ON 
    PTC_SetHigh();
	
    
    

}

void SetPowerOff_ForDoing(void)
{
     Buzzer_KeySound();//Buzzer_KeySound();
	run_t.gPower_flag = POWER_OFF;
	run_t.gFan_counter=0;
	run_t.gFan_continueRun =1; //the fan still run 60s
	run_t.gPower_On=POWER_OFF;
    wifi_t.wifi_power=0;
    wifi_t.wifiPowerOn_flag =0;

	
  

    PLASMA_SetLow(); //
	HAL_TIM_PWM_Stop(&htim1, TIM_CHANNEL_1);//ultrasnoic ON 
	PTC_SetLow();
	FAN_Stop();

}


/**********************************************************************
	*
	*Functin Name: vaoid MainBord_Template_Action_Handler(void)
	*Function : main board self function
	*Input Ref:  NO
	*Return Ref: NO
	*
**********************************************************************/
void  MainBord_Template_Action_Handler(void)
{
   if(run_t.gDry == 1){
		 if(run_t.set_wind_speed_value < 67){
            Fan_CCW_Run_Min();//Fan_Slowly_Speed();
		 }
		 else
		 	Fan_CCW_Run_Max();
	
	        PTC_SetHigh();
	     
	}
	else{
	   PTC_SetLow();

	}
	//kill
	if(run_t.gPlasma == 1){
		 if(run_t.set_wind_speed_value < 67){
            Fan_CCW_Run_Min();//Fan_Slowly_Speed();
		 }
		 else
		 Fan_CCW_Run_Max();	//FAN_CCW_RUN();
	     PLASMA_SetHigh();
	}
	else{

		PLASMA_SetLow();
	}
	//driver bug
	if(run_t.gUlransonic ==1){
		 if(run_t.set_wind_speed_value < 67){
            Fan_CCW_Run_Min();//Fan_Slowly_Speed();
		 }
		 else
		 	Fan_CCW_Run_Max();//FAN_CCW_RUN();
	 
		HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);//ultrasnoic ON 
	}
	else{
	  HAL_TIM_PWM_Stop(&htim1, TIM_CHANNEL_1);//ultrasnoic off

	}

	if(run_t.gPlasma ==0 && run_t.gDry==0){

        run_t.gFan_counter=0;
		run_t.gFan_continueRun=1;        

	}



}

