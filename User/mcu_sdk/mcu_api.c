/****************************************Copyright (c)*************************
**                               ��Ȩ���� (C), 2015-2020, Ϳѻ�Ƽ�
**
**                                 http://www.tuya.com
**
**--------------�ļ���Ϣ-------------------------------------------------------
**��   ��   ��: mcu_api.c
**��        ��: �·�/�ϱ����ݴ�����
**ʹ �� ˵ �� : ���ļ��º��������û��޸�,�û���Ҫ���õ��ļ����ڸ��ļ���
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
#define MCU_API_GLOBAL

#include "wifi.h"

/*****************************************************************************
�������� : hex_to_bcd
�������� : hexתbcd
������� : Value_H:���ֽ�/Value_L:���ֽ�
���ز��� : bcd_value:ת����ɺ�����
*****************************************************************************/
unsigned char hex_to_bcd(unsigned char Value_H,unsigned char Value_L)
{
  unsigned char bcd_value;
  
  if((Value_H >= '0') && (Value_H <= '9'))
    Value_H -= '0';
  else if((Value_H >= 'A') && (Value_H <= 'F'))
    Value_H = Value_H - 'A' + 10;
  else if((Value_H >= 'a') && (Value_H <= 'f'))
    Value_H = Value_H - 'a' + 10;
   
  bcd_value = Value_H & 0x0f;
  
  bcd_value <<= 4;
  if((Value_L >= '0') && (Value_L <= '9'))
    Value_L -= '0';
  else if((Value_L >= 'A') && (Value_L <= 'F'))
    Value_L = Value_L - 'a' + 10;
  else if((Value_L >= 'a') && (Value_L <= 'f'))
    Value_L = Value_L - 'a' + 10;
  
  bcd_value |= Value_L & 0x0f;

  return bcd_value;
}
/*****************************************************************************
�������� : my_strlen
�������� : ���ַ�������
������� : src:Դ��ַ
���ز��� : len:���ݳ���
*****************************************************************************/
unsigned long my_strlen(unsigned char *str)  
{
  unsigned long len = 0;
  if(str == NULL)
  { 
    return 0;
  }
  
  for(len = 0; *str ++ != '\0'; )
  {
    len ++;
  }
  
  return len;
}
/*****************************************************************************
�������� : my_memset
�������� : ��src��ָ�ڴ������ǰcount���ֽ����ó��ַ�c
������� : src:Դ��ַ
           ch:�����ַ�
           count:�������ݳ���
���ز��� : src:���ݴ�������Դ��ַ
*****************************************************************************/
void *my_memset(void *src,unsigned char ch,unsigned short count)
{
  unsigned char *tmp = (unsigned char *)src;
  
  if(src == NULL)
  {
    return NULL;
  }
  
  while(count --)
  {
    *tmp ++ = ch;
  }
  
  return src;
}
/*****************************************************************************
�������� : mymemcpy
�������� : �ڴ濽��
������� : dest:Ŀ���ַ
           src:Դ��ַ
           count:���ݿ�������
���ز��� : src:���ݴ�������Դ��ַ
*****************************************************************************/
void *my_memcpy(void *dest, const void *src, unsigned short count)  
{  
  unsigned char *pdest = (unsigned char *)dest;  
  const unsigned char *psrc  = (const unsigned char *)src;  
  unsigned short i;
  
  if(dest == NULL || src == NULL)
  { 
    return NULL;
  }
  
  if((pdest <= psrc) || (pdest > psrc + count))
  {  
    for(i = 0; i < count; i ++)
    {  
      pdest[i] = psrc[i];  
    }  
  }
  else
  {
    for(i = count; i > 0; i --)
    {  
      pdest[i - 1] = psrc[i - 1];  
    }  
  }  
  
  return dest;  
}
/*****************************************************************************
�������� : int_to_byte
�������� : ��int���Ͳ���ĸ��ֽ�
������� : number:4�ֽ�ԭ����;value:������ɺ�4�ֽ�����
���ز��� :��
****************************************************************************/
void int_to_byte(unsigned long number,unsigned char value[4])
{
  value[0] = number >> 24;
  value[1] = number >> 16;
  value[2] = number >> 8;
  value[3] = number & 0xff;
}
/*****************************************************************************
�������� : byte_to_int
�������� : ��4�ֽںϲ�Ϊ1��32bit����
������� : value:4�ֽ�����
���ز��� : number:�ϲ���ɺ��32bit����
****************************************************************************/
unsigned long byte_to_int(const unsigned char value[4])
{
  unsigned long nubmer = 0;

  nubmer = (unsigned long)value[0];
  nubmer <<= 8;
  nubmer |= (unsigned long)value[1];
  nubmer <<= 8;
  nubmer |= (unsigned long)value[2];
  nubmer <<= 8;
  nubmer |= (unsigned long)value[3];
  
  return nubmer;
}
#ifndef WIFI_CONTROL_SELF_MODE
/*****************************************************************************
�������� : mcu_get_reset_wifi_flag
�������� : MCU��ȡ��λwifi�ɹ���־
������� : ��
���ز��� : ��λ��־:RESET_WIFI_ERROR:ʧ��/RESET_WIFI_SUCCESS:�ɹ�
ʹ��˵�� : 1:MCU��������mcu_reset_wifi()����øú�����ȡ��λ״̬
           2:���Ϊģ���Դ���ģʽ,MCU������øú���
*****************************************************************************/
unsigned char mcu_get_reset_wifi_flag(void)
{
  return reset_wifi_flag;
}
/*****************************************************************************
�������� : reset_wifi
�������� : MCU��������wifi����ģʽ
������� : ��
���ز��� : ��
ʹ��˵�� : 1:MCU��������,ͨ��mcu_get_reset_wifi_flag()������ȡ����wifi�Ƿ�ɹ�
           2:���Ϊģ���Դ���ģʽ,MCU������øú���
*****************************************************************************/
void mcu_reset_wifi(void)
{
  reset_wifi_flag = RESET_WIFI_ERROR;
  
  wifi_uart_write_frame(WIFI_RESET_CMD, 0);
}
/*****************************************************************************
�������� : mcu_get_wifimode_flag
�������� : ��ȡ����wifi״̬�ɹ���־
������� : ��
���ز��� : SET_WIFICONFIG_ERROR:ʧ��/SET_WIFICONFIG_SUCCESS:�ɹ�
ʹ��˵�� : 1:MCU��������mcu_set_wifi_mode()����øú�����ȡ��λ״̬
           2:���Ϊģ���Դ���ģʽ,MCU������øú���
*****************************************************************************/
unsigned char mcu_get_wifimode_flag(void)
{
  return set_wifimode_flag;
}
/*****************************************************************************
�������� : mcu_set_wifi_mode
�������� : MCU����wifi����ģʽ
������� : mode:
          SMART_CONFIG:����smartconfigģʽ
          AP_CONFIG:����APģʽ
���ز��� : ��
ʹ��˵�� : 1:MCU��������
           2:�ɹ���,���ж�set_wifi_config_state�Ƿ�ΪTRUE;TRUE��ʾΪ����wifi����ģʽ�ɹ�
           3:���Ϊģ���Դ���ģʽ,MCU������øú���
*****************************************************************************/
void mcu_set_wifi_mode(unsigned char mode)
{
  unsigned char length = 0;
  
  set_wifimode_flag = SET_WIFICONFIG_ERROR;
  
  length = set_wifi_uart_byte(length, mode);
  
  wifi_uart_write_frame(WIFI_MODE_CMD, length);
}
/*****************************************************************************
�������� : mcu_get_wifi_work_state
�������� : MCU������ȡ��ǰwifi����״̬
������� : ��
���ز��� : WIFI_WORK_SATE_E:
          SMART_CONFIG_STATE:smartconfig����״̬
          AP_STATE:AP ����״̬
          WIFI_NOT_CONNECTED:WIFI ���óɹ���δ����·����
          WIFI_CONNECTED:WIFI ���óɹ�������·����
ʹ��˵�� : ��
*****************************************************************************/
unsigned char mcu_get_wifi_work_state(void)
{
  return wifi_work_state;
}
#endif

