/**
  ******************************************************************************
  * @file    main.c
  * @author  fire
  * @version V1.0
  * @date    2013-xx-xx
  * @brief   串口中断接收测试
  ******************************************************************************
  * @attention
  *
  * 实验平台:野火 iSO STM32 开发板 
  * 论坛    :http://www.chuxue123.com
  * 淘宝    :http://firestm32.taobao.com
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
  * @brief  主函数
  * @param  无
  * @retval 无
  */

int main(void)
{
	
	Key_Init();
	
	
	Led_Init();
		/* USART1 配置模式为 115200 8-N-1，中断接收 */
	USART1_Config();	
	
  //调用wifi初始化  
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
          TIM_Cmd(TIM3, ENABLE);  //使能TIMx	1秒10下
    			TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE ); //使能指定的TIM3中断,允许更新中断
			break;
			case 0x01:

			break;
			case 0x02:                  //1秒两下
			    	Led_Status=slow;
				break;
			case 0x03:
				 LED2_ON
				 TIM_Cmd(TIM3, DISABLE);  //使能TIMx	
			   TIM_ITConfig(TIM3,TIM_IT_Update,DISABLE ); //使能指定的TIM3中断,允许更新中断
				break;
		}
	}
}

//定时器3中断服务程序
void TIM3_IRQHandler(void)   //TIM3中断
{
	static uint8_t count;
	if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)  //检查TIM3更新中断发生与否
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
			
		TIM_ClearITPendingBit(TIM3, TIM_IT_Update  );  //清除TIMx更新中断标志 

	}
}

/*********************************************END OF FILE**********************/
