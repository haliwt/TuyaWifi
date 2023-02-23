#include "run.h"
#include "wifi_fun.h"

#include "dht11.h"
#include "fan.h"
#include "tim.h"
#include "cmd_link.h"
#include "special_power.h"
#include "wifi.h"

#include "mcu_api.h"

 


//static CProcess1 cprocess;
RUN_T run_t; 


 
/**********************************************************************
*
*Function Name:void Decode_RunCmd(void)
*Function: receive usart touchkey of command 
*Input Ref:NO
*Return Ref:NO
*
**********************************************************************/
void Decode_RunCmd(void)
{

 uint8_t cmdType_1=inputCmd[0],cmdType_2 = inputCmd[1];
    
  switch(cmdType_1){
  
      case 'P': //power 


         Single_ReceiveCmd(cmdType_2);  
        
       break;

	  case 'W': //wifi-function
	      if(run_t.gPower_flag==POWER_ON){
	      if(cmdType_2==1){
              //fast led blink 
			  Buzzer_KeySound();	
              wifi_t.wifiRun_Cammand_label = wifi_link_tuya_cloud;//2 
		   }
		   else if(cmdType_2==0){
                
                Buzzer_KeySound(); 
		   }
		   else if(cmdType_2==0x14){
               // run_t.gModel =2; //turn off
                Buzzer_KeySound();
            }
            else if(cmdType_2==0x04){
               // run_t.gModel =1;  //turn on
                Buzzer_KeySound();
            }
           
           
        }
       
	   break;

	    case 'C':
           if(run_t.gPower_flag==POWER_ON){
               Single_ReceiveCmd(cmdType_2); 
              
           }
     
         
      break;

	  case 'M': //temperature value
	  	if(run_t.gPower_flag==POWER_ON){
              
             run_t.set_temperature_value = cmdType_2;
			if(wifi_work_state == WIFI_CONN_CLOUD)
		    	mcu_dp_value_update(DPID_SET_TEMPERATURE,cmdType_2); //VALUE型数据上报;
			   
         }
	  

	  break;

	  case 'T':
		if(run_t.gPower_flag==POWER_ON){
              
             wifi_t.setTimesValue = cmdType_2;
			if(wifi_work_state == WIFI_CONN_CLOUD)
		    	mcu_dp_value_update(DPID_SET_TIMGING,cmdType_2); //VALUE型数据上报;
			 
         }
	  
	      


	  break;

	  


	  case 'Z' ://buzzer sound 
	    if(run_t.gPower_flag==POWER_ON){

		    if(cmdType_2== 'Z'){//turn off AI
			    Buzzer_KeySound();
			}
			 
		
		}
     
	    break;
	  /******************************************************/
  	}
}
/**********************************************************************
	*
	*Functin Name: void Single_ReceiveCmd(uint8_t cmd)
	*Function : resolver is by usart port receive data  from display panle  
	*Input Ref:  usart receive data
	*Return Ref: NO
	*
**********************************************************************/
void Single_ReceiveCmd(uint8_t cmd)
{
 

  
	switch(cmd){

    case 0x00: //power off
           Buzzer_KeySound();
		  run_t.gPower_On=POWER_OFF;
	      run_t.gPower_flag =POWER_OFF;
		  run_t.RunCommand_Label=POWER_OFF;
		
		  wifiUpdate_Power_Status(0);
		 
           
    break;

    case 0x01: // power on
         Buzzer_KeySound();
		run_t.gPower_On=POWER_ON;
	    run_t.gPower_flag=POWER_ON;
	
		wifi_t.wifi_power =POWER_ON; //WI.EDTI 2022.09.02
	    wifiUpdate_Power_Status(1);
	
         
		   
     break;

	 	 //dry key
     case 0x12: //PTC turn on
       if( run_t.gPower_flag == POWER_ON){
         run_t.gDry = 1;
         run_t.gFan_continueRun =0;
	   if(wifi_work_state == WIFI_CONN_CLOUD)
		  wifiUpdate_Dry_Status(1);

		  	
	
       }

	break;

     case 0x02: //PTC turn off
	if( run_t.gPower_flag == POWER_ON){
		run_t.gDry =0;
		//Dry_Function(0) ;//
        if(run_t.gPlasma ==0){ //plasma turn off flag
			run_t.gFan_counter =0;
			run_t.gFan_continueRun =1;

		}
		if(wifi_work_state == WIFI_CONN_CLOUD)
			wifiUpdate_Dry_Status(0);
	   }
       
     break;

     default:
         
     break;

	}
    

}

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
		HAL_Delay(200);
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

	   case POWER_OFF_FAN_STATE:
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
    
