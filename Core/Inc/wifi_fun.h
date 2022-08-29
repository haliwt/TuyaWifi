#ifndef __WIFI_FUN_
#define __WIFI_FUN_
#include "main.h"


typedef enum{
  
  wifi_AI ,wifi_NotAI,wif_Kill,wif_Dry,wifi_Timer,wifi_Temp


}wifi_mode;


typedef struct _WIFI_FUN{

    uint8_t wifi_power;
    uint8_t wifiPowerOn_flag;
    uint8_t wifi_RunMode;

	uint8_t aikey;
	uint8_t notaikey;
	uint8_t wifi_dry;
	uint8_t wifi_time;
	uint8_t wifi_kill;
	uint8_t wifi_counter;
	


}WIFI_FUN;

extern WIFI_FUN   wifi_t;

extern void (*PowerOn)(void); //函数指针
extern void (*PowerOff)(void);
extern void (*SetTimes)(void);
extern void (*SetTemperature)(void);

void PowerOn_Host(void (*poweronHandler)(void));
void PowerOff_Host(void (*poweroffHandler)(void));
void SetTimeHost(void(*timesHandler)(void));
void SetTemperatureHost(void(*temperatureHandler)(void));

void Wifi_Mode(void);



#endif 