#ifdef SUPPORT_MCU_RTC_CHECK
/*****************************************************************************
��������  : mcu_get_system_time
�������� : MCU��ȡϵͳʱ��,����У�Ա���ʱ��
������� : ��
���ز��� : ��
ʹ��˵�� : MCU����������ɺ���mcu_write_rtctime������У��rtcʱ��
*****************************************************************************/
void mcu_get_system_time(void)
{
  wifi_uart_write_frame(GET_LOCAL_TIME_CMD,0);
}
#endif

#ifdef WIFI_TEST_ENABLE
/*****************************************************************************
�������� : mcu_start_wifitest
�������� : mcu����wifi���ܲ���
������� : ��
���ز��� : ��
ʹ��˵�� : MCU��Ҫ���е��øù���
*****************************************************************************/
void mcu_start_wifitest(void)
{
  wifi_uart_write_frame(WIFI_TEST_CMD,0);
}
#endif

/*****************************************************************************
�������� : mcu_dp_raw_update
�������� : raw��dp�����ϴ�
������� : dpid:id��
           value:��ǰdpֵָ��
           len:���ݳ���
���ز��� : ��
*****************************************************************************/
unsigned char mcu_dp_raw_update(unsigned char dpid,const unsigned char value[],unsigned short len)
{
  unsigned short length = 0;
  
  if(stop_update_flag == ENABLE)
    return SUCCESS;
  //
  length = set_wifi_uart_byte(length,dpid);
  length = set_wifi_uart_byte(length,DP_TYPE_RAW);
  //
  length = set_wifi_uart_byte(length,len / 0x100);
  length = set_wifi_uart_byte(length,len % 0x100);
  //
  length = set_wifi_uart_buffer(length,(unsigned char *)value,len);
  
  wifi_uart_write_frame(STATE_UPLOAD_CMD,length);
  
  return SUCCESS;
}
/*****************************************************************************
�������� : mcu_dp_bool_update
�������� : bool��dp�����ϴ�
������� : dpid:id��
           value:��ǰdpֵ
���ز��� : ��
*****************************************************************************/
unsigned char mcu_dp_bool_update(unsigned char dpid,unsigned char value)
{
  unsigned short length = 0;
  
  if(stop_update_flag == ENABLE)
    return SUCCESS;
  
  length = set_wifi_uart_byte(length,dpid);
  length = set_wifi_uart_byte(length,DP_TYPE_BOOL);
  //
  length = set_wifi_uart_byte(length,0);
  length = set_wifi_uart_byte(length,1);
  //
  if(value == FALSE)
  {
    length = set_wifi_uart_byte(length,FALSE);
  }
  else
  {
    length = set_wifi_uart_byte(length,1);
  }
  
  wifi_uart_write_frame(STATE_UPLOAD_CMD,length);
  
  return SUCCESS;
}
/*****************************************************************************
�������� : mcu_dp_value_update
�������� : value��dp�����ϴ�
������� : dpid:id��
           value:��ǰdpֵ
���ز��� : ��
*****************************************************************************/
unsigned char mcu_dp_value_update(unsigned char dpid,unsigned long value)
{
  unsigned short length = 0;
  
  if(stop_update_flag == ENABLE)
    return SUCCESS;
  
  length = set_wifi_uart_byte(length,dpid);
  length = set_wifi_uart_byte(length,DP_TYPE_VALUE);
  //
  length = set_wifi_uart_byte(length,0);
  length = set_wifi_uart_byte(length,4);
  //
  length = set_wifi_uart_byte(length,value >> 24);
  length = set_wifi_uart_byte(length,value >> 16);
  length = set_wifi_uart_byte(length,value >> 8);
  length = set_wifi_uart_byte(length,value & 0xff);
  
  wifi_uart_write_frame(STATE_UPLOAD_CMD,length);
  
  return SUCCESS;
}
/*****************************************************************************
�������� : mcu_dp_string_update
�������� : rstring��dp�����ϴ�
������� : dpid:id��
           value:��ǰdpֵָ��
           len:���ݳ���
���ز��� : ��
*****************************************************************************/
unsigned char mcu_dp_string_update(unsigned char dpid,const unsigned char value[],unsigned short len)
{
  unsigned short length = 0;
  
  if(stop_update_flag == ENABLE)
    return SUCCESS;
  //
  length = set_wifi_uart_byte(length,dpid);
  length = set_wifi_uart_byte(length,DP_TYPE_STRING);
  //
  length = set_wifi_uart_byte(length,len / 0x100);
  length = set_wifi_uart_byte(length,len % 0x100);
  //
  length = set_wifi_uart_buffer(length,(unsigned char *)value,len);
  
  wifi_uart_write_frame(STATE_UPLOAD_CMD,length);
  
  return SUCCESS;
}
/*****************************************************************************
�������� : mcu_dp_enum_update
�������� : enum��dp�����ϴ�
������� : dpid:id��
           value:��ǰdpֵ
���ز��� : ��
*****************************************************************************/
unsigned char mcu_dp_enum_update(unsigned char dpid,unsigned char value)
{
  unsigned short length = 0;
  
  if(stop_update_flag == ENABLE)
    return SUCCESS;
  
  length = set_wifi_uart_byte(length,dpid);
  length = set_wifi_uart_byte(length,DP_TYPE_ENUM);
  //
  length = set_wifi_uart_byte(length,0);
  length = set_wifi_uart_byte(length,1);
  //
  length = set_wifi_uart_byte(length,value);
  
  wifi_uart_write_frame(STATE_UPLOAD_CMD,length);
  
  return SUCCESS;
}
/*****************************************************************************
�������� : mcu_dp_fault_update
�������� : fault��dp�����ϴ�
������� : dpid:id��
           value:��ǰdpֵ
���ز��� : ��
*****************************************************************************/
unsigned char mcu_dp_fault_update(unsigned char dpid,unsigned long value)
{
  unsigned short length = 0;
   
  if(stop_update_flag == ENABLE)
    return SUCCESS;
  
  length = set_wifi_uart_byte(length,dpid);
  length = set_wifi_uart_byte(length,DP_TYPE_FAULT);
  //
  length = set_wifi_uart_byte(length,0);
  
  if((value | 0xff) == 0xff)
  {
    length = set_wifi_uart_byte(length,1);
    length = set_wifi_uart_byte(length,value);
  }
  else if((value | 0xffff) == 0xffff)
  {
    length = set_wifi_uart_byte(length,2);
    length = set_wifi_uart_byte(length,value >> 8);
    length = set_wifi_uart_byte(length,value & 0xff);
  }
  else
  {
    length = set_wifi_uart_byte(length,4);
    length = set_wifi_uart_byte(length,value >> 24);
    length = set_wifi_uart_byte(length,value >> 16);
    length = set_wifi_uart_byte(length,value >> 8);
    length = set_wifi_uart_byte(length,value & 0xff);
  }    
  
  wifi_uart_write_frame(STATE_UPLOAD_CMD,length);

  return SUCCESS;
}
/*****************************************************************************
�������� : mcu_get_dp_download_bool
�������� : mcu��ȡbool���·�dpֵ
������� : value:dp���ݻ�������ַ
           length:dp���ݳ���
���ز��� : bool:��ǰdpֵ
*****************************************************************************/
unsigned char mcu_get_dp_download_bool(const unsigned char value[],unsigned short len)
{
  return(value[0]);
}
/*****************************************************************************
�������� : mcu_get_dp_download_enum
�������� : mcu��ȡenum���·�dpֵ
������� : value:dp���ݻ�������ַ
           length:dp���ݳ���
���ز��� : enum:��ǰdpֵ
*****************************************************************************/
unsigned char mcu_get_dp_download_enum(const unsigned char value[],unsigned short len)
{
  return(value[0]);
}
/*****************************************************************************
�������� : mcu_get_dp_download_value
�������� : mcu��ȡvalue���·�dpֵ
������� : value:dp���ݻ�������ַ
           length:dp���ݳ���
���ز��� : value:��ǰdpֵ
*****************************************************************************/
unsigned long mcu_get_dp_download_value(const unsigned char value[],unsigned short len)
{
  return(byte_to_int(value));
}



