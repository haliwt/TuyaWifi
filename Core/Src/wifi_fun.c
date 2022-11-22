#include "wifi_fun.h"
#include "cmd_link.h"
#include "run.h"
#include "fan.h"
#include "tim.h"
#include "special_power.h"
#include "wifi.h"


WIFI_FUN   wifi_t;

void (*PowerOn)(void);
void (*PowerOff)(void);
void (*Ai_Fun)(uint8_t sig);


void (*SetTimes)(void);
void (*SetTemperature)(void);

static void Wifi_RunCmd(uint8_t sig);
static void wifiPowerOn_After_data_update(void);





uint8_t temp[7];


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


/***********************************************
	*
	*Function Name: void Wifi_Mode(void)
	*Funciton : wifi power on machine
	*           default is AI mode
	*
***********************************************/
void Wifi_Mode(void)
{
     static uint8_t no_wifi;
     if(wifi_work_state != WIFI_CONN_CLOUD && run_t.gPower_On ==1 && wifi_t.wifi_sensor ==0 ){
             if(no_wifi <10){
                 no_wifi ++ ;
                 mcu_set_wifi_mode(SMART_CONFIG_STATE );//smart config 
                 
             }
      }


    if(wifi_t.wifi_sensor ==0){ //tunr on 
      
      
      
      
   if(wifi_work_state ==  WIFI_CONN_CLOUD){ //当WIFI连接成功，

   if(wifi_t.wifi_power ==1){
      SendWifiData_To_Cmd(0xAA);

      wifi_t.wifi_power = 0xf0;
      if(run_t.SingleMode !=1){
           PowerOn(); //default AI 
           SendWifiCmd_To_Order(0x80);
      }
      wifi_t.wifiPowerOn_flag =1;
      wifi_t.WifiMode =1;
      wifiPowerOn_After_data_update();
      
           
   }
  

   if(wifi_t.wifi_power ==2 ){ //wifi receive data ->control ->mainboard ,turn shut down power
          wifi_t.wifi_power = 0xff;
			 PowerOff();
          wifi_t.wifiPowerOn_flag=0;
          run_t.gFan_continueRun =1;
          run_t.gFan_counter=0;
          wifi_t.WifiMode =0;
		  run_t.SingleMode =0; //WT.EIDT 2022.09.02
		  mcu_dp_bool_update(DPID_UV,0); //BOOL型数据上报;
          mcu_dp_bool_update(DPID_DRYING,0); //BOOL型数据上报;//dry
          mcu_dp_bool_update(DPID_RAT_CONTROL,0);//BOOL型数据上报;//RAT_CONTROL
          
          SendWifiCmd_To_Order(0x81);
		  
           
    }
    if(wifi_t.wifiPowerOn_flag==1){
       if(wifi_t.wifi_counter ==0){
           wifi_t.wifi_counter ++;
          Wifi_ReceiveCmd(wifi_t.wifi_RunMode); //Wifi_ReceiveCmd(wifi_t.wifi_RunMode);//Single_Usart_ReceiveData(wifi_t.wifi_RunMode);
       }
	   if(run_t.globe_setPriority==0){
           Wifi_RunCmd(wifi_t.wifi_cmd);
       }
      
    }
  }
 
  }

  
  if(wifi_work_state == WIFI_CONN_CLOUD && run_t.gPower_On ==1 && wifi_t.wifi_sensor ==0 ){

            if(run_t.gTimer_send_0xaa > 10){
			  run_t.gTimer_send_0xaa=0;

			  SendWifiData_To_Cmd(0xAA);

            }
    }
}
/***********************************************
   *
   *Function Name: void Wifi_RunCmd(void)
   *Funciton : wifi power on default is AI mode
   *
   *
***********************************************/
static void Wifi_RunCmd(uint8_t sig)
{
   Ai_Fun(sig); //调用函数地址,有参数的函数

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
    
    mcu_dp_value_update(DPID_SET_TIMGING,0); //VALUE型数据上报;
    mcu_dp_value_update(DPID_HUMIDITY,wifi_t.dispHumidityValue); //VALUE型数据上报;
    mcu_dp_value_update(DPID_SET_TEMPERATURE,0); //VALUE型数据上报;
  

}
/***********************************************
   *
   *Function Name: void Wifi_RunCmd(void)
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
  mcu_dp_enum_update(DPID_RAT_CONTROL,aiv); //枚举型数据上报;
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


