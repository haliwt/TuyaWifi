#include "tuya_protocol.h"
#include "bsp.h"

uint16_t  HeatAddr = 0X55aa; //Ä¬ÈÏ
//send usart one byte
static void MYUSART_SendData(uint8_t data)
{
	while((USART2->ISR&0X40)==0); 
	USART2->TDR = data;
}


// heat of address·
static void SendHead(void)
{
	MYUSART_SendData(0x55);
	MYUSART_SendData(0xaa);
}

//·¢ËÍ°ü±êÊ¶,
static void SendVersion(uint8_t flag)
{
	MYUSART_SendData(flag);

}

//·¢ËÍ°ü±êÊ¶,
static void SendCmd(uint8_t flag)
{
	MYUSART_SendData(flag);

}

//data len
static void SendLenght(uint16_t length)
{
	MYUSART_SendData(length>>8);
	MYUSART_SendData(length);
}

//data len
static void SendData(uint8_t data)
{
	MYUSART_SendData(data);
}

/********************************************************
	*
	*Function Name: void muc_send_heartbeat(uint8_t beat)
	*Function:
	*Input Ref:
	*Return Ref:
	*
********************************************************/
void muc_send_heartbeat(uint8_t beat)
{
	uint16_t temp;
   
	SendHead();
	SendVersion(0x03);
	SendCmd(0x00);
	SendLenght(0x01);
	
	temp = (0x55+0xaa+0x03+0x00+0x01)/256;
//	SendCheck(temp);
//	data=JudgeStr(2000);
//	if(data)
//		ensure=data[9];
//	else
//		ensure=0xff;
//	return ensure;



}
/********************************************************
	*
	*Function Name: void muc_send_heartbeat(uint8_t beat)
	*Function:
	*Input Ref:
	*Return Ref:
	*
********************************************************/
//void mcu_send_query(uint8_t ique)
/********************************************************
	*
	*Function Name: void muc_send_heartbeat(uint8_t beat)
	*Function:
	*Input Ref:
	*Return Ref:
	*
********************************************************/
//void mcu_send_mode_works(void)
/********************************************************
	*
	*Function Name: void muc_send_heartbeat(uint8_t beat)
	*Function:
	*Input Ref:
	*Return Ref:
	*
********************************************************/
//void mcu_send_wifi_state(uint8_t st)
/********************************************************
	*
	*Function Name: void muc_send_heartbeat(uint8_t beat)
	*Function:
	*Input Ref:
	*Return Ref:
	*
********************************************************/
//void mcu_send_reset_wifi(void)
/********************************************************
	*
	*Function Name: void muc_send_heartbeat(uint8_t beat)
	*Function:
	*Input Ref:
	*Return Ref:
	*
********************************************************/






