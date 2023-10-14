#ifndef __RUN_H__
#define __RUN_H__
#include "main.h"

#define WIFI_TUYA      1  //





typedef enum {                   /* enumeration for CProcess signals */
    kill =1,
	notkill,
	dry,
	notdry,
	rat_control,
	notrat_control
}Signal;



typedef enum
{
  WIFIENABLE =1,
  WIFIDISABLE = !WIFIENABLE

}WifiStatus;

typedef enum{

   POWER_ON =0x01,
   POWER_OFF,
   POWER_CONNECTOR_WIFI,
   UPDATE_TO_PANEL_DATA,
   POWER_OFF_FAN_STATE,
   WIFI_RESTART_INIT

   

}run_state_t;


typedef struct _RUN_T{
    
    uint8_t RunCommand_Label;
	uint8_t gPower_On;
	uint8_t gPower_flag;
	uint8_t gDht11_flag;
	uint8_t set_temperature_value;

	uint8_t gDht11_humidity ;
	uint8_t gDht11_temperature;

    uint8_t gFan_continueRun;
	uint8_t gTimer_dogfood_times ;
	
	
  
    uint8_t decodeFlag;
	
    uint8_t setup_timer_flag;
    uint8_t gmt_time_flag;
	
	uint8_t set_wind_speed_value;
	



	uint8_t  gModel;
	uint8_t  gPlasma;
	uint8_t  gDry;
	uint8_t  gUlransonic;

	
	uint8_t gTimer_60s;
	uint8_t gTimer_1s;

	uint8_t gFan_counter;
	uint8_t gTimer_senddata_panel;


 }RUN_T;

//#define CProcessInit(me_) ((me_)->cmdCtr__ =0,(me_)->state__ = IDLE)
extern uint8_t ReceiveBuffer[1];
extern RUN_T run_t; 

void RunCommand_MainBoard_Handler(void);





#endif 