/*****************************************************************************
�������� : uart_receive_input
�������� : �����ݴ���
������� : value:�����յ��ֽ�����
���ز��� : ��
ʹ��˵�� : ��MCU���ڽ��պ����е��øú���,�������յ���������Ϊ��������
*****************************************************************************/
void uart_receive_input(unsigned char value)
{
  if((queue_in > queue_out) && ((queue_in - queue_out) >= sizeof(wifi_queue_buf)))
  {
    //���ݶ�����
  }
  else if((queue_in < queue_out) && ((queue_out  - queue_in) == 0))
  {
    //���ݶ�����
  }
  else
  {
    //���в���
    if(queue_in >= (unsigned char *)(wifi_queue_buf + sizeof(wifi_queue_buf)))
    {
      queue_in = (unsigned char *)(wifi_queue_buf);
    }
    
    *queue_in ++ = value;
  }
}
/*****************************************************************************
��������  : wifi_uart_service
��������  : wifi���ڴ������
������� : ��
���ز��� : ��
ʹ��˵�� : ��MCU������whileѭ���е��øú���
*****************************************************************************/
void wifi_uart_service(void)
{
  static unsigned short rx_in = 0;
  unsigned short offset = 0;
  unsigned short rx_value_len = 0;             //����֡����
  
  while((rx_in < sizeof(wifi_uart_rx_buf)) && get_queue_total_data() > 0)
  {
    wifi_uart_rx_buf[rx_in ++] = Queue_Read_Byte();
  }
  
  if(rx_in < PROTOCOL_HEAD)
    return;
  
  while((rx_in - offset) >= PROTOCOL_HEAD)
  {
    if(wifi_uart_rx_buf[offset + HEAD_FIRST] != FRAME_FIRST) //��һ���ֽڲ�����0x55
    {
      offset ++;
      continue; 
    }
    
    if(wifi_uart_rx_buf[offset + HEAD_SECOND] != FRAME_SECOND)//������0xaa 
    {
      offset ++;
      continue;
    }  
    
    if(wifi_uart_rx_buf[offset + PROTOCOL_VERSION] != VERSION)//�жϰ汾
    {
      offset += 2;
      continue;
    }      
    /*����*/
    rx_value_len = wifi_uart_rx_buf[offset + LENGTH_HIGH] * 0x100 + wifi_uart_rx_buf[offset + LENGTH_LOW] + PROTOCOL_HEAD;
    if(rx_value_len > sizeof(wifi_uart_rx_buf) + PROTOCOL_HEAD)
    {
      offset += 3;
      continue;
    }
    
    if((rx_in - offset) < rx_value_len)
    {
      break;
    }
    
    //���ݽ������
    if(get_check_sum((unsigned char *)wifi_uart_rx_buf + offset,rx_value_len - 1) != wifi_uart_rx_buf[offset + rx_value_len - 1])//��У��
    {
      //У�����
      offset += 3;
      continue;
    }
    
    data_handle(offset);
    offset += rx_value_len;
  }//end while

  rx_in -= offset;
  if(rx_in > 0)
  {
    my_memcpy(wifi_uart_rx_buf,wifi_uart_rx_buf + offset,rx_in);
  }
}
/*****************************************************************************
�������� :  wifi_protocol_init
�������� : Э�鴮�ڳ�ʼ������
������� : ��
���ز��� : ��
ʹ��˵�� : ������MCU��ʼ�������е��øú���
*****************************************************************************/
void wifi_protocol_init(void)
{
  queue_in = (unsigned char *)wifi_queue_buf;
  queue_out = (unsigned char *)wifi_queue_buf;
  //
#ifndef WIFI_CONTROL_SELF_MODE
  wifi_work_state = WIFI_SATE_UNKNOW;
#endif
}


