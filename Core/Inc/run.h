#ifndef __RUN_H__
#define __RUN_H__
#include "main.h"

#define WIFI_TUYA      1  //
#define AI_ENABLE      1

typedef enum {                   /* enumeration for CProcess signals */
    WIFI_SIG,RUN_SIG,AI_SIG
}Signal;

typedef enum
{
  AIENABLE = 1,
  AIDISABLE = !AIENABLE
} AiStatus;

typedef enum
{
  WIFIENABLE =1,
  WIFIDISABLE = !WIFIENABLE

}WifiStatus;



typedef struct _RUN_T{
    
   uint8_t gPower_On;
   uint8_t gPower_flag;
   uint8_t gDht11_flag;
   uint8_t gTemperature;

   uint8_t gDht11_humidity ;
   uint8_t gDht11_temperature;

   uint8_t gTimer_Counter;
   uint8_t gFan_continueRun;
 


   uint8_t gbuzzer_flag;
 
  uint8_t decodeFlag;
  uint8_t gTimer_hours ;
  uint8_t sendtimes;
 

   uint8_t  AI ;
   uint8_t  gFan;
   uint8_t  gFan_flag;
   uint8_t  gPlasma;
   uint8_t  gDry;
   uint8_t  gAi;  
   uint8_t  Ai_key;

   
	uint8_t ai_key;
	uint8_t ai_key_off;
			
	uint8_t ster_key;
	uint8_t ster_key_off;

	uint8_t dry_key;
	uint8_t dry_key_off;

	uint8_t fan_key;
	uint8_t fan_key_off;

   uint8_t gTimer_60s;
  
   uint8_t gFan_counter;

   //wifi 
   uint8_t gTimer_wifi_20ms ;
   
 }RUN_T;

#define CProcessInit(me_) ((me_)->cmdCtr__ =0,(me_)->state__ = IDLE)
extern uint8_t ReceiveBuffer[1];
extern RUN_T run_t; 



//void CProcessRun_Init(void);
//void CProcess_Run(void);
void RunCommand_Mode(uint8_t sig);
void RunCommand_Order(void);

void Decode_RunCmd(void);

#endif 


