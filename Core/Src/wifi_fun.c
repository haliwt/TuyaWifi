#include "wifi_fun.h"
#include "cmd_link.h"
#include "run.h"
#include "fan.h"
#include "tim.h"
#include "special_power.h"
#include "wifi.h"
#include "flash.h"
#include "gpio.h"
#include "dht11.h"

WIFI_FUN   wifi_t;

uint8_t time[7];

void (*PowerOn)(void);
void (*PowerOff)(void);
void (*Ai_Fun)(uint8_t sig);


void (*SetTimes)(void);
void (*SetTemperature)(void);


static void wifiPowerOn_After_data_update(void);
static void Get_BeiJing_Time(void);


void PowerOn_Host(void (* poweronHandler)(void))
{
    PowerOn = poweronHandler;  

}


void PowerOff_Host(void(*poweroffHandler)(void))
{
   PowerOff = poweroffHandler;

}
/****************************************************************
     * 
     * Function Name:void AI_Function_Host(void(*AIhandler)(uint8_t sig))
     * Function: take with reference of function pointer
     * 
     * 
****************************************************************/
void AI_Function_Host(void(*AIhandler)(uint8_t sig))
{
         Ai_Fun=AIhandler;
}

void SetTimeHost(void(*timesHandler)(void))
{
     SetTimes = timesHandler;

}


void SetTemperatureHost(void(*temperatureHandler)(void))
{
      SetTemperature = temperatureHandler ;

}


