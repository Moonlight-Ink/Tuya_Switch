#ifndef __LED_H
#define	__LED_H

#include "stm32f10x.h"

#define LED1_Pin   GPIO_Pin_0
#define LED1_Port  GPIOB
#define LED2_Pin   GPIO_Pin_1
#define LED2_Port  GPIOB





#define Toggle(p,i)		   {p->ODR ^=i;}			//Êä³ö·´×ª×´Ì¬

#define LED1_ON          GPIO_ResetBits(LED1_Port,LED1_Pin);
#define LED1_OFF         GPIO_SetBits(LED1_Port,LED1_Pin);
#define LED1_TOGGLE		   Toggle(LED1_Port,LED1_Pin);

#define LED2_ON          GPIO_ResetBits(LED2_Port,LED2_Pin);
#define LED2_OFF         GPIO_SetBits(LED2_Port,LED2_Pin);
#define LED2_TOGGLE		   Toggle(LED2_Port,LED2_Pin);


//void TIM3_Int_Init(void);
void Led_Init(void);



#endif

