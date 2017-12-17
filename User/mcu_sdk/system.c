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
#define SYSTEM_GLOBAL

#include "wifi.h"
//
//
extern const DOWNLOAD_CMD_S download_cmd[];

/*****************************************************************************
�������� : set_wifi_uart_byte
�������� : дwifi_uart�ֽ�
������� : dest:��������ʵ��ַ;
           byte:д���ֽ�ֵ
���ز��� : д����ɺ���ܳ���
*****************************************************************************/
unsigned short set_wifi_uart_byte(unsigned short dest, unsigned char byte)
{
  unsigned char *obj = (unsigned char *)wifi_uart_tx_buf + DATA_START + dest;
  
  *obj = byte;
  dest += 1;
  
  return dest;
}
/*****************************************************************************
�������� : set_wifi_uart_buffer
�������� : дwifi_uart_buffer
������� : dest:Ŀ���ַ
           src:Դ��ַ
           len:���ݳ���
���ز��� : ��
*****************************************************************************/
unsigned short set_wifi_uart_buffer(unsigned short dest, unsigned char *src, unsigned short len)
{
  unsigned char *obj = (unsigned char *)wifi_uart_tx_buf + DATA_START + dest;
  
  my_memcpy(obj,src,len);
  
  dest += len;
  return dest;
}
/*****************************************************************************
�������� : wifi_uart_write_data
�������� : ��wifi uartд����������
������� : in:���ͻ���ָ��
           len:���ݷ��ͳ���
���ز��� : ��
*****************************************************************************/
static void wifi_uart_write_data(unsigned char *in, unsigned short len)
{
  if((NULL == in) || (0 == len))
  {
    return;
  }
  
  while(len --)
  {
    uart_transmit_output(*in);
    in ++;
  }
}
/*****************************************************************************
�������� : get_check_sum
�������� : ����У���
������� : pack:����Դָ��
           pack_len:����У��ͳ���
���ز��� : У���
*****************************************************************************/
unsigned char get_check_sum(unsigned char *pack, unsigned short pack_len)
{
  unsigned short i;
  unsigned char check_sum = 0;
  
  for(i = 0; i < pack_len; i ++)
  {
    check_sum += *pack ++;
  }
  
  return check_sum;
}
/*****************************************************************************
�������� : wifi_uart_write_frame
�������� : ��wifi���ڷ���һ֡����
������� : fr_type:֡����
           len:���ݳ���
���ز��� : ��
*****************************************************************************/
void wifi_uart_write_frame(unsigned char fr_type, unsigned short len)
{
  unsigned char check_sum = 0;
  
  wifi_uart_tx_buf[HEAD_FIRST] = 0x55;
  wifi_uart_tx_buf[HEAD_SECOND] = 0xaa;
  wifi_uart_tx_buf[PROTOCOL_VERSION] = 0x00;
  wifi_uart_tx_buf[FRAME_TYPE] = fr_type;
  wifi_uart_tx_buf[LENGTH_HIGH] = len >> 8;
  wifi_uart_tx_buf[LENGTH_LOW] = len & 0xff;
  
  len += PROTOCOL_HEAD;
  check_sum = get_check_sum((unsigned char *)wifi_uart_tx_buf, len - 1);
  wifi_uart_tx_buf[len - 1] = check_sum;
  //
  wifi_uart_write_data((unsigned char *)wifi_uart_tx_buf, len);
}
/*****************************************************************************
�������� : heat_beat_check
�������� : ���������
������� : ��
���ز��� : ��
*****************************************************************************/
static void heat_beat_check(void)
{
  unsigned char length = 0;
  static unsigned char mcu_reset_state = FALSE;
  
  if(FALSE == mcu_reset_state)
  {
    length = set_wifi_uart_byte(length,FALSE);
    mcu_reset_state = TRUE;
  }
  else
  {
    length = set_wifi_uart_byte(length,TRUE);
  }
  
  wifi_uart_write_frame(HEAT_BEAT_CMD, length);
}
/*****************************************************************************
��������  : product_info_update
��������  : ��Ʒ��Ϣ�ϴ�
������� : ��
���ز��� : ��
*****************************************************************************/
static void product_info_update(void)
{
  unsigned char length = 0;
  
  length = set_wifi_uart_buffer(length,(unsigned char *)PRODUCT_KEY,my_strlen((unsigned char *)PRODUCT_KEY));
  length = set_wifi_uart_buffer(length,(unsigned char *)MCU_VER,my_strlen((unsigned char *)MCU_VER));
  
  wifi_uart_write_frame(PRODUCT_INFO_CMD, length);
}
/*****************************************************************************
�������� : get_mcu_wifi_mode
�������� : ��ѯmcu��wifi�Ĺ���ģʽ
������� : ��
���ز��� : ��
*****************************************************************************/
static void get_mcu_wifi_mode(void)
{
  unsigned char length = 0;
  
#ifdef WIFI_CONTROL_SELF_MODE                                   //ģ���Դ���
  length = set_wifi_uart_byte(length, WF_STATE_KEY);
  length = set_wifi_uart_byte(length, WF_RESERT_KEY);
#else                                                           
  //���账������
#endif
  
  wifi_uart_write_frame(WORK_MODE_CMD, length);
}
/*****************************************************************************
�������� : get_update_dpid_index
�������� : �����ƶ�DPID�������е����
������� : dpid:dpid
���ز��� : index:dp���
*****************************************************************************/
static unsigned char get_dowmload_dpid_index(unsigned char dpid)
{
  unsigned char index;
  unsigned char total = get_download_cmd_total();
  
  for(index = 0; index < total; index ++)
  {
    if(download_cmd[index].dp_id == dpid)
    {
      break;
    }
  }
  
  return index;
}
/*****************************************************************************
�������� : data_point_handle
�������� : �·����ݴ���
������� : value:�·�����Դָ��
���ز��� : ret:�������ݴ�����
*****************************************************************************/
static unsigned char data_point_handle(const unsigned char value[])
{
  unsigned char dp_id,index;
  unsigned char dp_type;
  unsigned char ret;
  unsigned short dp_len;
  
  dp_id = value[0];
  dp_type = value[1];
  dp_len = value[2] * 0x100;
  dp_len += value[3];
  
  index = get_dowmload_dpid_index(dp_id);

  if(dp_type != download_cmd[index].dp_type)
  {
    //������ʾ
    return FALSE;
  }
  else
  {
    ret = dp_download_handle(dp_id,value + 4,dp_len);
  }
  
  return ret;
}
/*****************************************************************************
�������� : data_handle
�������� : ����֡����
������� : offset:������ʼλ
���ز��� : ��
*****************************************************************************/
void data_handle(unsigned short offset)
{
#ifdef SUPPORT_MCU_FIRM_UPDATE
  unsigned char *firmware_addr;
  static unsigned long firm_length;                                             //MCU�����ļ�����
  static unsigned char firm_update_flag;                                        //MCU������־
  unsigned long dp_len;
#else
  unsigned short dp_len;
#endif
  
  unsigned char ret;
  unsigned short i,total_len;
  unsigned char cmd_type = wifi_uart_rx_buf[offset + FRAME_TYPE];
  
  switch(cmd_type)
  {
  case HEAT_BEAT_CMD:                                   //������
    heat_beat_check();
    break;
    
  case PRODUCT_INFO_CMD:                                //��Ʒ��Ϣ
    product_info_update();
    break;
    
  case WORK_MODE_CMD:                                   //��ѯMCU�趨��ģ�鹤��ģʽ
    get_mcu_wifi_mode();
    break;
    
#ifndef WIFI_CONTROL_SELF_MODE
  case WIFI_STATE_CMD:                                  //wifi����״̬	  03
    wifi_work_state = wifi_uart_rx_buf[offset + DATA_START]; //WiFi����ģʽ���� wifi_work_state���ж� 
    wifi_uart_write_frame(WIFI_STATE_CMD,0);
    break;

  case WIFI_RESET_CMD:                                  //����wifi(wifi���سɹ�)
    reset_wifi_flag = RESET_WIFI_SUCCESS;
    break;
    
  case WIFI_MODE_CMD:                                   //ѡ��smartconfig/APģʽ(wifi���سɹ�)	
    set_wifimode_flag = SET_WIFICONFIG_SUCCESS;        
	
    break;
#endif
    
  case DATA_QUERT_CMD:                                  //�����·�
    total_len = wifi_uart_rx_buf[offset + LENGTH_HIGH] * 0x100;
    total_len += wifi_uart_rx_buf[offset + LENGTH_LOW];
    
    for(i = 0;i < total_len;)
    {
      dp_len = wifi_uart_rx_buf[offset + DATA_START + i + 2] * 0x100;
      dp_len += wifi_uart_rx_buf[offset + DATA_START + i + 3];
      //
      ret = data_point_handle((unsigned char *)wifi_uart_rx_buf + offset + DATA_START + i);
      
      if(SUCCESS == ret)
      {
        //�ɹ���ʾ
      }
      else
      {
        //������ʾ
      }
      
      i += (dp_len + 4);
    }
    
    break;
    
  case STATE_QUERY_CMD:                                 //״̬��ѯ
    all_data_update();                               
    break;
    
#ifdef SUPPORT_MCU_FIRM_UPDATE
  case UPDATE_START_CMD:                                //������ʼ
    firm_length = wifi_uart_rx_buf[offset + DATA_START];
    firm_length <<= 8;
    firm_length |= wifi_uart_rx_buf[offset + DATA_START + 1];
    firm_length <<= 8;
    firm_length |= wifi_uart_rx_buf[offset + DATA_START + 2];
    firm_length <<= 8;
    firm_length |= wifi_uart_rx_buf[offset + DATA_START + 3];
    //
    wifi_uart_write_frame(UPDATE_START_CMD,0);
    firm_update_flag = UPDATE_START_CMD;
     break;
    
  case UPDATE_TRANS_CMD:                                //��������
    if(firm_update_flag == UPDATE_START_CMD)
    {
      //ֹͣһ�������ϱ�
      stop_update_flag = ENABLE;                                                 
      
      total_len = wifi_uart_rx_buf[offset + LENGTH_HIGH] * 0x100;
      total_len += wifi_uart_rx_buf[offset + LENGTH_LOW];
      
      dp_len = wifi_uart_rx_buf[offset + DATA_START];
      dp_len <<= 8;
      dp_len |= wifi_uart_rx_buf[offset + DATA_START + 1];
      dp_len <<= 8;
      dp_len |= wifi_uart_rx_buf[offset + DATA_START + 2];
      dp_len <<= 8;
      dp_len |= wifi_uart_rx_buf[offset + DATA_START + 3];
      
      firmware_addr = wifi_uart_rx_buf + offset + DATA_START + 4;
      if((total_len == 4) && (dp_len == firm_length))
      {
        //���һ��
        ret = mcu_firm_update_handle(firmware_addr,dp_len,0);
        
        firm_update_flag = 0;
      }
      else if((total_len - 4) <= FIRM_UPDATA_SIZE)
      {
        ret = mcu_firm_update_handle(firmware_addr,dp_len,total_len - 4);
      }
      else
      {
        firm_update_flag = 0;
        ret = ERROR;
      }
      
      if(ret == SUCCESS)
      {
        wifi_uart_write_frame(UPDATE_TRANS_CMD,0);
      }
      //�ָ�һ�������ϱ�
      stop_update_flag = DISABLE;    
    }
    break;
#endif      
    
#ifdef SUPPORT_MCU_RTC_CHECK
  case GET_LOCAL_TIME_CMD:                             //��ȡ����ʱ��
      mcu_write_rtctime(wifi_uart_rx_buf + offset + DATA_START);
    break;
#endif
 
#ifdef WIFI_TEST_ENABLE
  case WIFI_TEST_CMD:                                   //wifi���ܲ���
    wifi_test_result(wifi_uart_rx_buf[offset + DATA_START],wifi_uart_rx_buf[offset + DATA_START + 1]);
    break;
#endif
    
  default:
    break;
  }
}
/*****************************************************************************
�������� : get_queue_total_data
�������� : ��ȡ����������
������� : ��
���ز��� : ��
*****************************************************************************/
unsigned char get_queue_total_data(void)
{
  if(queue_in != queue_out)
    return 1;
  else
    return 0;
}
/*****************************************************************************
�������� : Queue_Read_Byte
�������� : ��ȡ����1�ֽ�����
������� : ��
���ز��� : ��
*****************************************************************************/
unsigned char Queue_Read_Byte(void)
{
  unsigned char value;
  
  if(queue_out != queue_in)
  {
    //������
    if(queue_out >= (unsigned char *)(wifi_queue_buf + sizeof(wifi_queue_buf)))
    {
      //�����Ѿ���ĩβ
      queue_out = (unsigned char *)(wifi_queue_buf);
    }
    
    value = *queue_out ++;   
  }
  
  return value;
}