/*********************************************************************
	*
	*Function Name: void Wifi_Mode(void)
	*Funciton : wifi power on machine
	*           default is AI mode
	*
*********************************************************************/
void RunWifi_Command_Handler(void)
{
      static uint8_t first_connect,first_cloud_data,wbr3_flag;

	 switch(wifi_t.wifiRun_Cammand_label){

      case wifi_has_been_connected:
       
		   WIFI_WBR3_EN();
	       mcu_set_wifi_mode(AP_STATE);//AP_STATE
          // mcu_set_wifi_mode(SMART_CONFIG);//smart
		   mcu_get_wifi_work_state();

		 if(wifi_work_state ==WIFI_CONN_CLOUD){
		 
	        wifi_t.wifiRun_Cammand_label = wifi_up_update_tuya_cloud_data;
			
				
		  }
         wifi_t.wifiRun_Cammand_label=0xff;
		break;

        case wifi_link_tuya_cloud: //02
           
			 WIFI_WBR3_EN();
			
		    mcu_set_wifi_mode(AP_STATE);//AP_STATE
	       

			 mcu_get_wifi_work_state();

		    if(wifi_work_state ==WIFI_CONN_CLOUD){
			    wifi_t.wifiRun_Cammand_label = wifi_up_update_tuya_cloud_data;
				
			}
         wifi_t.wifiRun_Cammand_label=0xff;
	    break;

	  	
	  	case wifi_tuya_up_init_data://03
		  
	       if(first_cloud_data==0){
	            first_cloud_data++;
	          
			    wifiPowerOn_After_data_update();
				wifi_t.wifiRun_Cammand_label= 0xff;
	           
	   	    }
		   
            
		 
		
		 
       	break;

	  

//		case wifi_get_beijing_time://7
//	       if(wifi_t.gTimer_beijing_time > 29){
//               wifi_t.gTimer_beijing_time=0;
//               SendData_Real_GMT(wifi_t.getGreenwichTime[0],wifi_t.getGreenwichTime[1],wifi_t.getGreenwichTime[2]);
//		     
//		     wifi_t.wifiRun_Cammand_label=wifi_up_update_tuya_cloud_data;
//
//	       	}
//		    else{
//
//				wifi_t.wifiRun_Cammand_label=wifi_up_update_tuya_cloud_data;
//			}
//		   
//	   break;

	   

	   default:

	   break;
	 
     }
 

	 if(wifi_work_state == WIFI_CONN_CLOUD  ){

            if(first_connect < 5){
			   first_connect ++ ;

			  SendWifiData_To_Cmd(0x01);

            }
		   if(run_t.flash_write_data_flag == 0){
			run_t.flash_write_data_flag=2;
               Flash_Erase_Data();
               Flash_Write_Data();

		 }

		 if(wifi_t.gTimer_beijing_time > 29){
               wifi_t.gTimer_beijing_time=0;
			   mcu_get_greentime(time);
		 
               mcu_write_rtctime(wifi_t.getGreenwichTime);
			   
               SendData_Real_GMT( wifi_t.getGreenwichTime[4], wifi_t.getGreenwichTime[5], wifi_t.getGreenwichTime[6]);
		     
		     wifi_t.wifiRun_Cammand_label=wifi_up_update_tuya_cloud_data;

	      }

		 if(wifi_t.gTimer_up_dht11 >0){ //1 minutes
		   	  wifi_t.gTimer_up_dht11=0;
			  Wifi_DHT11_Up_Value(&DHT11);
		      wifiDisplayTemperature_Humidity();
			
          }
		 Get_BeiJing_Time();
            
		 Wifi_ReceiveData_Handler(wifi_t.response_wifi_signal_label);
		 
    }

	if(wifi_t.gTimer_get_wifi_state > 40){
		wifi_t.gTimer_get_wifi_state=0;
        mcu_get_wifi_work_state();
        if(wifi_work_state == WIFI_CONN_CLOUD)
              SendWifiData_To_Cmd(0x01);
	}

	 
}
/**********************************************************************
	*
	*Functin Name: void Wifi_RunMode(uint8_t cmd)
	*Function : resolver is by usart port receive data  from display panle  
	*Input Ref:  usart receive data
	*Return Ref: NO
	*
**********************************************************************/
void Wifi_ReceiveData_Handler(uint8_t cmd)
{

 
   switch(cmd){

       case OPEN_OFF_ITEM:

        
	    run_t.gPower_On = POWER_OFF;
        run_t.gPower_flag =POWER_OFF;
		run_t.RunCommand_Label=POWER_OFF;

		SendWifiCmd_To_Order(WIFI_POWER_OFF);

        Buzzer_KeySound();
        wifi_t.response_wifi_signal_label=0xff;
      cmd= 0xff;
	  break;

	   case OPEN_ON_ITEM:

	  
       run_t.gPower_On = POWER_ON;
	   run_t.gPower_flag =POWER_ON;
	   run_t.RunCommand_Label=POWER_ON;
	   SendWifiCmd_To_Order(WIFI_POWER_ON);
	   Buzzer_KeySound();
	    wifi_t.response_wifi_signal_label=0xff;

	  cmd= 0xff;

	  break;
	  
	  case PTC_ON_ITEM:
	  if(run_t.gPower_flag ==POWER_ON){
      
	     run_t.gDry=1;
		 SendWifiCmd_To_Order(WIFI_PTC_ON);
         Buzzer_KeySound();
	  	}
	    wifi_t.response_wifi_signal_label=0xff;
	   break;

	  case PTC_OFF_ITEM:
	  	if(run_t.gPower_flag ==POWER_ON){
      
	     run_t.gDry=0;
		 SendWifiCmd_To_Order(WIFI_PTC_OFF);
         Buzzer_KeySound();
	  	}
	     wifi_t.response_wifi_signal_label=0xff;
	  
	  break;

	  case PLASMA_OFF_ITEM: //"杀菌"
	  	if(run_t.gPower_flag ==POWER_ON){
            run_t.gPlasma=0;
			SendWifiCmd_To_Order(WIFI_KILL_OFF);
	  	    Buzzer_KeySound();
	  	}
	  wifi_t.response_wifi_signal_label=0xff;
	  	break;
		
	  case PLASMA_ON_ITEM:
	  	if(run_t.gPower_flag ==POWER_ON){
            run_t.gPlasma=1;
			SendWifiCmd_To_Order(WIFI_KILL_ON);
	  	    Buzzer_KeySound();
	  	}
	    wifi_t.response_wifi_signal_label=0xff;
	    break;

	  case ULTRASONIC_OFF_ITEM:
        if(run_t.gPower_flag ==POWER_ON){
            run_t.gUlransonic=0;
			SendWifiCmd_To_Order(WIFI_ULTRASONIC_OFF);
			Buzzer_KeySound();
        }
	    wifi_t.response_wifi_signal_label=0xff;
	  	break;

	  case ULTRASONIC_ON_ITEM:
	    if(run_t.gPower_flag ==POWER_ON){
            run_t.gUlransonic=1;
			SendWifiCmd_To_Order(WIFI_ULTRASONIC_ON);
			Buzzer_KeySound();
        }
	   wifi_t.response_wifi_signal_label=0xff;
	  	break;

	  case SMART_OFF_ITEM:
	  if(run_t.gPower_flag ==POWER_ON){
            run_t.gModel=0;
			SendWifiCmd_To_Order(WIFI_MODE_2);
		    Buzzer_KeySound();
        }
	    wifi_t.response_wifi_signal_label=0xff;
	  break;
		
	  case SMART_ON_ITEM:
	  	 if(run_t.gPower_flag ==POWER_ON){
            run_t.gModel=1;
			SendWifiCmd_To_Order(WIFI_MODE_1);
		    Buzzer_KeySound();
        }
	    wifi_t.response_wifi_signal_label=0xff;
	  	break;

	  case TEMPERATURE_ITEM:
	   if(run_t.gPower_flag ==POWER_ON){
         
			SendWifiData_To_PanelTemp(run_t.set_temperature_value);
            Buzzer_KeySound();
         }
	    wifi_t.response_wifi_signal_label=0xff;
	  break;

	  case FAN_ITEM:
	    if(run_t.gPower_flag ==POWER_ON){
      
			//run_t.gFan_counter = run_t.set_wind_speed_value;
    		SendWifiData_To_PanelWindSpeed(run_t.set_wind_speed_value);
          
			Buzzer_KeySound();
            
		}
	  
	     wifi_t.response_wifi_signal_label=0xff;
	  	break;

		case TIME_ITEM:

		 
		  SendWifiData_To_SetTime(wifi_t.setTimesValue);
          wifi_t.response_wifi_signal_label=0xff;
		  Buzzer_KeySound();

		break;

	 


	   default:

	     

	   break;

		}


   }
  
