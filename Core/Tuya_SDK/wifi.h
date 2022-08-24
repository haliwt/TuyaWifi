/**********************************Copyright (c)**********************************
**                       ��Ȩ���� (C), 2015-2020, Ϳѻ�Ƽ�
**
**                             http://www.tuya.com
**
*********************************************************************************/
/**
 * @file    wifi.h
 * @author  Ϳѻ�ۺ�Э�鿪����
 * @version v2.5.6
 * @date    2020.12.16
 * @brief   �û�������ĸ��ļ�ʵ������
 */

/****************************** �������� ������ *******************************
����MCU���ͺͱ��뻷�����ֶ��������Դ˴�������ο����û������аѿ����մ���������
Ϳѻ����MCU���ܽ������
******************************************************************************/

#ifndef __WIFI_H_
#define __WIFI_H_

//#include "stm32f1xx.h"
#include "stdio.h"
#include "string.h"
#include "protocol.h"
#include "system.h"
#include "mcu_api.h"


//=============================================================================
//���峣��
//������뷢������: #40: eWIFIDISABLE an identifier  DISABLE = 0, ���������Ĵ�����ʾ�����԰���ͷ�ļ� #include "stm32f1xx.h" �����
//=============================================================================
#ifndef TRUE
#define      TRUE                1
#endif

#ifndef FALSE
#define         FALSE            0
#endif

#ifndef NULL
#define         NULL             ((void *) 0)
#endif

#ifndef WIFISUCCESS
#define         WIFISUCCESS          1
#endif

#ifndef WIFIERROR
#define         WIFIERROR            0
#endif

#ifndef INVALID
#define         INVALID          0xFF
#endif

#ifndef WIFIENABLE
#define         WIFIENABLE           1
#endif

#ifndef WIFIDISABLE
#define         WIFIDISABLE          0
#endif
//=============================================================================
//dp���ݵ�����
//=============================================================================
#define         DP_TYPE_RAW                     0x00        //RAW ����
#define         DP_TYPE_BOOL                    0x01        //bool ����
#define         DP_TYPE_VALUE                   0x02        //value ����
#define         DP_TYPE_STRING                  0x03        //string ����
#define         DP_TYPE_ENUM                    0x04        //enum ����
#define         DP_TYPE_BITMAP                  0x05        //fault ����

//=============================================================================
//WIFI����״̬
//=============================================================================
#define         SMART_CONFIG_STATE              0x00
#define         AP_STATE                        0x01
#define         WIFI_NOT_CONNECTED              0x02
#define         WIFI_CONNECTED                  0x03
#define         WIFI_CONN_CLOUD                 0x04
#define         WIFI_LOW_POWER                  0x05
#define         SMART_AND_AP_STATE              0x06
#define         WIFI_SATE_UNKNOW                0xff
//=============================================================================
//wifi�����ķ�ʽ
//=============================================================================
#define         SMART_CONFIG                    0x0  
#define         AP_CONFIG                       0x1   

//=============================================================================
//wifi��λ״̬
//=============================================================================
#define         RESET_WIFI_WIFIERROR                0
#define         RESET_WIFI_WIFISUCCESS              1

//=============================================================================
//wifi���ø�λ״̬
//=============================================================================
#define         SET_WIFICONFIG_WIFIERROR            0
#define         SET_WIFICONFIG_WIFISUCCESS          1

//=============================================================================
//MCU�̼�����״̬
//=============================================================================
#define         FIRM_STATE_UN_SUPPORT           0x00                            //��֧�� MCU ����
#define         FIRM_STATE_WIFI_UN_READY        0x01                            //ģ��δ����
#define         FIRM_STATE_GET_WIFIERROR            0x02                            //�ƶ�������Ϣ��ѯʧ��
#define         FIRM_STATE_NO                   0x03                            //�����������ƶ��޸��°汾��
#define         FIRM_STATE_START                0x04                            //���������ȴ�ģ�鷢����������

//=============================================================================
//WIFI��mcu�Ĺ�����ʽ 
//=============================================================================
#define         UNION_WORK                      0x0                             //mcuģ����wifi��ϴ���
#define         WIFI_ALONE                      0x1                             //wifiģ���Դ���

//=============================================================================
//ϵͳ����ģʽ
//=============================================================================
#define         NORMAL_MODE                     0x00                            //��������״̬
#define         FACTORY_MODE                    0x01                            //����ģʽ	
#define         UPDATE_MODE                     0x02                            //����ģʽ	 

//=============================================================================
//������ʽѡ��
//=============================================================================
#define         CONFIG_MODE_DEFAULT             "0"                             //Ĭ��������ʽ
#define         CONFIG_MODE_LOWPOWER            "1"                             //�͹���������ʽ
#define         CONFIG_MODE_SPECIAL             "2"                             //����������ʽ  




//=============================================================================
//�·�����
//=============================================================================
typedef struct {
  unsigned char dp_id;                              //dp���
  unsigned char dp_type;                            //dp����
} DOWNLOAD_CMD_S;

#endif

