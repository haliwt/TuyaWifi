#ifndef __BSP_DECODER_H
#include __BSP_DECODER_H
#include "main.h"


typedef enum{

	 DRY_ON = 0x40,
	 DRY_OFF = 0x41,

     DRY_ON_NO_BUZZER = 0x90,
	 DRY_OFF_NO_BUZZER = 0x91,

	 PLASMA_ON = 0x20,
	 PLASMA_OFF = 0x21,
     PLASM_ON_NO_BUZZER = 0xA0,
     PLASM_OFF_NO_BUZZER = 0xA1,

     

	 FAN_LEVEL_MIN =0x10,
	 FAN_LEVEL_MAX = 0x11,
	 FAN_LEVEL_MAX_NO_SOUND = 0x12,
	 FAN_STOP = 0x13,
	 

     AI_MODE_ON = 0x30,   //EDIT 2023.09.13 new Add
     AI_MODE_OFF =0x31

}Rx_Receive_state;



void Decode_RunCmd(void);





void Rx_From_DisplayCmd(uint8_t cmd);

void Wifi_ReceiveCmd(uint8_t cmd);



#endif 


