#ifndef __WIFI_FUN_
#define __WIFI_FUN_
#include "main.h"


typedef enum{
  
   wifi_AI=0x01 ,wifi_notAI=0x11,wifi_itemkill=0x04,wifi_itemnotkill=0x14,
     wifi_heat= 0x02,wifi_notheat=0x12,wifi_Timer,wifi_Temp


}wifi_mode;


typedef struct _WIFI_FUN{

    uint8_t wifi_power;
    uint8_t wifiPowerOn_flag;
    uint8_t wifi_RunMode;
	

	uint8_t wifi_ai;
	uint8_t wifi_itemAi;
	uint8_t wifi_dry;
	uint8_t wifi_time;
	uint8_t wifi_kill;
	
	


}WIFI_FUN;

extern WIFI_FUN   wifi_t;

extern void (*PowerOn)(void); //函数指针
extern void (*PowerOff)(void);
extern void (*Ai_Fun)(uint8_t sig);
extern void (*SetTimes)(void);
extern void (*SetTemperature)(void);

void PowerOn_Host(void (*poweronHandler)(void));
void PowerOff_Host(void (*poweroffHandler)(void));
void AI_Function_Host(void(*AIhandler)(uint8_t sig));

void SetTimeHost(void(*timesHandler)(void));
void SetTemperatureHost(void(*temperatureHandler)(void));

void Wifi_Mode(void);



#endif 

