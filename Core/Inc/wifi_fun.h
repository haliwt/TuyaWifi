#ifndef __WIFI_FUN_
#define __WIFI_FUN_
#include "main.h"


typedef enum DISPLAY_STATE_T{
   
    WIFI_POWER_ON = 0x80,
    WIFI_POWER_OFF=0X81,
    WIFI_MODE_1=0X08,   //state ->normal works
    WIFI_MODE_2=0X18,   //state->sleeping works
    WIFI_KILL_ON=0x04,  //Anion(plasma)
    WIFI_KILL_OFF=0x14,
    WIFI_PTC_ON = 0x02, 
    WIFI_PTC_OFF = 0x12,
    WIFI_ULTRASONIC_ON = 0x01,       //ultrasonic
    WIFI_ULTRASONIC_OFF = 0x11,
    WIFI_WIND_SPEED = 0x90,
    WIFI_TEMPERATURE = 0xA0,
    WIFI_POWER_ON_NORMAL= 0xB0, 
    WIFI_POWER_OFF_NORMAL =0xB1


}display_state_t;

typedef enum _CLOUD_STATE{
   OPEN_OFF_ITEM=0x01,
   OPEN_ON_ITEM,
   PTC_OFF_ITEM,
   PTC_ON_ITEM,
   PLASMA_OFF_ITEM,
   PLASMA_ON_ITEM,
   ULTRASONIC_OFF_ITEM,
   ULTRASONIC_ON_ITEM,
   SMART_ON_ITEM,
   SMART_OFF_ITEM,
   TEMPERATURE_ITEM,
   FAN_ITEM,
   TIME_ITEM
}cloud_state;



typedef enum _wifi_state_t{  
	
    wifi_has_been_connected =0x01,
	wifi_link_tuya_cloud, //2
	wifi_tuya_up_init_data, //3
	wifi_tuya_download_data, //4
	wifi_up_update_tuya_cloud_data,//5
	wifi_tuya_up_dht11_data, //6
	wifi_get_beijing_time, //7
	wifi_disconnect//8


}wifi_state_t;



typedef struct _WIFI_FUN{

    uint8_t wifi_power;
    uint8_t wifiPowerOn_flag;
    uint8_t wifi_RunMode;
	uint8_t getNet_flag;
	uint8_t WifiMode;
	uint8_t wifi_cmd;
    uint8_t wifi_sensor;
	uint8_t wifi_power_times;
	uint8_t wifiRun_Cammand_label;




	uint8_t setTimesValue;
	uint8_t dispTimesValue;
	uint8_t SetTemperatureValue;
	uint8_t dispTemperatureValue;
	uint8_t dispHumidityValue;
	

    uint8_t getTime_flag;
    uint8_t response_wifi_signal_label;
	uint8_t getGreenTime;
	

	uint8_t real_hours;
	uint8_t real_minutes;
	uint8_t real_seconds; 

    
  


 
	uint8_t gTimer_1s;
    uint8_t gTimer_get_wifi_state;
	uint8_t gTimer_up_dht11;
	uint8_t gTimer_beijing_time;
	uint8_t get_greenwich_error;
	uint8_t gTimer_gmt;
	uint8_t getGreenwichTime[7];
	


}WIFI_FUN;

extern WIFI_FUN   wifi_t;

typedef struct{

  uint8_t tuya_wifi_info;

}_TUYA_T;

extern _TUYA_T tuya_t;


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

void RunWifi_Command_Handler(void);

void wifiDisplayTemperature_Humidity(void);
void wifiUpdate_Power_Status(uint8_t pv);
void wifiUpdate_Kill_Status(uint8_t kv);
//void wifiUpdate_AI_Status(uint8_t av);
void wifiUpdate_Rat_Control_Status(uint8_t rm);


void wifiUpdate_Dry_Status(uint8_t dv);

void wifiUpdate_SetTimeValue(uint8_t tv);
void wifiUpdate_SetTemperatureValue(uint8_t temp);
void Wifi_ReceiveData_Handler(uint8_t cmd);
void wifiUpdate_Fan_Level(uint8_t temp);



void MainBoard_Self_Inspection_PowerOn_Fun(void);



#endif 

