#ifndef _pbdata_H
#define _pbdata_H

#include "stm32f10x.h"

//�������

extern u8 dt;

//���庯��
void RCC_HSE_Configuration(void);
void delay(u32 nCount);
void delay_us(u32 nus);
void delay_ms(u16 nms);

#endif
