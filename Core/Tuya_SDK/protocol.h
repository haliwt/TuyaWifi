/**********************************Copyright (c)**********************************
**                       ��Ȩ���� (C), 2015-2020, Ϳѻ�Ƽ�
**
**                             http://www.tuya.com
**
*********************************************************************************/
/**
 * @file    protocol.h
 * @author  Ϳѻ�ۺ�Э�鿪����
 * @version v2.5.6
 * @date    2020.12.16
 * @brief                
 *                       *******�ǳ���Ҫ��һ��Ҫ��Ŷ������********
 *          1. �û��ڴ��ļ���ʵ�������·�/�ϱ�����
 *          2. DP��ID/TYPE�����ݴ�����������Ҫ�û�����ʵ�ʶ���ʵ��
 *          3. ����ʼĳЩ�궨�����Ҫ�û�ʵ�ִ���ĺ����ڲ���#err��ʾ,��ɺ�������ɾ����#err
 */

/****************************** �������� ������ *******************************
����MCU���ͺͱ��뻷�����ֶ��������Դ˴�������ο����û������аѿ����մ���������
Ϳѻ����MCU���ܽ������
******************************************************************************/

#ifndef __PROTOCOL_H_
#define __PROTOCOL_H_


/******************************************************************************
                           �û������Ϣ����
******************************************************************************/
/******************************************************************************
                       1:�޸Ĳ�Ʒ��Ϣ
******************************************************************************/
#define PRODUCT_KEY "zivxwtzw0adtg0jg"    //����ƽ̨������Ʒ�����ɵ�16λ�ַ���ƷΨһ��ʶ

#define MCU_VER "1.0.0"         //�û��������汾,����MCU�̼�����,MCU�����汾���޸�

/*  ģ�鹤����ʽѡ��,ֻ����ѡһ,�Ƽ�ʹ�÷���ģʽ  */
//#define CONFIG_MODE     CONFIG_MODE_DEFAULT             //Ĭ�Ϲ���ģʽ
//#define CONFIG_MODE     CONFIG_MODE_LOWPOWER            //��ȫģʽ (�͹���������ʽ)
#define CONFIG_MODE     CONFIG_MODE_SPECIAL             //����ģʽ(����������ʽ)

/*  ���õ͹���������ʽ������������ʽ������ģʽ��ʱ��,�ú괦��ע��״̬���������Ӵ���,����֧�ֵ��������ݷ�Χ: 3~10 ����  */
//#define CONFIG_MODE_DELAY_TIME    10         //����ģʽ��ʱ�� ��λ:����

/*  ѡ��smartģʽ��APģʽ,�ú궼ע�ͽ�����smartģʽ��APģʽ�����л�  */
//#define CONFIG_MODE_CHOOSE        0         //ģ��ͬʱ֧��AP����������EZ���������û��л�,��Ӧ������״̬0x06
//#define CONFIG_MODE_CHOOSE        1         //��ֻ��AP����ģʽ

/*  ����ģ��ĺ��⹦�ܲ���֪ģ�������շ���ʹ����ЩIO�ڣ�û�и��ֶκ�������Ĭ�Ϲر�  */
//#define WIFIENABLE_MODULE_IR_FUN                  //����ģ��ĺ��⹦��
#ifdef WIFIENABLE_MODULE_IR_FUN
#define MODULE_IR_PIN_TX      5       //���ⷢ�ͽ�
#define MODULE_IR_PIN_RX      12      //������ս�
#endif

/*  ģ���Ƿ������ֳ����ӵĵ͹���ģʽ��û�и��ֶε͹���ģʽĬ�Ϲر�  */
//#define LONG_CONN_LOWPOWER        0         //�رյ͹���ģʽ
//#define LONG_CONN_LOWPOWER        1         //�򿪵͹���ģʽ

