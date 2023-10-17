#ifndef __TUYA_PROTOCOL_H
#define __TUYA_PROTOCOL_H
#include "main.h"



void muc_send_heartbeat(uint8_t beat);

void mcu_send_query(uint8_t ique);

void mcu_send_mode_works(void);

void mcu_send_wifi_state(uint8_t st);

void mcu_send_reset_wifi(void);




#endif 

