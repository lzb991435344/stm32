#include "pbdata.h"

void RCC_Configuration(void);
void GPIO_Configuration(void);
void NVIC_Configuration(void);
void TIM3_Configuration(void);

int main(void)
{
   RCC_Configuration();	//系统时钟初始化
   GPIO_Configuration();//端口初始化
   TIM3_Configuration();
   NVIC_Configuration();
   
   while(1);	
}

void RCC_Configuration(void)
{
  SystemInit();
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
}

void GPIO_Configuration(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;	
	//LED
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
}

void TIM3_Configuration(void)
{
	/**
	    typedef struct
      {
         u16 TIM_Period;
         u16 TIM_Prescaler;
         u8 TIM_ClockDivision;
         u16 TIM_CounterMode;
      } TIM_TimeBaseInitTypeDef;
	*/
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStruct;
	
	//清除TIMx的中断待处理位
	TIM_ClearITPendingBit(TIM3,TIM_IT_Update);
	
  //初值,TIM_Period设置了在下一个更新事件装入活动的自动重装载寄存器周期的值。它的取值必须在0x0000和0xFFFF之间。
	TIM_TimeBaseStruct.TIM_Period=2000;
	
	//TIM_Prescaler设置了用来作为TIMx时钟频率除数的预分频值。它的取值必须在0x0000和0xFFFF之间。
	TIM_TimeBaseStruct.TIM_Prescaler=35999;//预分频
	
	//TIM_ClockDivision设置了时钟分割
	TIM_TimeBaseStruct.TIM_ClockDivision=0;
	
	//TIM_CounterMode选择了计数器模式
	TIM_TimeBaseStruct.TIM_CounterMode=TIM_CounterMode_Up;//向上

  //根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位
	//参数1：TIMx：x可以是2，3或者4，来选择TIM外设
	//参数2：TIMTimeBase_InitStruct：指向结构TIM_TimeBaseInitTypeDef的指针，包含了TIMx时间基数单位的配置信息
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseStruct);
   
	 //使能或者失能指定的TIM中断
	 //参数1：TIMx：x可以是2，3或者4，来选择TIM外设
	 //参数2：TIM_IT：待使能或者失能的TIM中断源
	 //参数3：NewState：TIMx中断的新状态
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE);
	
	//使能或者失能TIMx外设
	TIM_Cmd(TIM3,ENABLE);	 
}

void NVIC_Configuration(void)
{
   	NVIC_InitTypeDef NVIC_InitStructure; 

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1); 

	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn; 
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; 
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1; 
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 
	NVIC_Init(&NVIC_InitStructure);
}