/******************************************************************************
                          2:MCU�Ƿ���Ҫ֧�̼�����
����Ҫ֧��MCU�̼�����,�뿪���ú�
MCU�ɵ���mcu_api.c�ļ��ڵ�mcu_firm_update_query()������ȡ��ǰMCU�̼��������
                        ********WARNING!!!**********
��ǰ���ջ�����Ϊ�رչ̼����¹��ܵĴ�С,�̼���������ѡ��Ĭ��256�ֽڴ�С
����Ҫ�����ù���,���ڽ��ջ���������
******************************************************************************/
//#define         SUPPORT_MCU_FIRM_UPDATE                 //����MCU�̼���������(Ĭ�Ϲر�)
/*  Firmware package size selection  */
#ifdef SUPPORT_MCU_FIRM_UPDATE
#define PACKAGE_SIZE                   0        //����СΪ256�ֽ�
//#define PACKAGE_SIZE                   1        //����СΪ512�ֽ�
//#define PACKAGE_SIZE                   2        //����СΪ1024�ֽ�
#endif
/******************************************************************************
                         3:�����շ�����:
                    �統ǰʹ��MCU��RAM����,���޸�Ϊ24
******************************************************************************/
#ifndef SUPPORT_MCU_FIRM_UPDATE
#define WIFI_UART_RECV_BUF_LMT          16              //�������ݽ��ջ�������С,��MCU��RAM����,����С
#define WIFI_DATA_PROCESS_LMT           24              //�������ݴ�����������С,�����û�DP���ݴ�С����,�������24
#else
#define WIFI_UART_RECV_BUF_LMT          128             //�������ݽ��ջ�������С,��MCU��RAM����,����С

//���ڴ˴�ѡ����ʵĴ������ݴ��������С����������MCU�̼�������ѡ��Ĵ�С���Ƿ�������������ѡ�������Ļ��棩
#define WIFI_DATA_PROCESS_LMT           300             //�������ݴ��������С,����MCU�̼�����,��������Сѡ��256,�򻺴�������260,��������������,����Ҫ����
//#define WIFI_DATA_PROCESS_LMT           600             //�������ݴ��������С,����MCU�̼�����,��������Сѡ��512,�򻺴�������520,��������������,����Ҫ����
//#define WIFI_DATA_PROCESS_LMT           1200            //�������ݴ��������С,����MCU�̼�����,��������Сѡ��1024,�򻺴�������1030,��������������,����Ҫ����

#endif

#define WIFIR_UART_SEND_BUF_LMT         48              //�����û�DP���ݴ�С����,�������48
/******************************************************************************
                        4:����ģ�鹤����ʽ
ģ���Դ���:
          wifiָʾ�ƺ�wifi��λ��ť����wifiģ����(����WIFI_CONTROL_SELF_MODE��)
          ����ȷ����WF_STATE_KEY��WF_RESET_KEY
MCU�Դ���:
          wifiָʾ�ƺ�wifi��λ��ť����MCU��(�ر�WIFI_CONTROL_SELF_MODE��)
          MCU����Ҫ������λwifi�ĵط�����mcu_api.c�ļ��ڵ�mcu_reset_wifi()����,���ɵ���mcu_get_reset_wifi_flag()�������ظ�λwifi���
          ���������wifiģʽmcu_api.c�ļ��ڵ�mcu_set_wifi_mode(WIFI_CONFIG_E mode)����,���ɵ���mcu_get_wifi_work_state()������������wifi���
******************************************************************************/
//#define         WIFI_CONTROL_SELF_MODE                       //wifi�Դ���������LEDָʾ��;��ΪMCU��簴��/LEDָʾ����رոú�
#ifdef          WIFI_CONTROL_SELF_MODE                      //ģ���Դ���
  #define     WF_STATE_KEY            14                    //wifiģ��״ָ̬ʾ�����������ʵ��GPIO�ܽ�����
  #define     WF_RESERT_KEY           0                     //wifiģ�����ð����������ʵ��GPIO�ܽ�����
#endif