/**********************************************************************
	*
	*Functin Name: static void Get_BeiJing_Time(void)
	*Function : get beijing times
	*Input Ref:  usart receive data
	*Return Ref: NO
	*
**********************************************************************/     
static void Get_BeiJing_Time(void)
{
	

	    if(wifi_t.gTimer_gmt > 2){ //10 minute 
            wifi_t.gTimer_gmt=0;
            wifi_t.getGreenTime=1;
             wifi_t.getGreenTime =0xFE;
           // Decode_GMT(rx_wifi_data);
            wifi_t.real_hours = rx_wifi_data[4] + 8;
			if(wifi_t.real_hours > 24){
				wifi_t.real_hours = wifi_t.real_hours -24 ;

			}
			wifi_t.real_minutes = rx_wifi_data[5];
			wifi_t.real_seconds = rx_wifi_data[6];
         
            SendData_Real_GMT(wifi_t.real_hours ,wifi_t.real_minutes,rx_wifi_data[6]); //gmt[4]->hours, gmt[5]->minutes
		    
	    }
	


}




/***********************************************
   *
   *Function Name: void Wifi_RunCmd(void)
   *Funciton : wifi power on default is AI mode
   *
   *
***********************************************/
static void wifiPowerOn_After_data_update(void)
{

    mcu_dp_bool_update(DPID_SWITCH,1); //BOOL型数据上报;
   
    mcu_dp_value_update(DPID_TEMP_CURRENT,wifi_t.dispTemperatureValue); //VALUE型数据上报;
    
    mcu_dp_bool_update(DPID_UV,1); //BOOL型数据上报;
    mcu_dp_bool_update(DPID_DRYING,1); //BOOL型数据上报;
     mcu_dp_bool_update(DPID_RAT_CONTROL,1); //BOOL型数据上报;//WT.EDIT 2022.11.22
    
    mcu_dp_value_update(DPID_SET_TIMGING,wifi_t.setTimesValue); //VALUE型数据上报;
    mcu_dp_value_update(DPID_HUMIDITY,wifi_t.dispHumidityValue); //VALUE型数据上报;
    mcu_dp_value_update(DPID_SET_TEMPERATURE,0); //VALUE型数据上报;

	 mcu_dp_bool_update(DPID_SMART,1); //BOOL型数据上报;
    mcu_dp_value_update(DPID_FAN,run_t.set_wind_speed_value); //VALUE型数据上报;
  

}
/**********************************************************************
	*
	*Functin Name: void MainBoard_Itself_PowerOn_Fun(void)
	*Function :
	*Input Ref:  key of value
	*Return Ref: NO
	*
**********************************************************************/
void MainBoard_Self_Inspection_PowerOn_Fun(void)
{
	
	static uint8_t self_power_on_flag=0, flash_read_data;
	   
	
	   if(self_power_on_flag==0){
		   self_power_on_flag ++ ;
		   flash_read_data =Flash_Read_Data();
		   switch(flash_read_data){
	
			case error: //wifi don't link to tuya cloud ,need manual operation
				wifi_t.wifiRun_Cammand_label = 0xff;
		        run_t.flash_write_data_flag = 0;
			     WIFI_WBR3_DISABLE();
			break;
	
			case success: //wifi has been linked to tuya cloud,need auto link to tuya cloud
			   //wifi_t.runCommand_order_lable = wifi_link_tencent_cloud;
			   run_t.flash_write_data_flag = 1;
                WIFI_WBR3_DISABLE();
                HAL_Delay(1000);
			    WIFI_WBR3_EN();
                
			break;
	
	
	
		   }
	   
	
	   switch(run_t.flash_write_data_flag){
	
		 case 0:
	
		 break;
	
		 case 1:
             mcu_get_wifi_work_state();
			if(wifi_work_state ==WIFI_CONN_CLOUD){
			   wifi_t.wifiRun_Cammand_label= wifi_has_been_connected ;
			    
		   }
		   else wifi_t.wifiRun_Cammand_label =wifi_link_tuya_cloud;//wifi_has_been_connected
	
		 break;
	
	
	   }
	  }
	   
	  if(wifi_work_state ==WIFI_CONN_CLOUD &&	self_power_on_flag==1){
		   self_power_on_flag++;
			   wifi_t.wifiRun_Cammand_label = wifi_has_been_connected;
			
	   }



}

