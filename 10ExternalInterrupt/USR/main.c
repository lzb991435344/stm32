#include "pbdata.h"

void RCC_Configuration(void);
void GPIO_Configuration(void);
void EXTI_Configuration(void);
void NVIC_Configuration(void);

int main(void)
{
   RCC_Configuration();	//系统时钟初始化
   GPIO_Configuration();//端口初始化
   EXTI_Configuration();
   NVIC_Configuration();
   
   while(1);	
}

void RCC_Configuration(void)
{
    SystemInit();
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);//RCC_APB2Periph_GPIOA GPIOA时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);//RCC_APB2Periph_AFIO 功能复用IO时钟
}

void GPIO_Configuration(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;	
	//LED
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_Init(GPIOB,&GPIO_InitStructure);

	//KEY
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;
	GPIO_Init(GPIOC,&GPIO_InitStructure);
}

void EXTI_Configuration(void)
{
	/**结构体类型
  typedef struct { u32 EXTI_Line;
	  EXTIMode_TypeDef EXTI_Mode; 
	  EXTIrigger_TypeDef EXTI_Trigger; 
	  FunctionalState EXTI_LineCmd; } EXTI_InitTypeDef; 
	*/
	EXTI_InitTypeDef EXTI_InitStructure; 

	//清空线路
	//void EXTI_ClearITPendingBit(u32 EXTI_Line)  清除EXTI线路挂起位
	EXTI_ClearITPendingBit(EXTI_Line5);
	
	//GPIO_EXTILineConfig 选择GPIO管脚用作外部中断线路
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOC, GPIO_PinSource5); 

	EXTI_InitStructure.EXTI_Line=EXTI_Line5;//外部中断线5
	
	//EXTI_Mode_Interrupt 设置EXTI线路为中断请求 ;EXTI_Mode_Event 设置EXTI线路为事件请求
	EXTI_InitStructure.EXTI_Mode=EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger=EXTI_Trigger_Falling;//设置输入线路下降沿为中断请求
	EXTI_InitStructure.EXTI_LineCmd=ENABLE;//EXTI_LineCmd用来定义选中线路的新状态。它可以被设为ENABLE或者DISABLE。

	 //EXTI_InitTypeDef 根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器
	 //参数：指向结构EXTI_InitTypeDef的指针，包含了外设EXTI的配置信息
	EXTI_Init(&EXTI_InitStructure);
}

void NVIC_Configuration(void)
{
	/**
	  typedef struct
   {
    u8 NVIC_IRQChannel;
    u8 NVIC_IRQChannelPreemptionPriority;
    u8 NVIC_IRQChannelSubPriority;
    FunctionalState NVIC_IRQChannelCmd;
   } NVIC_InitTypeDef;
	*/
  NVIC_InitTypeDef NVIC_InitStructure; 

	//NVIC_PriorityGroupConfig设置的先占优先级和从优先级可取的值
	//参数：NVIC_PriorityGroup_1 0-1(先占优先级) 0-7(从优先级) 先占优先级1位 从优先级3位
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1); 

	NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn; //EXTI9_5_IRQChannel 外部中断线9-5中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; 
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1; 
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 
	
	/**
	 根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器
   输入参数
   NVIC_InitStruct：指向结构NVIC_InitTypeDef的指针，包含了外设GPIO的配置信息
	*/
	NVIC_Init(&NVIC_InitStructure);
}