/******************************************************************************
                      5:MCU�Ƿ���Ҫ֧��Уʱ����
����Ҫ�뿪���ú�,����Protocol.c�ļ���mcu_write_rtctimeʵ�ִ���
mcu_write_rtctime�ڲ���#err��ʾ,��ɺ�������ɾ����#err
mcu��wifiģ����ȷ������ɵ���mcu_get_system_time()��������Уʱ����
******************************************************************************/
//#define         SUPPORT_MCU_RTC_CHECK                //����Уʱ����

/******************************************************************************
                      6:MCU�Ƿ���Ҫ֧��wifi���ܲ���
����Ҫ�뿪���ú�,����mcu����Ҫwifi���ܲ��Դ�����mcu_api.c�ļ���mcu_start_wifitest
����protocol.c�ļ�wifi_test_result�����ڲ鿴���Խ��,
wifi_test_result�ڲ���#err��ʾ,��ɺ�������ɾ����#err
******************************************************************************/
#define         WIFI_TEST_WIFIENABLE                //����WIFI���⹦�ܣ�ɨ��ָ��·�ɣ�

/******************************************************************************
                      7:�Ƿ�����������
����Ҫ�뿪���ú�,����protocol.c�ļ���weather_open_return_handle��weather_data_user_handle�����û�����������ʵ����ʾ�ȴ���
����������#err��ʾ,��ɺ�������ɾ����#err
�����������ܣ��������ݻ������Ĵ�СҪ����һЩ
******************************************************************************/
//#define         WEATHER_WIFIENABLE                  //����������
#ifdef          WEATHER_WIFIENABLE
/*  ��protocol.c�ļ���weather_choose�����пɵ�����Ȼ�󽫴򿪷����������Ŀд���˺궨��  */
#define         WEATHER_CHOOSE_CNT              4   //ѡ�����Ҫ�����������͵���Ŀ
/*  �ڴ���������ʱ���������ô˺궨��ѡ������Ԥ����������1��ʾ��������(����ҪԤ��������Ϊ1)�����Ϊ7��(���������ó�0�����7)  */
#define         WEATHER_FORECAST_DAYS_NUM       1   //��������Ԥ��������
#endif

/******************************************************************************
                      8:�Ƿ���WIFIģ�������رչ���
����Ҫ�뿪���ú�,����mcu_api.c�ļ���wifi_heart_stop��������ֹͣ����
******************************************************************************/
//#define         WIFI_HEARTSTOP_WIFIENABLE           //��������ֹͣ����

/******************************************************************************
                      9:�Ƿ�֧����������
STREM_PACK_LENΪ��������һ���Ĵ�С��Ŀǰģ�鴮�������Ի�������ݲ��ֿ��Դﵽ 1024 �ֽڣ�һ����ͼ 
���ݰ����ݲ��ֲ��ܳ��� 1024 �ֽڣ�ÿ����ͼ�������ݽ��� 512 �ֽ�ÿ����
******************************************************************************/
//#define         WIFI_STREAM_WIFIENABLE              //֧����������ع���
#ifdef WIFI_STREAM_WIFIENABLE
#define         STREM_PACK_LEN                 256
#endif

/******************************************************************************
                      10:MCU�Ƿ���Ҫ֧��wifi���ܲ���(����ָ��·��)
����Ҫ�뿪���ú�,����mcu����Ҫwifi���ܲ��Դ�����mcu_api.c�ļ���mcu_start_connect_wifitest
����protocol.c�ļ�wifi_connect_test_result�����ڲ鿴���Խ��,
wifi_connect_test_result�ڲ���#err��ʾ,��ɺ�������ɾ����#err
******************************************************************************/
//#define         WIFI_CONNECT_TEST_WIFIENABLE                //����WIFI���⹦�ܣ�����ָ��·�ɣ�

/******************************************************************************
                      11:MCU�Ƿ���Ҫ������ȡ��ǰWIFI����״̬����
����Ҫ�뿪���ú�,����mcu����Ҫ��ȡ��ǰWIFI����״̬������mcu_api.c�ļ���mcu_get_wifi_connect_status
����protocol.c�ļ�wifi_test_result�����ڲ鿴���,
wifi_test_result�ڲ���#err��ʾ,��ɺ�������ɾ����#err
******************************************************************************/
//#define         GET_WIFI_STATUS_WIFIENABLE                  //������ȡ��ǰWIFI����״̬����

/******************************************************************************
                      12:MCU�Ƿ���Ҫ������ȡģ��mac��ַ����
����Ҫ�뿪���ú�,����mcu����Ҫ��ȡģ��mac��ַ������mcu_api.c�ļ���mcu_get_module_mac
����protocol.c�ļ�mcu_get_mac�����ڲ鿴���,
mcu_get_mac�ڲ���#err��ʾ,��ɺ�������ɾ����#err
******************************************************************************/
//#define         GET_MODULE_MAC_WIFIENABLE                   //������ȡģ��mac��ַ����

/******************************************************************************
                      13:MCU�Ƿ���Ҫ֧�ֻ�ȡ����ʱ�书��
����Ҫ�뿪���ú�,����mcu����Ҫ��ȡ����ʱ�䴦����mcu_api.c�ļ���mcu_get_green_time
����protocol.c�ļ�mcu_get_greentime�����ڲ鿴���,
mcu_get_greentime�ڲ���#err��ʾ,��ɺ�������ɾ����#err
mcu��wifiģ����ȷ������ɵ���mcu_get_green_time()��������Уʱ����
******************************************************************************/
//#define         SUPPORT_GREEN_TIME                //��������ʱ�书��

/******************************************************************************
                      14:MCU�Ƿ���Ҫ����ͬ��״̬�ϱ�����
1) ������Ϊͬ��ָ�MCU ����״̬�ϱ�����Ҫ�ȴ�ģ�鷵�ؽ����
2) ÿ�η���ģ�鶼������Ӧ��WIFI ģ��δ��Ӧǰ���ɶ���ϱ���
3) ���粻�ã��������Լ�ʱ�ϱ�ʱ��ģ����� 5 �󷵻�ʧ�ܣ�MCU ��Ҫ�ȴ����� 5 �롣
******************************************************************************/
//#define         MCU_DP_UPLOAD_SYN                   //����ͬ��״̬�ϱ�����

/******************************************************************************
                      15:MCU�Ƿ���Ҫ��������״̬֪ͨ����
����Ҫ�뿪���ú�,
����protocol.c�ļ�get_ir_status�����ڲ鿴������ظ�,
get_ir_status�ڲ���#err��ʾ,��ɺ�������ɾ����#err
******************************************************************************/
//#define         GET_IR_STATUS_WIFIENABLE                   //��������״̬֪ͨ����

/******************************************************************************
                      16:MCU�Ƿ���Ҫ������������շ����⹦��
����Ҫ�뿪���ú�,����mcu����Ҫ������������շ����⴦����mcu_api.c�ļ���mcu_start_ir_test
����protocol.c�ļ�ir_tx_rx_test_result�����ڲ鿴���Խ��,
ir_tx_rx_test_result�ڲ���#err��ʾ,��ɺ�������ɾ����#err
******************************************************************************/
//#define         IR_TX_RX_TEST_WIFIENABLE                   //������������շ����⹦��

/******************************************************************************
                      17:�ļ������ع���
����Ҫ�뿪���ú�,������Ҫѡ�����С
����protocol.c�ļ�file_download_handle������������,
file_download_handle�ڲ���#err��ʾ,��ɺ�������ɾ����#err
******************************************************************************/
//#define         FILE_DOWNLOAD_WIFIENABLE                   //�����ļ������ع���
//�ļ����ذ���Сѡ��
#ifdef FILE_DOWNLOAD_WIFIENABLE
#define FILE_DOWNLOAD_PACKAGE_SIZE                   0        //����СΪ256�ֽ�
//#define FILE_DOWNLOAD_PACKAGE_SIZE                   1        //����СΪ512�ֽ�
//#define FILE_DOWNLOAD_PACKAGE_SIZE                   2        //����СΪ1024�ֽ�
#endif

