#include "interrupt_manager.h"
#include "bsp.h"


/*****************************************************************************************
  *
  * Function Name: void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
  * Function: Tim3 interrupt call back function
  * Tim3 timer :timing time 10ms
  * 
*****************************************************************************************/
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{

    static uint8_t tm0 ,tm1;
    if(htim->Instance==TIM3){
	 tm0 ++ ;
    
	 run_t.gTimer_senddata_panel++;
   
	   if(tm0 == 100){//100ms *10 = 1000ms =1s
       tm0 =0;
        tm1++;
      
	   wifi_t.gTimer_beijing_time++;

       wifi_t.gTimer_get_wifi_state++;
	   wifi_t.gTimer_1s++;
	   run_t.gTimer_dogfood_times ++;
	   if(run_t.gFan_continueRun ==1){
           run_t.gFan_counter++;
		 
	   }

      if(tm1 > 59){ // 1minute 
         tm1=0;
         run_t.gTimer_60s++;
         wifi_t.gTimer_up_dht11 ++;
		 wifi_t.gTimer_gmt++ ;
         
      }

	 }
  }

} 