/***********************************************
   *
   *Function Name: void wifiDisplayTemperature_Humidity(void)
   *Funciton : separately update value 
   *
   *
***********************************************/
void wifiDisplayTemperature_Humidity(void)
{
  mcu_dp_value_update(DPID_TEMP_CURRENT,wifi_t.dispTemperatureValue); //VALUE型数据上报;
  mcu_dp_value_update(DPID_HUMIDITY,wifi_t.dispHumidityValue); //VALUE型数据上报;

}

void wifiUpdate_Power_Status(uint8_t pvalue)
{

   mcu_dp_bool_update(DPID_SWITCH,pvalue); //BOOL型数据上报;
}
void wifiUpdate_Kill_Status(uint8_t kvalue)
{
   mcu_dp_bool_update(DPID_UV,kvalue); //BOOL型数据上报;
}
//void wifiUpdate_AI_Status(uint8_t aiv)
//{
//  mcu_dp_enum_update(DPID_DRYING,aiv); //枚举型数据上报;
//}

void wifiUpdate_Rat_Control_Status(uint8_t aiv)
{
   mcu_dp_bool_update(DPID_RAT_CONTROL,aiv); //BOOL型数据上报;
}

void wifiUpdate_Dry_Status(uint8_t dvalue)
{
    mcu_dp_bool_update(DPID_DRYING,dvalue); //BOOL型数据上报;
}


void wifiUpdate_SetTimeValue(uint8_t tv)
{
   mcu_dp_value_update(DPID_SET_TIMGING,tv); //VALUE型数据上报;

}

void wifiUpdate_SetTemperatureValue(uint8_t temp)
{
   mcu_dp_value_update(DPID_SET_TEMPERATURE,temp); //VALUE型数据上报;
}



