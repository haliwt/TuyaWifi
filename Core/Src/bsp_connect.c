#include "bsp_connect.h"
#include "bsp.h"

#define BSP_TIMEOUT		1		/* �������ʱʱ��, ��λms */
#define NUM			1			/* ѭ�����ʹ��� */
uint8_t ADD_NUM ;

/**********************************************************************
*
*Functin Name:uint8_t Wifi_ReadParam_PowerOnOff(uint8_t sel);
*Function : run order from main command 
*Input Ref:  run_t.single_dat is command 
*Return Ref: receive is ok -> 1 don't receive data -> 0
*
**********************************************************************/
uint8_t Wifi_ReadParam_PowerOnOff(uint8_t reg)
{

	uint8_t i;
	
	for (i = 0; i < (NUM+ADD_NUM); i++)
	{

        if(reg ==1)  SendWifiCmd_To_Order(WIFI_POWER_ON_NORMAL);
		else	SendWifiCmd_To_Order(WIFI_POWER_OFF_NORMAL);
		run_t.gTimer_receive_times =0;
		
		while (1)				/* �ȴ�Ӧ��,��ʱ����յ�Ӧ����break  */
		{
			bsp_Idle();

			if (run_t.gTimer_receive_times > BSP_TIMEOUT)		
			{
				break;		/* ͨ�ų�ʱ�� */
			}
			
			if (reg == 1 )
			{
               if(run_t.response_power_on ==1)
				break;		/* ���յ�Ӧ�� */
			}
			else{
				if(run_t.response_power_off ==1)
				break;		/* ���յ�Ӧ�� */

			}
		}
		
		if (reg == 1 )
		{
           if(run_t.response_power_on ==1)
			break;
           else 
		      ADD_NUM++;
		  
		}
		else{
			if(run_t.response_power_off ==1)
			break;		/* ���յ�Ӧ�� */
            else 
			   ADD_NUM++;
			
				

		}
	}
	
	if (reg == 1 )
	{
       if(run_t.response_power_on ==1)
		return 1 ;/* ���յ�Ӧ�� */
	   else
	   	return 0;
	}
	else{
		
		if(run_t.response_power_off ==1)
			return 1;
        else 
			return 0;
	}



}
/**********************************************************************
*
*Functin Name:uint8_t Wifi_ReadParam_PowerOnOff(uint8_t sel);
*Function : run order from main command 
*Input Ref:  run_t.single_dat is command 
*Return Ref: receive is ok -> 1 don't receive data -> 0
*
**********************************************************************/
uint8_t  Wifi_ReadParam_Temperature_Value(void)
{	
	uint8_t i;
	
	for (i = 0; i < (NUM+ADD_NUM); i++)
	{
		 //SendData_Set_Wifi(0x01);		  /* �������� */
		  SendWifiData_To_PanelTemp(run_t.set_temperature_value);
	      run_t.gTimer_receive_times =0;
		
		while (1)				/* �ȴ�Ӧ��,��ʱ����յ�Ӧ����break  */
		{
			bsp_Idle();

			if (run_t.gTimer_receive_times > BSP_TIMEOUT)		
			{
				break;		/* ͨ�ų�ʱ�� */
			}
			
			
            if(run_t.response_temperature_value ==1){
				break;		/* ���յ�Ӧ�� */
			}
			

			
		}
		
		
        if(run_t.response_temperature_value==1){
			break;		/* ���յ�Ӧ�� */
		 
		}
		else{
			
		   break;	//ADD_NUM++;
        }
	}
	

    if(run_t.response_temperature_value ==1)
		return 1 ;/* ���յ�Ӧ�� */
	else
	   return 0;
	
	
}

/**********************************************************************
*
*Functin Name:uint8_t Wifi_ReadParam_PowerOnOff(uint8_t sel);
*Function : run order from main command 
*Input Ref:  run_t.single_dat is command 
*Return Ref: receive is ok -> 1 don't receive data -> 0
*
**********************************************************************/
uint8_t  Wifi_ReadParam_Timer_Value(void)
{	
	uint8_t i;
	
	for (i = 0; i < (NUM+ADD_NUM); i++)
	{
		 //SendData_Set_Wifi(0x01);		  /* �������� */
		  SendWifiData_To_SetTime(wifi_t.setTimesValue);
	      run_t.gTimer_receive_times =0;
		
		while (1)				/* �ȴ�Ӧ��,��ʱ����յ�Ӧ����break  */
		{
			bsp_Idle();

			if (run_t.gTimer_receive_times > BSP_TIMEOUT)		
			{
				break;		/* ͨ�ų�ʱ�� */
			}
			
			
            if(run_t.response_timer_value ==1){
				break;		/* ���յ�Ӧ�� */
			}
			

			
		}
		
		
        if(run_t.response_timer_value ==1){
			break;		/* ���յ�Ӧ�� */
		 
		}
		else{
			
		   break;//ADD_NUM++;
        }
	}
	

    if(run_t.response_timer_value  ==1)
		return 1 ;/* ���յ�Ӧ�� */
	else
	   return 0;
	
	
}

