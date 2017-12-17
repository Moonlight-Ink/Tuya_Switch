#ifndef  __APPLICATION_H
#define  __APPLICATION_H



#include "stm32f10x.h"

#define  Event_None     0x00
#define  Key1_Event     0x01
#define  Key2_Event     0x02
#define  Timing_Event   0x03



//uint8_t Key_Scan(void);
uint8_t Key_Scan(void);
uint8_t Key_Event(void);
uint8_t Delay_10ms(void);























#endif
