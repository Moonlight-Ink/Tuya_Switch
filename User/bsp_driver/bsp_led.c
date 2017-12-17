#include "bsp_led.h"


void Led_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	 //使能PB端口时钟

	
	GPIO_InitStructure.GPIO_Pin = LED1_Pin;	 //LED_D5-->PB.0  LED_D6-->PB.1 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
	GPIO_Init(LED1_Port, &GPIO_InitStructure);					 //根据设定参数初始化PB0.1
	GPIO_SetBits(LED1_Port,LED1_Pin);			     //PB0.1输出高	
	
	
	GPIO_InitStructure.GPIO_Pin = LED2_Pin;	 //LED_D5-->PB.0  LED_D6-->PB.1 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
	GPIO_Init(LED2_Port, &GPIO_InitStructure);					 //根据设定参数初始化PB0.1
	GPIO_SetBits(LED2_Port,LED2_Pin);			     //PB0.1输出高
}


//void SetLedStatus(unsigned char status)
//{
//	 if(status)
//	 {
//		 LED1_ON;
//	 }
//	 else
//	 {
//		 LED1_OFF;
//	 }
//}
