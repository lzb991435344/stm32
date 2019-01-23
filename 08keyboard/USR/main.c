#include "pbdata.h"

void RCC_Configuration(void);
void GPIO_Configuration(void);

int main(void)
{
   RCC_Configuration();	//系统时钟初始化
   GPIO_Configuration();//端口初始化
   
	while(1)
	{
		//GPIO_ReadInputDataBit读取指定端口管脚的输入
		//参数1：GPIOx：x可以是A，B，C，D或者E，来选择GPIO外设
		//参数2：GPIO_Pin：待读取的端口位
		/*
		typedef enum
   { Bit_RESET = 0,
     Bit_SET
     }BitAction;
		*/
		if(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_5) == Bit_RESET)
		{
			//LED1 发光
			GPIO_ResetBits(GPIOB,GPIO_Pin_5);
		}
		else
		{
		   //LED1 熄灭
		   GPIO_SetBits(GPIOB,GPIO_Pin_5);
		}
		
		//LED2,KEY2
		if(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_1) == Bit_RESET)
		{
			GPIO_ResetBits(GPIOD,GPIO_Pin_6);
		}
		else
		{
		  GPIO_SetBits(GPIOD,GPIO_Pin_6);
		}
		
		//LED3,KEY3
		if(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_2) == Bit_RESET)
		{
			GPIO_ResetBits(GPIOD,GPIO_Pin_3);
		}
		else
		{
		  GPIO_SetBits(GPIOD,GPIO_Pin_3);
		}
		
		//LDE1,2,3
		if(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_3)  == Bit_RESET)
		{
			GPIO_ResetBits(GPIOB,GPIO_Pin_5);
			GPIO_ResetBits(GPIOD,GPIO_Pin_6);
			GPIO_ResetBits(GPIOD,GPIO_Pin_3);
		}
		else
		{
			//GPIO_SetBits(GPIOB,GPIO_Pin_5);
			//GPIO_SetBits(GPIOD,GPIO_Pin_6);
		  GPIO_SetBits(GPIOC,GPIO_Pin_3);
		}
	}
}

void RCC_Configuration(void)
{
  SystemInit();
	//RCC_APB2PeriphClockCmd 使能或者失能APB2外设时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);//B端口
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);//C端口
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD,ENABLE);//D端口
}

void GPIO_Configuration(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;	
	//LED1
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_Init(GPIOB,&GPIO_InitStructure);

	//KEY1，独立键盘
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;//上拉输入模式
	GPIO_Init(GPIOC,&GPIO_InitStructure);
	
	
	//LED2
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_Init(GPIOD,&GPIO_InitStructure);

	//KEY2，独立键盘
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;//上拉输入模式
	GPIO_Init(GPIOC,&GPIO_InitStructure);
	
	
	//LED3
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_Init(GPIOD,&GPIO_InitStructure);

	//KEY3，独立键盘
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;//上拉输入模式
	GPIO_Init(GPIOC,&GPIO_InitStructure);
	
	//LED1,2,3
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_Init(GPIOD,&GPIO_InitStructure);
	
	//KEY4
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;//上拉输入模式
	GPIO_Init(GPIOC,&GPIO_InitStructure);
}

