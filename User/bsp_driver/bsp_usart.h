#ifndef __USART1_H
#define	__USART1_H

#include "stm32f10x.h"
#include <stdio.h>


#define BaudRate     9600



void USART1_Config(void);

int fputc(int ch, FILE *f);
int fgetc(FILE *f);
void Uart_PutChar(uint8_t ch);
#endif /* __USART1_H */