/******************************************************************************
                      18:MCU�Ƿ���Ҫ֧������ģ�����Э�鹦��
��Э��ֻ��������ģ��VWXR2��ͨ�öԽӣ�����������ģ���ͨ�ù̼�û�б�Ŀ¼�����Э�鹦��
����Ҫ�뿪���ú�,����mcu����Ҫ����ģ�����Э�鹦�ܴ�����mcu_api.c�ļ���
get_voice_state/set_voice_MIC_silence/set_speaker_voice/voice_test/voice_awaken_test�⼸������
����protocol.c�ļ���ؽ�����������ڲ鿴���,
������������ڲ���#err��ʾ,��ɺ�������ɾ����#err
******************************************************************************/
//#define         VOICE_MODULE_PROTOCOL_WIFIENABLE           //��������ģ�����Э�鹦��

/******************************************************************************
                      19:MCU�Ƿ���Ҫ֧��ģ����չ������
����Ҫ�뿪���ú�,����mcu����Ҫģ����չ���񴦵���mcu_api.c�ļ���open_module_time_serve
����protocol.c�ļ�open_module_time_serve_result�����ڲ鿴���,
open_module_time_serve_result�ڲ���#err��ʾ,��ɺ�������ɾ����#err
******************************************************************************/
//#define         MODULE_EXPANDING_SERVICE_WIFIENABLE        //����ģ����չ������

/******************************************************************************
                      20:MCU�Ƿ���Ҫ֧��������ع���
����Ҫ�뿪���ú�,����mcu����Ҫ������ع��ܴ�����mcu_api.c�ļ���mcu_start_BLE_test
����protocol.c�ļ�BLE_test_result�����ڲ鿴���Խ��,
BLE_test_result�ڲ���#err��ʾ,��ɺ�������ɾ����#err
******************************************************************************/
//#define         BLE_RELATED_FUNCTION_WIFIENABLE            //����������ع���




/******************************************************************************
                        1:dp���ݵ����к����¶���
          **��Ϊ�Զ����ɴ���,���ڿ���ƽ̨������޸�����������MCU_SDK**         
******************************************************************************/
//����(���·����ϱ�)
//��ע:
#define DPID_START 1
//ģʽ(���·����ϱ�)
//��ע:
#define DPID_MODE 2
//���ϸ澯(ֻ�ϱ�)
//��ע:
#define DPID_FAULT 6
//�¶�(���·����ϱ�)
//��ע:
#define DPID_TEMP 101
//ɱ��(���·����ϱ�)
//��ע:
#define DPID_KILL 102
//����(���·����ϱ�)
//��ע:
#define DPID_HEAT 103
//���ö�ʱʱ��(���·����ϱ�)
//��ע:
#define DPID_TIM 104



/**
 * @brief  ���ڷ�������
 * @param[in] {value} ����Ҫ���͵�1�ֽ�����
 * @return Null
 */
void uart_transmit_output(unsigned char value);

/**
 * @brief  ϵͳ����dp����Ϣ�ϴ�,ʵ��APP��muc����ͬ��
 * @param  Null
 * @return Null
 * @note   MCU����ʵ�ָú����������ϱ�����
 */
void all_data_update(void);

/**
 * @brief  dp�·���������
 * @param[in] {dpid} dpid ���
 * @param[in] {value} dp���ݻ�������ַ
 * @param[in] {length} dp���ݳ���
 * @return dp�������
 * -           0(WIFIERROR): ʧ��
 * -           1(WIFISUCCESS): �ɹ�
 * @note   �ú����û������޸�
 */
unsigned char dp_download_handle(unsigned char dpid,const unsigned char value[], unsigned short length);

/**
 * @brief  ��ȡ����dp�����ܺ�
 * @param[in] Null
 * @return �·������ܺ�
 * @note   �ú����û������޸�
 */
