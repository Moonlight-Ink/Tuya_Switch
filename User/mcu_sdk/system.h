/****************************************Copyright (c)*************************
**                               ��Ȩ���� (C), 2015-2020, Ϳѻ�Ƽ�
**
**                                 http://www.tuya.com
**
**--------------�ļ���Ϣ-------------------------------------------------------
**��   ��   ��: system.c
**��        ��: wifi���ݴ�����
**ʹ �� ˵ �� : �û�������ĸ��ļ�ʵ������
**
**
**--------------��ǰ�汾�޶�---------------------------------------------------
** ��  ��: v2.3.7
** �ա���: 2017��4��18��
** �衡��: 1:�Ż����ڶ��н��մ���
		   
** ��  ��: v2.3.6
** �ա���: 2016��7��21��
** �衡��: 1:�޸���ȡ����ʱ�����
           2:���hex_to_bcdת������
		   
** ��  ��: v2.3.5
** �ա���: 2016��6��3��
** �衡��: 1:�޸ķ���Э��汾Ϊ0x01
           2:�̼���������ƫ�����޸�Ϊ4�ֽ�

** ��  ��: v2.3.4
** �ա���: 2016��5��26��
** �衡��: 1:�Ż����ڽ�������
           2:�Ż�������������,ȡ��enum���Ͷ���

** ��  ��: v2.3.3
** �ա���: 2016��5��24��
** �衡��: 1:�޸�mcu��ȡ����ʱ�亯��
           2:���wifi���ܲ���

** ��  ��: v2.3.2
** �ա���: 2016��4��23��
** �衡��: 1:�Ż��������ݽ���
           2:�Ż�MCU�̼���������
           3:�Ż��ϱ�����

** ��  ��: v2.3.1
** �ա���: 2016��4��15��
** �衡��: 1:�Ż��������ݽ���

** ��  ��: v2.3
** �ա���: 2016��4��14��
** �衡��: 1:֧��MCU�̼���������

** ��  ��: v2.2
** �ա���: 2016��4��11��
** �衡��: 1:�޸Ĵ������ݽ��շ�ʽ

** ��  ��: v2.1
** �ա���: 2016��4��8��
** �衡��: 1:����ĳЩ��������֧�ֺ���ָ�����ѡ��

** ��  ��: v2.0
** �ա���: 2016��3��29��
** �衡��: 1:�Ż�����ṹ
2:��ʡRAM�ռ�
**
**-----------------------------------------------------------------------------
******************************************************************************/
#ifndef __SYSTEM_H_
#define __SYSTEM_H_

#ifdef SYSTEM_GLOBAL
  #define SYSTEM_EXTERN
#else
  #define SYSTEM_EXTERN   extern
#endif

//=============================================================================
//֡���ֽ�˳��
//=============================================================================
#define         HEAD_FIRST                      0
#define         HEAD_SECOND                     1        
#define         PROTOCOL_VERSION                2
#define         FRAME_TYPE                      3
#define         LENGTH_HIGH                     4
#define         LENGTH_LOW                      5
#define         DATA_START                      6

//=============================================================================
//����֡����
//=============================================================================
#define         HEAT_BEAT_CMD                   0                               //������
#define         PRODUCT_INFO_CMD                1                               //��Ʒ��Ϣ
#define         WORK_MODE_CMD                   2                               //��ѯMCU �趨��ģ�鹤��ģʽ	
#define         WIFI_STATE_CMD                  3                               //wifi����״̬	
#define         WIFI_RESET_CMD                  4                               //����wifi
#define         WIFI_MODE_CMD                   5                               //ѡ��smartconfig/APģʽ	
#define         DATA_QUERT_CMD                  6                               //�����·�
#define         STATE_UPLOAD_CMD                7                               //״̬�ϱ�	 
#define         STATE_QUERY_CMD                 8                               //״̬��ѯ   
#define         UPDATE_QUERY_CMD                9                               //������ѯ
#define         UPDATE_START_CMD                0x0a                            //������ʼ
#define         UPDATE_TRANS_CMD                0x0b                            //��������
#define         GET_ONLINE_TIME_CMD             0x0c                            //��ȡϵͳʱ��(��������ʱ��)
#define         FACTORY_MODE_CMD                0x0d                            //�������ģʽ    
#define         WIFI_TEST_CMD                   0x0e                            //wifi���ܲ���
#define         GET_LOCAL_TIME_CMD              0x1c                            //��ȡ����ʱ��                         


