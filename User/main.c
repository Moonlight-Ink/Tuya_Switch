/**
  ******************************************************************************
  * @file    main.c
  * @author  fire
  * @version V1.0
  * @date    2013-xx-xx
  * @brief   �����жϽ��ղ���
  ******************************************************************************
  * @attention
  *
  * ʵ��ƽ̨:Ұ�� iSO STM32 ������ 
  * ��̳    :http://www.chuxue123.com
  * �Ա�    :http://firestm32.taobao.com
  *
  ******************************************************************************
  */ 

#include "stm32f10x.h"
#include "bsp_usart.h"
#include "bsp_key.h"
#include "bsp_led.h"
#include "wifi.h"
#include "application.h"
#include "bsp_timer.h"

 typedef enum
 {
	  fast,
		slow,	
	 
 }Led_Status_obj;
 Led_Status_obj Led_Status=fast;


/**
  * @brief  ������
  * @param  ��
  * @retval ��
  */

int main(void)
{
	
	Key_Init();
	
	
	Led_Init();
		/* USART1 ����ģʽΪ 115200 8-N-1���жϽ��� */
	USART1_Config();	
	
  //����wifi��ʼ��  
  wifi_protocol_init();

	TIM3_Int_Init();

	while(1)
	{	
		wifi_uart_service();
		Key_event();
//		if(set_wifimode_flag)
//		{
//			LED1_ON;
//		}
	 switch(wifi_work_state)
		{
			case 0x00:
				  Led_Status=fast;
          TIM_Cmd(TIM3, ENABLE);  //ʹ��TIMx	1��10��
    			TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE ); //ʹ��ָ����TIM3�ж�,��������ж�
			break;
			case 0x01:

			break;
			case 0x02:                  //1������
			    	Led_Status=slow;
				break;
			case 0x03:
				 LED2_ON
				 TIM_Cmd(TIM3, DISABLE);  //ʹ��TIMx	
			   TIM_ITConfig(TIM3,TIM_IT_Update,DISABLE ); //ʹ��ָ����TIM3�ж�,��������ж�
				break;
		}
	}
}

//��ʱ��3�жϷ������
void TIM3_IRQHandler(void)   //TIM3�ж�
{
	static uint8_t count;
	if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)  //���TIM3�����жϷ������
	{ 
		count++;
		switch(Led_Status)
		{
			case fast:
				   LED2_TOGGLE;
				break;
			case slow:
				   if(count>=5)
					 {
						 LED2_TOGGLE;
						 count=0;
					 }
				break;
		}
			
		TIM_ClearITPendingBit(TIM3, TIM_IT_Update  );  //���TIMx�����жϱ�־ 

	}
}

/*********************************************END OF FILE**********************/
