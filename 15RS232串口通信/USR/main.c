#include "pbdata.h"

void RCC_Configuration(void);
void GPIO_Configuration(void);
void NVIC_Configuration(void);
void USART_Configuration(void);
int main(void)
{
   RCC_Configuration();	//系统时钟初始化
   GPIO_Configuration();//端口初始化
   USART_Configuration();
   NVIC_Configuration();//中断优先级配置
   
   while(1);	
}

void RCC_Configuration(void)
{
    SystemInit();//72m
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);//GPIOA时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);//USART1时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);//功能复用IO时钟
}

void GPIO_Configuration(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;	
	//LED
	//TX
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_9;//TX
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;//推挽输出，输出能力更强
	GPIO_Init(GPIOA,&GPIO_InitStructure);

	//RX
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_10;//RX
	//浮空输入，随着外界的电压变化而变化，读取外界的信号
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
}

void NVIC_Configuration(void)
{
	/**
	typedef struct
	{
		u8 NVIC_IRQChannel;//该参数用以使能或者失能指定的IRQ通道
		u8 NVIC_IRQChannelPreemptionPriority;//该参数设置了成员NVIC_IRQChannel中的先占优先
		u8 NVIC_IRQChannelSubPriority;//该参数设置了成员NVIC_IRQChannel中的从优先
		FunctionalState NVIC_IRQChannelCmd;//该参数指定了在成员NVIC_IRQChannel中定义的IRQ通道被使能还是失能。这个参数取值为ENABLE或者DISABLE。
	} NVIC_InitTypeDef;
	
	*/
   	NVIC_InitTypeDef NVIC_InitStructure; 
  //先占优先级1位，从优先级3位
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1); 

	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn; 
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; 
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1; 
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 
	NVIC_Init(&NVIC_InitStructure);
}

void USART_Configuration(void)
{
	/**
	 typedef struct
{
u32 USART_BaudRate;//该成员设置了USART传输的波特率
u16 USART_WordLength;//提示了在一个帧中传输或者接收到的数据位数
u16 USART_StopBits;//SART_StopBits定义了发送的停止位数
u16 USART_Parity;//USART_Parity定义了奇偶模式
u16 USART_HardwareFlowControl;//USART_HardwareFlowControl指定了硬件流控制模式使能还是失能
u16 USART_Mode;//USART_Mode指定了使能或者失能发送和接收模式
u16 USART_Clock;//USART_CLOCK提示了USART时钟使能还是失能
u16 USART_CPOL;//USART_CPOL指定了下SLCK引脚上时钟输出的极性
u16 USART_CPHA;//USART_CPHA指定了下SLCK引脚上时钟输出的相位，和CPOL位一起配合来产生用户希望的时钟/数据的采样关系。
u16 USART_LastBit;//SART_LastBit来控制是否在同步模式下，在SCLK引脚上输出最后发送的那个数据字 (MSB)对应的时钟脉冲
} USART_InitTypeDef;
	*/
  USART_InitTypeDef  USART_InitStructure;

	USART_InitStructure.USART_BaudRate=9600;//1波特率 = 1bps(位/秒)
	USART_InitStructure.USART_WordLength=USART_WordLength_8b;
	USART_InitStructure.USART_StopBits=USART_StopBits_1;
	USART_InitStructure.USART_Parity=USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl=USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode=USART_Mode_Rx|USART_Mode_Tx;

	USART_Init(USART1,&USART_InitStructure);
	/**
	void USART_ITConfig(USART_TypeDef* USARTx, u16 USART_IT, FunctionalState NewState)
	@function 使能或者失能指定的USART中断
	@param1 USARTx：x可以是1，2或者3，来选择USART外设
	@param2 USART_IT：待使能或者失能的USART中断源
	@param3 NewState：USARTx中断的新状态,这个参数可以取：ENABLE或者DISABLE
	@return  void
	*/
	USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);
	
	USART_Cmd(USART1,ENABLE);
	/**
	void USART_ClearFlag(USART_TypeDef* USARTx, u16 USART_FLAG)
	@function 清除USARTx的待处理标志位
	@param1 USARTx：x可以是1，2或者3，来选择USART外设
	@param2 USART_FLAG：待清除的USART标志位,通过FlagStatus USART_GetFlagStatus(USART_TypeDef* USARTx, u16 USART_FLAG)函数来获取
	@return void
	*/
	USART_ClearFlag(USART1,USART_FLAG_TC);//配置完成直接进入发送的状态，否则第一个字母无法发送出去
}