unsigned char get_download_cmd_total(void);



#ifdef SUPPORT_MCU_FIRM_UPDATE
/**
 * @brief  ��������Сѡ��
 * @param[in] {package_sz} ��������С
 * @ref           0x00: 256byte (Ĭ��)
 * @ref           0x01: 512byte
 * @ref           0x02: 1024byte
 * @return Null
 * @note   MCU��Ҫ����ʵ�ָù���
 */
void upgrade_package_choose(unsigned char package_sz);

/**
 * @brief  MCU����̼�����ģʽ
 * @param[in] {value} �̼�������
 * @param[in] {position} ��ǰ���ݰ����ڹ̼�λ��
 * @param[in] {length} ��ǰ�̼�������(�̼�������Ϊ0ʱ,��ʾ�̼����������)
 * @return Null
 * @note   MCU��Ҫ����ʵ�ָù���
 */
unsigned char mcu_firm_update_handle(const unsigned char value[],unsigned long position,unsigned short length);
#endif

#ifdef SUPPORT_GREEN_TIME
/**
 * @brief  ��ȡ���ĸ���ʱ��
 * @param[in] {time} ��ȡ���ĸ���ʱ������
 * @return Null
 * @note   MCU��Ҫ����ʵ�ָù���
 */
void mcu_get_greentime(unsigned char time[]);
#endif

#ifdef SUPPORT_MCU_RTC_CHECK
/**
 * @brief  MCUУ�Ա���RTCʱ��
 * @param[in] {time} ��ȡ���ĸ���ʱ������
 * @return Null
 * @note   MCU��Ҫ����ʵ�ָù���
 */
void mcu_write_rtctime(unsigned char time[]);
#endif

#ifdef WIFI_TEST_WIFIENABLE
/**
 * @brief  wifi���ܲ��Է���
 * @param[in] {result} wifi���ܲ��Խ��
 * @ref       0: ʧ��
 * @ref       1: �ɹ�
 * @param[in] {rssi} ���Գɹ���ʾwifi�ź�ǿ��/����ʧ�ܱ�ʾ��������
 * @return Null
 * @note   MCU��Ҫ����ʵ�ָù���
 */
void wifi_test_result(unsigned char result,unsigned char rssi);
#endif

#ifdef WEATHER_WIFIENABLE
/**
* @brief  mcu����������
 * @param  Null
 * @return Null
 */
void mcu_open_weather(void);

/**
 * @brief  ���������ܷ����û��Դ�������
 * @param[in] {res} ���������ܷ��ؽ��
 * @ref       0: ʧ��
 * @ref       1: �ɹ�
 * @param[in] {err} ������
 * @return Null
 * @note   MCU��Ҫ����ʵ�ָù���
 */
void weather_open_return_handle(unsigned char res, unsigned char err);

/**
 * @brief  ���������û��Դ�������
 * @param[in] {name} ������
 * @param[in] {type} ��������
 * @ref       0: int ��
 * @ref       1: string ��
 * @param[in] {data} ����ֵ�ĵ�ַ
 * @param[in] {day} ��һ�������  0:��ʾ���� ȡֵ��Χ: 0~6
 * @ref       0: ����
 * @ref       1: ����
 * @return Null
 * @note   MCU��Ҫ����ʵ�ָù���
 */
void weather_data_user_handle(char *name, unsigned char type, const unsigned char *data, char day);
#endif

#ifdef MCU_DP_UPLOAD_SYN
/**
 * @brief  ״̬ͬ���ϱ����
 * @param[in] {result} ���
 * @ref       0: ʧ��
 * @ref       1: �ɹ�
 * @return Null
 * @note   MCU��Ҫ����ʵ�ָù���
 */
void get_upload_syn_result(unsigned char result);
#endif

