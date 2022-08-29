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
   
   if(wifi_work_state == WIFI_CONNECTED || wifi_work_state ==  WIFI_CONN_CLOUD  ){ //当WIFI连接成功，打开天气数据且仅一次

   if(wifi_t.wifi_power ==1){

      wifi_t.wifi_power = 0xf0;

      PowerOn(); //default AI 
      wifi_t.wifiPowerOn_flag =1;
      wifiPowerOn_After_data_update();
           
   }

   if(wifi_t.wifi_power ==0 ){
          wifi_t.wifi_power = 0xff;
			 PowerOff();
          wifi_t.wifiPowerOn_flag=0;
          run_t.gFan_continueRun =1;
          run_t.gFan_counter=0;
           
    }
    if(wifi_t.wifiPowerOn_flag==1){
      Wifi_RunCmd(wifi_t.wifi_RunMode);
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

    mcu_dp_bool_update(DPID_START,1); //BOOL型数据上报;
    mcu_dp_enum_update(DPID_MODE,0); //枚举型数据上报;
    mcu_dp_fault_update(DPID_FAULT,0); //故障型数据上报;
    mcu_dp_value_update(DPID_DISPTEMP,0); //VALUE型数据上报;
    mcu_dp_bool_update(DPID_KILL,1); //BOOL型数据上报;
    mcu_dp_bool_update(DPID_HEAT,1); //BOOL型数据上报;
    mcu_dp_value_update(DPID_SETTIME,0); //VALUE型数据上报;
    mcu_dp_value_update(DPID_DISPHUM,0); //VALUE型数据上报;
    mcu_dp_value_update(DPID_SETTEMP,0); //VALUE型数据上报;
    mcu_dp_value_update(DPID_DISPTIME,0); //VALUE型数据上报;




}
