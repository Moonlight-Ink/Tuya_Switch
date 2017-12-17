#ifndef __KEY_H
#define	__KEY_H

#include "stm32f10x.h"

#define Key1_Pin   GPIO_Pin_1
#define Key1_Port  GPIOA
#define Key2_Pin   GPIO_Pin_2
#define Key2_Port  GPIOA







#define Press   0x01
#define Unpress  0x00
#define Key1_Press  GPIO_ReadInputDataBit(Key1_Port,Key1_Pin)//读取按键K2 
#define Key2_Press  GPIO_ReadInputDataBit(Key1_Port,Key2_Pin)//读取按键K3

void Key_Init(void);
uint8_t Key1_Scan(void);
uint8_t Key2_Scan(void);


////自定义的键值
//#define KEY_K1_PRESS 	1
//#define KEY_K2_PRESS	2

//void Key_Init(void);
//u8 KEY_Scan(u8 mode);
//void Key_event(void);

#endif