#ifdef GET_WIFI_STATUS_WIFIENABLE
/**
 * @brief  ��ȡ WIFI ״̬���
 * @param[in] {result} ָʾ WIFI ����״̬
 * @ref       0x00: wifi״̬ 1 smartconfig ����״̬
 * @ref       0x01: wifi״̬ 2 AP ����״̬
 * @ref       0x02: wifi״̬ 3 WIFI �����õ�δ����·����
 * @ref       0x03: wifi״̬ 4 WIFI ������������·����
 * @ref       0x04: wifi״̬ 5 ������·���������ӵ��ƶ�
 * @ref       0x05: wifi״̬ 6 WIFI �豸���ڵ͹���ģʽ
 * @ref       0x06: wifi״̬ 7 WIFI �豸����smartconfig&AP����״̬
 * @return Null
 * @note   MCU��Ҫ����ʵ�ָù���
 */
void get_wifi_status(unsigned char result);
#endif

#ifdef WIFI_STREAM_WIFIENABLE
/**
 * @brief  �������ͽ��
 * @param[in] {result} ���
 * @ref       0x00: �ɹ�
 * @ref       0x01: ��������δ����
 * @ref       0x02: ��������δ���ӳɹ�
 * @ref       0x03: �������ͳ�ʱ
 * @ref       0x04: ��������ݳ��ȴ���
 * @return Null
 * @note   MCU��Ҫ����ʵ�ָù���
 */
void stream_trans_send_result(unsigned char result);

/**
 * @brief  ���ͼ�������ͽ��
 * @param[in] {result} ���
 * @ref       0x00: �ɹ�
 * @ref       0x01: ʧ��
 * @return Null
 * @note   MCU��Ҫ����ʵ�ָù���
 */
void maps_stream_trans_send_result(unsigned char result);
#endif

#ifdef WIFI_CONNECT_TEST_WIFIENABLE
/**
 * @brief  ·����Ϣ���ս��֪ͨ
 * @param[in] {result} ģ���Ƿ�ɹ����յ���ȷ��·����Ϣ
 * @ref       0x00: ʧ��
 * @ref       0x01: �ɹ�
 * @return Null
 * @note   MCU��Ҫ����ʵ�ָù���
 */
void wifi_connect_test_result(unsigned char result);
#endif

#ifdef GET_MODULE_MAC_WIFIENABLE
/**
 * @brief  ��ȡģ��mac���
 * @param[in] {mac} ģ�� MAC ����
 * @ref       mac[0]: Ϊ�Ƿ��ȡmac�ɹ���־��0x00 ��ʾ�ɹ���0x01 ��ʾʧ��
 * @ref       mac[1]~mac[6]: ����ȡ MAC��ַ��־λ���mac[0]Ϊ�ɹ������ʾģ����Ч��MAC��ַ
 * @return Null
 * @note   MCU��Ҫ����ʵ�ָù���
 */
void mcu_get_mac(unsigned char mac[]);
#endif

#ifdef GET_IR_STATUS_WIFIENABLE
/**
 * @brief  ��ȡ����״̬���
 * @param[in] {result} ָʾ����״̬
 * @ref       0x00: ����״̬ 1 ���ڷ��ͺ�����
 * @ref       0x01: ����״̬ 2 ���ͺ��������
 * @ref       0x02: ����״̬ 3 ����ѧϰ��ʼ
 * @ref       0x03: ����״̬ 4 ����ѧϰ����
 * @return Null
 * @note   MCU��Ҫ����ʵ�ָù���
 */
void get_ir_status(unsigned char result);
#endif

#ifdef IR_TX_RX_TEST_WIFIENABLE
/**
 * @brief  ��������շ�������֪ͨ
 * @param[in] {result} ģ���Ƿ�ɹ����յ���ȷ����Ϣ
 * @ref       0x00: ʧ��
 * @ref       0x01: �ɹ�
 * @return Null
 * @note   MCU��Ҫ����ʵ�ָù���
 */
void ir_tx_rx_test_result(unsigned char result);
#endif

