#include "cmd_link.h"
#include "usart.h"
#include "run.h"
#include "fan.h"
#include "wifi.h"

#define MAX_BUFFER_SIZE  8

uint8_t inputBuf[4];
uint8_t  inputCmd[2];
uint8_t Res,i;
uint8_t wifiInputBuf[8];

static uint8_t transferSize;
static uint8_t outputBuf[MAX_BUFFER_SIZE];
volatile static uint8_t transOngoingFlag;



void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    static uint8_t state=0;
    if(huart->Instance==USART1)
	//if(huart==&huart1) // Motor Board receive data (filter)
	{

		switch(state)
		{
		case 0:  //#0
			if(inputBuf[0] == 'T')  //hex :54 - "T" -fixed
				state=1; //=1
		
			break;
		case 1: //#1
             if(inputBuf[0] == 'K')  //hex :4B - "K" -fixed
				state=2; //=1
			else
			   state =0;
			break;
            
        case 2:
             inputCmd[0]= inputBuf[0];
             state = 3;
        
        break;
        
        case 3:
            inputCmd[1]= inputBuf[0];
            run_t.decodeFlag =1;
            state = 0;
        
        break;
	
		default:
			state=0;
			run_t.decodeFlag =0;
		}
		HAL_UART_Receive_IT(&huart1,inputBuf,1);//UART receive data interrupt 1 byte
		
	}
    if(huart->Instance==USART2){
    //if(huart == &huart2){
      
      if(__HAL_UART_GET_FLAG(&huart2, UART_FLAG_RXNE) != RESET){ //如果接收到了一个字节的数据
          Res= USART2->RDR ;
          uart_receive_input(Res);
      
      
      }
        
      if(__HAL_UART_GET_FLAG(&huart2,UART_FLAG_IDLE)!= RESET)  //如果接收到了一个字节的数据
      {
         __HAL_UART_CLEAR_IDLEFLAG(&huart2);//清除标志位  
         // USART2->DR; //清除USART_IT_IDLE标志          
         // Res= huart2.Instance->RDR ;//wifiInputBuf[i];
         // uart_receive_input(Res); 
          i++;
       
    // Res= USART2->RDR ;
     // uart_receive_input(Res);
         
       
     
     }
    __HAL_UART_ENABLE_IT(&huart2, UART_IT_RXNE);
     __HAL_UART_ENABLE_IT(&huart2, UART_IT_IDLE);//??????
    
    }
}

//
void Decode_Function(void)
{
   if(run_t.decodeFlag==1){
   
      run_t.decodeFlag =0;
      Decode_RunCmd();
      
     }
}

/********************************************************************************
	**
	*Function Name:void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
	*Function :UART callback function  for UART interrupt for receive data
	*Input Ref: structure UART_HandleTypeDef pointer
	*Return Ref:NO
	*
*******************************************************************************/
void SendData_To_TouchKey(uint8_t hum,uint8_t temp)
{

	//crc=0x55;
	outputBuf[0]='M'; //4D
	outputBuf[1]='A'; //41
	outputBuf[2]='D'; //44	// 'M' for motor board
	outputBuf[3]=hum; //	// 'R' rotator motor for select filter
	outputBuf[4]=temp; // // one command parameter
	
	//for(i=3;i<6;i++) crc ^= outputBuf[i];
	//outputBuf[i]=crc;
	transferSize=5;
	if(transferSize)
	{
		while(transOngoingFlag); //UART interrupt transmit flag ,disable one more send data.
		transOngoingFlag=1;
		HAL_UART_Transmit_IT(&huart1,outputBuf,transferSize);
	}



}


/********************************************************************************
**
*Function Name:void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
*Function :UART callback function  for UART interrupt for transmit data
*Input Ref: structure UART_HandleTypeDef pointer
*Return Ref:NO
*
*******************************************************************************/
void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{
	if(huart==&huart1)
	{
		transOngoingFlag=0; //UART Transmit interrupt flag =0 ,RUN
	}

}





