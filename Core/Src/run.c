#include "run.h"
#include "wifi_fun.h"

#include "dht11.h"
#include "fan.h"
#include "tim.h"
#include "cmd_link.h"
#include "special_power.h"
#include "wifi.h"

#include "mcu_api.h"
#include "gpio.h"

 


//static CProcess1 cprocess;
RUN_T run_t; 


 /**********************************************************************
	*
	*Functin Name: void RunCommand_Order(void)
	*Function : be check key of value 
	*Input Ref:  key of value
	*Return Ref: NO
	*
**********************************************************************/
void RunCommand_MainBoard_Handler(void)
{
    
    static uint8_t power_just_on;


	switch(run_t.RunCommand_Label){

       case POWER_ON:
	    PowerOn(); //PowerOn_Host();
	   	run_t.RunCommand_Label= UPDATE_TO_PANEL_DATA;
	  
	    Display_DHT11_Value(&DHT11);
		HAL_Delay(2);
		run_t.gTimer_60s=0; //dht11 datat send displayPanel 
		if(wifi_work_state == WIFI_CONN_CLOUD){
			  SendWifiData_To_Cmd(0x01); //wifi has been link TuYa cloud

		}
	   	
	   break;

	   case POWER_OFF:
	   PowerOff();//PowerOff_Host();
	   run_t.gPower_flag=POWER_OFF;
	   run_t.gFan_continueRun =1;
	     
	   run_t.gPower_flag =POWER_OFF;
		
       run_t.RunCommand_Label=POWER_OFF_FAN_STATE;

	   break;

	   case UPDATE_TO_PANEL_DATA:
	     if(run_t.gTimer_senddata_panel >30 && run_t.gPower_On==POWER_ON){ //300ms
	   	    run_t.gTimer_senddata_panel=0;
	         MainBord_Template_Action_Handler();
		    
	     }
		 if(run_t.gTimer_60s > 0){
		    run_t.gTimer_60s=0;
            Display_DHT11_Value(&DHT11);

		 }
		 
	   	
	   break;

	   case POWER_OFF_FAN_STATE: //5
            if(run_t.gFan_continueRun ==1 && run_t.gPower_flag == POWER_OFF){
          
                if(run_t.gFan_counter < 60){
          
                       FAN_CCW_RUN();
                  }       

	           if(run_t.gFan_counter > 59){
		           
				   run_t.gFan_counter=0;
				
				   run_t.gFan_continueRun++;
				   FAN_Stop();
	           }
	       }

	   break;

	   default:
	   break;




	}


   if((run_t.gTimer_1s>30 && run_t.gPower_flag == POWER_ON)||power_just_on < 10){
    	power_just_on ++ ;
		run_t.gTimer_1s=0;
		 Display_DHT11_Value(&DHT11);

	}

    if(run_t.gPlasma==0 && run_t.gDry==0 && run_t.gPower_flag ==POWER_ON && run_t.gFan_continueRun ==1){

              if(run_t.gFan_counter < 60){
          
                       FAN_CCW_RUN();
                  }       

	           if(run_t.gFan_counter > 59){
		           
				   run_t.gFan_counter=0;
				
				   run_t.gFan_continueRun++;
				   FAN_Stop();
	           }

	     }

}



    
