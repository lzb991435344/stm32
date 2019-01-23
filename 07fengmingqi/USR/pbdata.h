#ifndef _pbdata_H
#define _pbdata_H

#include "stm32f10x.h"

//定义变量

extern u8 dt;

//定义函数
void RCC_HSE_Configuration(void);
void delay(u32 nCount);
void delay_us(u32 nus);
void delay_ms(u16 nms);

#endif
