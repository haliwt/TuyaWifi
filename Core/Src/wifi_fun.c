#include "wifi_fun.h"
#include "cmd_link.h"
#include "run.h"
#include "fan.h"
#include "tim.h"
#include "special_power.h"

WIFI_FUN   wifi_t;

void (*PowerOn)(void);
void (*PowerOff)(void);
void (*SetTimes)(void);
void (*SetTemperature)(void);

static void Wifi_RunCmd(void);
static void wifi_SpeicalAI_Fun(void);
static void wifi_SpeicalNotAI_Fun(void);




void PowerOn_Host(void (* poweronHandler)(void))
{
    PowerOn = poweronHandler;  

}


void PowerOff_Host(void(*poweroffHandler)(void))
{
   PowerOff = poweroffHandler;

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
  
   if(wifi_work_state == WIFI_CONNECTED ){ //当WIFI连接成功，打开天气数据且仅一次

   if(wifi_t.wifi_power ==1){

      wifi_t.wifi_power = 0xf0;

      PowerOn(); //default AI 
      wifi_t.wifiPowerOn_flag =1;
           
   }

   if(wifi_t.wifi_power ==0 ){
          wifi_t.wifi_power = 0xff;
			 PowerOff();
          wifi_t.wifiPowerOn_flag=0;
           
    }
    Wifi_RunCmd();
  }
}
/***********************************************
   *
   *Function Name: void Wifi_RunCmd(void)
   *Funciton : wifi power on default is AI mode
   *
   *
***********************************************/
static void Wifi_RunCmd(void)
{
    static uint8_t wifi_ai = 0xff,wifi_notai=0xff;
    
    if(wifi_t.wifiPowerOn_flag ==1){

      switch(wifi_t.wifi_RunMode){
         
         case wifi_AI:
            if(wifi_t.wifi_power==0xf0){
                wifi_t.wifi_power++;
            }
            else{
               if(wifi_ai != wifi_t.aikey){
                   wifi_ai = wifi_t.aikey;
                   wifi_SpeicalAI_Fun();
                }
            }

         break;

         case wifi_NotAI:
            if(wifi_notai !=wifi_t.notaikey){
             wifi_notai = wifi_t.notaikey;
             wifi_SpeicalNotAI_Fun();

         }

         break;


      }


    }


}
/****************************************************************
   *
   *Function Name:  static void wifi_SpeicalAI_Fun(void)
   *Funciton :
   *
   *
****************************************************************/
static void wifi_SpeicalAI_Fun(void)
{
     FAN_CCW_RUN(); 
     PTC_SetHigh(); //dry on
     PLASMA_SetHigh(); // plasma on
     HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);//ultrasnoic ON 
     
}
/****************************************************************
   *
   *Function Name:  static void wifi_SpeicalNotAI_Fun();
   *Funciton :
   *
   *
****************************************************************/
 static void wifi_SpeicalNotAI_Fun()
 {
    if(wifi_t.wifi_kill == 0){  //power on default kill function Tunr on
       run_t.gFan_continueRun =0; //Turn On fan
       PLASMA_SetHigh(); // plasma on
       HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);//ultrasnoic ON 
    }
    else{

      PLASMA_SetLow();
      HAL_TIM_PWM_Stop(&htim1, TIM_CHANNEL_1);//ultrasnoic off
      run_t.gFan_continueRun =1;
      run_t.gFan_counter=0;

    }

    if(wifi_t.wifi_dry==0){ //heat turn On default On
      run_t.gFan_continueRun =0;//turn On fan
       PTC_SetHigh();
    }
    else{
      PTC_SetLow();
      run_t.gFan_continueRun =1;
      run_t.gFan_counter=0;
    }


 }