//=============================================================================
#define VERSION                 0x00                                            //Э��汾��
#define PROTOCOL_HEAD           0x07                                            //�̶�Э��ͷ����
#define FIRM_UPDATA_SIZE        256                                            //��������С
#define FRAME_FIRST             0x55
#define FRAME_SECOND            0xaa
//============================================================================= 
SYSTEM_EXTERN unsigned char volatile wifi_queue_buf[PROTOCOL_HEAD + WIFI_UART_QUEUE_LMT];  //���ڶ��л���
SYSTEM_EXTERN unsigned char wifi_uart_rx_buf[PROTOCOL_HEAD + WIFI_UART_RECV_BUF_LMT];         //���ڽ��ջ���
SYSTEM_EXTERN unsigned char wifi_uart_tx_buf[PROTOCOL_HEAD + WIFIR_UART_SEND_BUF_LMT];        //���ڷ��ͻ���
//
SYSTEM_EXTERN volatile unsigned char *queue_in;
SYSTEM_EXTERN volatile unsigned char *queue_out;

SYSTEM_EXTERN unsigned char stop_update_flag;

#ifndef WIFI_CONTROL_SELF_MODE
SYSTEM_EXTERN unsigned char reset_wifi_flag;                                                  //����wifi��־(TRUE:�ɹ�/FALSE:ʧ��)
SYSTEM_EXTERN unsigned char set_wifimode_flag;                                                //����WIFI����ģʽ��־(TRUE:�ɹ�/FALSE:ʧ��)
SYSTEM_EXTERN unsigned char wifi_work_state;                                                  //wifiģ�鵱ǰ����״̬
#endif


/*****************************************************************************
�������� : set_wifi_uart_byte
�������� : дwifi_uart�ֽ�
������� : dest:��������ʵ��ַ;
           byte:д���ֽ�ֵ
���ز��� : д����ɺ���ܳ���
*****************************************************************************/
unsigned short set_wifi_uart_byte(unsigned short dest, unsigned char byte);

/*****************************************************************************
�������� : set_wifi_uart_buffer
�������� : дwifi_uart_buffer
������� : dest:Ŀ���ַ
           src:Դ��ַ
           len:���ݳ���
���ز��� : ��
*****************************************************************************/
unsigned short set_wifi_uart_buffer(unsigned short dest, unsigned char *src, unsigned short len);

/*****************************************************************************
�������� : wifi_uart_write_frame
�������� : ��wifi���ڷ���һ֡����
������� : fr_type:֡����
           len:���ݳ���
���ز��� : ��
*****************************************************************************/
void wifi_uart_write_frame(unsigned char fr_type, unsigned short len);

/*****************************************************************************
�������� : get_check_sum
�������� : ����У���
������� : pack:����Դָ��
           pack_len:����У��ͳ���
���ز��� : У���
*****************************************************************************/
unsigned char get_check_sum(unsigned char *pack, unsigned short pack_len);

/*****************************************************************************
�������� : data_handle
�������� : ����֡����
������� : offset:������ʼλ
���ز��� : ��
*****************************************************************************/
void data_handle(unsigned short offset);

/*****************************************************************************
�������� : get_queue_total_data
�������� : ��ȡ����������
������� : ��
���ز��� : ��
*****************************************************************************/
unsigned char get_queue_total_data(void);

/*****************************************************************************
�������� : Queue_Read_Byte
�������� : ��ȡ����1�ֽ�����
������� : ��
���ز��� : ��
*****************************************************************************/
unsigned char Queue_Read_Byte(void);

#endif
  
  
	
	