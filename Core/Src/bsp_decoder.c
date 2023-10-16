#include "bsp_decoder.h"
#include "bsp.h"

uint8_t response_signal_on,response_signal_off;
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


         Rx_From_DisplayCmd(cmdType_2);  
        
       break;

	  case 'W': //wifi-function
	      if(run_t.gPower_On==POWER_ON){
	      if(cmdType_2==1){
              //fast led blink 
              SendWifiData_To_Cmd(0x52);
			  Buzzer_KeySound();	
              wifi_t.wifiRun_Cammand_label = wifi_link_tuya_cloud;//2 
//             WIFI_WBR3_DISABLE();
//             HAL_Delay(1000);
//			 WIFI_WBR3_EN();

				tuya_t.wifi_login_process =1;
             
              
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
           if(run_t.gPower_On==POWER_ON){
               Rx_From_DisplayCmd(cmdType_2); 
              
           }
     
         
      break;

	  case 'M': //temperature value
	  	if(run_t.gPower_On==POWER_ON){
              
             run_t.set_temperature_value = cmdType_2;
			if(wifi_work_state == WIFI_CONN_CLOUD)
		    	mcu_dp_value_update(DPID_SET_TEMPERATURE,cmdType_2); //VALUE型数据上报;
			   
         }
	  

	  break;

	  case 'T':
		if(run_t.gPower_On==POWER_ON){
              
             wifi_t.setTimesValue = cmdType_2;
			if(wifi_work_state == WIFI_CONN_CLOUD)
		    	mcu_dp_value_update(DPID_SET_TIMGING,cmdType_2); //VALUE型数据上报;
			 
         }
	  
	      


	  break;

	  


	  case 'Z' ://buzzer sound 
	    if(run_t.gPower_On==POWER_ON){

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
	*Functin Name: void Rx_From_DisplayCmd(uint8_t cmd)
	*Function : resolver is by usart port receive data  from display panle  
	*Input Ref:  usart receive data
	*Return Ref: NO
	*
**********************************************************************/
void Rx_From_DisplayCmd(uint8_t cmd)
{
 
   static uint8_t response_int_on=0xff, response_int_off =0xff;
  
  
	switch(cmd){

    case 0x00: //power off
    
		  SendWifiData_To_Cmd(0x53);
	      if(response_int_off != response_signal_off){
		  	response_int_off = response_signal_off;
	      	Buzzer_KeySound();

	      }
		  response_signal_on++;
		  run_t.gPower_On=POWER_OFF;
	      run_t.gPower_flag =POWER_OFF;
		  run_t.RunCommand_Label=POWER_OFF;
		 
		  wifiUpdate_Power_Status(0);
		 
           
    break;

    case 0x01: // power on
    	 SendWifiData_To_Cmd(0x54);
		 
		 if(response_int_on != response_signal_on){
		  	response_int_on = response_signal_on;
             Buzzer_KeySound();
		 }
		response_signal_off++;
		run_t.gPower_On=POWER_ON;
	    run_t.gPower_flag=POWER_ON;
	
		wifi_t.wifi_power =POWER_ON; //WI.EDTI 2022.09.02
		run_t.RunCommand_Label=POWER_ON;
	    wifiUpdate_Power_Status(1);
	
         
		   
     break;

	 	 //dry key
     case DRY_ON : //PTC turn on
       if( run_t.gPower_flag == POWER_ON){
         run_t.gDry = 1;
		 Buzzer_KeySound();
         run_t.gFan_continueRun =0;
	   if(wifi_work_state == WIFI_CONN_CLOUD)
		  wifiUpdate_Dry_Status(1);

		  }

	break;

	case DRY_OFF:
	  if( run_t.gPower_flag == POWER_ON){
         run_t.gDry = 0;
		 Buzzer_KeySound();
         run_t.gFan_continueRun =0;
	   if(wifi_work_state == WIFI_CONN_CLOUD)
		  wifiUpdate_Dry_Status(0);

		 }

	break;

	case DRY_ON_NO_BUZZER:
		 if( run_t.gPower_flag == POWER_ON){
         run_t.gDry = 1;
         run_t.gFan_continueRun =0;
	   if(wifi_work_state == WIFI_CONN_CLOUD)
		  wifiUpdate_Dry_Status(1);

		  }
		

	break;

	case DRY_OFF_NO_BUZZER:
		if( run_t.gPower_flag == POWER_ON){
         run_t.gDry = 0;
		
         run_t.gFan_continueRun =0;
	   if(wifi_work_state == WIFI_CONN_CLOUD)
		  wifiUpdate_Dry_Status(0);

		 }

	break;

	case PLASMA_ON:
		if( run_t.gPower_flag == POWER_ON){
         run_t.gPlasma = 1;
		 Buzzer_KeySound();
         run_t.gFan_continueRun =0;
	   if(wifi_work_state == WIFI_CONN_CLOUD)
		  wifiUpdate_Kill_Status(1);

		 }

	break;

	case PLASMA_OFF:
		
	    if( run_t.gPower_flag == POWER_ON){
			 run_t.gPlasma = 0;
			 Buzzer_KeySound();
			 run_t.gFan_continueRun =0;
		   if(wifi_work_state == WIFI_CONN_CLOUD)
			  wifiUpdate_Kill_Status(0);
	
			 }

	break;

	case FAN_LEVEL_MAX:

	 if( run_t.gPower_flag == POWER_ON){
	
		run_t.set_wind_speed_value =100;
			 Buzzer_KeySound();
			 run_t.gFan_continueRun =0;
	if(wifi_work_state == WIFI_CONN_CLOUD)
			wifiUpdate_Fan_Level(100);
	
	}

	break;

	case FAN_LEVEL_MIN:
		 if( run_t.gPower_flag == POWER_ON){
		
			 run_t.set_wind_speed_value = 50;
			 Buzzer_KeySound();
			 run_t.gFan_continueRun =0;
		   if(wifi_work_state == WIFI_CONN_CLOUD)
			  wifiUpdate_Fan_Level(50);
	
			 }

	break;
	

   

     default:
         
     break;

	}
    

}