#ifdef FILE_DOWNLOAD_WIFIENABLE
/**
 * @brief  �ļ����ذ���Сѡ��
 * @param[in] {package_sz} �ļ����ذ���С
 * @ref       0x00: 256 byte (Ĭ��)
 * @ref       0x01: 512 byte
 * @ref       0x02: 1024 byte
 * @return Null
 * @note   MCU��Ҫ����ʵ�ָù���
 */
void file_download_package_choose(unsigned char package_sz);

/**
 * @brief  �ļ�������ģʽ
 * @param[in] {value} ���ݻ�����
 * @param[in] {position} ��ǰ���ݰ������ļ�λ��
 * @param[in] {length} ��ǰ�ļ�������(����Ϊ0ʱ,��ʾ�ļ����������)
 * @return ���ݴ������
 * -           0(WIFIERROR): ʧ��
 * -           1(WIFISUCCESS): �ɹ�
 * @note   MCU��Ҫ����ʵ�ָù���
 */
unsigned char file_download_handle(const unsigned char value[],unsigned long position,unsigned short length);
#endif

#ifdef MODULE_EXPANDING_SERVICE_WIFIENABLE
/**
 * @brief  ��ģ��ʱ�����֪ͨ���
 * @param[in] {value} ���ݻ�����
 * @param[in] {length} ���ݳ���
 * @return Null
 * @note   MCU��Ҫ����ʵ�ָù���
 */
void open_module_time_serve_result(const unsigned char value[], unsigned short length);
#endif

#ifdef BLE_RELATED_FUNCTION_WIFIENABLE
/**
 * @brief  ���������Բ��Խ��
 * @param[in] {value} ���ݻ�����
 * @param[in] {length} ���ݳ���
 * @return Null
 * @note   MCU��Ҫ����ʵ�ָù���
 */
void BLE_test_result(const unsigned char value[], unsigned short length);
#endif

#ifdef VOICE_MODULE_PROTOCOL_WIFIENABLE
/**
 * @brief  ��ȡ����״̬����
 * @param[in] {result} ����״̬��
 * @ref       0x00: ����
 * @ref       0x01: mic����״̬
 * @ref       0x02: ����
 * @ref       0x03: ����¼��
 * @ref       0x04: ����ʶ��
 * @ref       0x05: ʶ��ɹ�
 * @ref       0x06: ʶ��ʧ��
 * @return Null
 * @note   MCU��Ҫ����ʵ�ָù���
 */
void get_voice_state_result(unsigned char result);

/**
 * @brief  MIC��������
 * @param[in] {result} ����״̬��
 * @ref       0x00: mic ����
 * @ref       0x01: mic ����
 * @return Null
 * @note   MCU��Ҫ���е��øù���
 */
void set_voice_MIC_silence_result(unsigned char result);

/**
 * @brief  speaker�������ý��
 * @param[in] {result} ����ֵ
 * @ref       0~10: ������Χ
 * @return Null
 * @note   MCU��Ҫ���е��øù���
 */
void set_speaker_voice_result(unsigned char result);

/**
 * @brief  ��Ƶ������
 * @param[in] {result} ��Ƶ����״̬
 * @ref       0x00: �ر���Ƶ����
 * @ref       0x01: mic1��Ƶ��·����
 * @ref       0x02: mic2��Ƶ��·����
 * @return Null
 * @note   MCU��Ҫ���е��øù���
 */
void voice_test_result(unsigned char result);

/**
 * @brief  ���Ѳ�����
 * @param[in] {result} ���ѷ���ֵ
 * @ref       0x00: ���ѳɹ�
 * @ref       0x01: ����ʧ��(10s��ʱʧ��)
 * @return Null
 * @note   MCU��Ҫ���е��øù���
 */
void voice_awaken_test_result(unsigned char result);

/**
 * @brief  ����ģ����չ����
 * @param[in] {value} ���ݻ�����
 * @param[in] {length} ���ݳ���
 * @return Null
 * @note   MCU��Ҫ����ʵ�ָù���
 */
void voice_module_extend_fun(const unsigned char value[], unsigned short length);
#endif


#endif


