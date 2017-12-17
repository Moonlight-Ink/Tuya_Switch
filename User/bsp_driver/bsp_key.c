#include "bsp_key.h"
#include "bsp_led.h"
#include "wifi.h"

/********************************************/
extern uint8_t Delay_10ms(void);
/********************************************/



void Key_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);//使能PORTA时钟
 
 	GPIO_InitStructure.GPIO_Pin  = Key1_Pin;    //PA1----K1
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //设置成上拉输入
 	GPIO_Init(Key1_Port, &GPIO_InitStructure);        //初始化PA1

	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_2;    //PA0----K2
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; //PA0设置成输入，默认下拉	  
	GPIO_Init(Key1_Port, &GPIO_InitStructure);        //初始化PA0	
	
}




uint8_t Key1_Scan(void)
{
   if(Key1_Press)
	 {
     Delay_10ms();
		 if(Key1_Press)
		 {
			 return Press;
		 }
   }
	 else
	 {     
     Delay_10ms();
		 if(!Key1_Press)
		 {
       return Unpress;
     }
   }
}

uint8_t Key2_Scan(void)
{
	 if(Key2_Press)
	 {
     Delay_10ms();
		 if(Key2_Press)
		 {
			 return Press;
		 }
   }
	 else
	 {     
     Delay_10ms();
		 if(!Key2_Press)
		 {
       return Unpress;
     }
   }
}


//extern  void all_data_update(void);
//unsigned char GetKeyStates(void);
//extern void SetLedStatus(unsigned char status);
//void Key_Init(void)
//{

// 	GPIO_InitTypeDef GPIO_InitStructure;

// 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);//使能PORTA时钟

//	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_1;    //PA1----K1
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //设置成上拉输入
// 	GPIO_Init(GPIOA, &GPIO_InitStructure);        //初始化PA1

//	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_0;    //PA0----K2
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; //PA0设置成输入，默认下拉	  
//	GPIO_Init(GPIOA, &GPIO_InitStructure);        //初始化PA0

//}

//void Key_event(void)
//{
//  u8 key;
//		key=KEY_Scan(0);
//		switch(key)
//		{
//			case KEY_K1_PRESS : 

//			  mcu_set_wifi_mode(SMART_CONFIG);
////			USART1_Send(tt,8);
//			break;
//			case KEY_K2_PRESS : 
//    if(GetKeyStates())
//		{
//			SetLedStatus(0);
//			SetKeyStates( 0);
//		}
//		else
//		{
//			SetLedStatus(1);
//			SetKeyStates(1);
//		}
//			all_data_update();
////			USART1_Send(tt,8);
//			break;
//		}
//}

//u8 KEY_Scan(u8 mode)
//{	 
//	static u8 key_up=1;//按键按松开标志
//	if(mode)key_up=1;  //支持连按		  
//	if(key_up&&(KEY_K1==0||KEY_K2==1))
//	{
//		Delay_ms(10);//去抖动 
//		key_up=0;
//		if(KEY_K1==0)     
//			return KEY_K1_PRESS;
//		else if(KEY_K2==1)
//			return KEY_K2_PRESS;
//	}
//	else if(KEY_K1==1&&KEY_K2==0)key_up=1; 	    
// 	return 0;// 无按键按下
//}













