#include "pbdata.h"

void RCC_Configuration(void);
void GPIO_Configuration(void);
void TIM3_Configuration(void);

int main(void)
{
   u8 led_fx=1;
   u16 led_dt=0;

   RCC_Configuration();	//系统时钟初始化
   GPIO_Configuration();//端口初始化
   TIM3_Configuration();//定时器和pwm配置 
   while(1)
   {
   	 delay_ms(10);
	 if(led_fx==1)
	 {
	 	led_dt++;
	 }
	 else
	 {
	   led_dt--;
	 }

	 if(led_dt>300)  led_fx=0;
   	 if(led_dt==0)	 led_fx=1;

	 TIM_SetCompare2(TIM3,led_dt);
   }	
}

void RCC_Configuration(void)
{
  SystemInit();
	/**
	void RCC_AHBPeriphClockCmd(u32 RCC_AHBPeriph,FunctionalState NewState)
	@function 使能或者失能AHB外设时钟
	@param1 RCC_AHBPeriph: 门控AHB外设时钟
	@param2 NewState：指定外设时钟的新状态，这个参数可以取：ENABLE或者DISABLE
	@return void
	*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);//GPIOB时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);//TIM3时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);//功能复用IO时钟
}

//GPIO时钟配置函数
void GPIO_Configuration(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;	
	//LED
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;//选择复用推挽输出
	GPIO_Init(GPIOB,&GPIO_InitStructure);
}

//TIM3始终配置
void TIM3_Configuration(void)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStruct;
	/**
	typedef struct
  {
	u16 TIM_OCMode;//选择定时器的模式
	u16 TIM_Channel;//选择通道
	u16 TIM_Pulse;//设置了待装入捕获比较寄存器的脉冲值。它的取值必须在0x0000和0xFFFF之
	u16 TIM_OCPolarity;//输出极性，极性的高低
	} TIM_OCInitTypeDef;
	*/
	//根据TIM_OCInitStruct中指定的参数初始化外设TIMx
	TIM_OCInitTypeDef TIM_OCInitStructure; 

	GPIO_PinRemapConfig(GPIO_PartialRemap_TIM3,ENABLE);

	//定时器初始化
	TIM_TimeBaseStruct.TIM_Period=899;//初值，设置进去之后会进行加1操作，故设置为899
	TIM_TimeBaseStruct.TIM_Prescaler=0;//预分频
	TIM_TimeBaseStruct.TIM_ClockDivision=0;
	TIM_TimeBaseStruct.TIM_CounterMode=TIM_CounterMode_Up;//向上
	
  /**
	void TIM_TimeBaseInit(TIM_TypeDef* TIMx, TIM_TimeBaseInitTypeDef* TIM_TimeBaseInitStruct)
	
	@function 根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位
	@param1 TIMx：x可以是2，3或者4，来选择TIM外设
	@param2 TIMTimeBase_InitStruct：指向结构TIM_TimeBaseInitTypeDef的指针，包含了TIMx时间基数单位的配置信息
	@return void
	*/
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseStruct);
	

	//pwm 初始化
	TIM_OCInitStructure.TIM_OCMode=TIM_OCMode_PWM1;//TIM脉冲宽度调制模式1
	TIM_OCInitStructure.TIM_OutputState=TIM_OutputState_Enable;//设置为可输出模式
	//TIM输出比较极性低,连接的是管脚5低电平端，点亮二极管需要设置为极性低
	TIM_OCInitStructure.TIM_OCPolarity=TIM_OCPolarity_Low;

	TIM_OC2Init(TIM3,&TIM_OCInitStructure);
	/**
	void TIM_OC2PreloadConfig(TIM_TypeDef* TIMx, u16 TIM_OCPreload)
	@function 使能或者失能TIMx在CCR2上的预装载寄存器
	@param1 TIMx：x可以是2，3或者4，来选择TIM外设
	@param2 TIM_OCPreload：输出比较预装载状态
	@return void
	*/
	TIM_OC2PreloadConfig(TIM3,TIM_OCPreload_Enable);
	/**
	void TIM_Cmd(TIM_TypeDef* TIMx, FunctionalState NewState)
	@function 使能或者失能TIMx外设
	@param1 TIMx：x可以是2，3或者4，来选择TIM外设
	@param2 NewState: 外设TIMx的新状态,这个参数可以取：ENABLE或者DISABLE
	@return void
	*/
	TIM_Cmd(TIM3,ENABLE);
		 
}
