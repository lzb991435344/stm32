#include "pbdata.h"

void RCC_Configuration(void);
void GPIO_Configuration(void);
void NVIC_Configuration(void);
void USART_Configuration(void);

#define FLASH_ADR 0x0807F800  //写入数据的地址
int fputc(int ch,FILE *f)
{
	/**
	 void USART_SendData(USART_TypeDef* USARTx, u8 Data)
	  @function  通过外设USARTx发送单个数据
	  @param1  USARTx：x可以是1，2或者3，来选择USART外设
	  @param2  Data: 待发送的数据
		@return void
	*/
	USART_SendData(USART1,(u8)ch);
	/*
	FlagStatus USART_GetFlagStatus(USART_TypeDef* USARTx, u16 USART_FLAG)
	 @function:检查指定的USART标志位设置与否
	 @param1  USARTx：x可以是1，2或者3，来选择USART外设
	 @param2  USART_FLAG：待检查的USART标志位
	 @return :USART_FLAG的新状态（SET或者RESET）	
	*/
	while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)==RESET);
	return ch;
}

int main(void)
{
   u32 data=12345678;

   RCC_Configuration();	//系统时钟初始化
   GPIO_Configuration();//端口初始化
   USART_Configuration();
   NVIC_Configuration();

	//解锁
	FLASH_Unlock();
	//清除标志位
	//标志位分别为 忙标志位，操作结束标志位，编写错误标志位，页面写保护错误标志位
	FLASH_ClearFlag(FLASH_FLAG_BSY|FLASH_FLAG_EOP|
					FLASH_FLAG_PGERR|FLASH_FLAG_WRPRTERR);
	
	//要擦出页的起始地址
	FLASH_ErasePage(FLASH_ADR);  //#define FLASH_ADR 0x0807F800
	//写数据
	FLASH_ProgramWord(FLASH_ADR,data);

	//FLASH_ProgramWord(FLASH_ADR+4,data);

	//锁定
	FLASH_Lock();

	data=0;//赋初值为0
	data=(*(__IO uint32_t*)(FLASH_ADR)); //对特定的地址取值
	printf("输出 data=%d\r\n",data);   
    while(1); //循环等待
}

void RCC_Configuration(void)
{
    SystemInit();//72m
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
}

void GPIO_Configuration(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;	
	//LED
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_9;//TX
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;
	GPIO_Init(GPIOA,&GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_10;//RX
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
}

void NVIC_Configuration(void)
{
   	NVIC_InitTypeDef NVIC_InitStructure; 

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1); 

	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn; 
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; 
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1; 
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 
	NVIC_Init(&NVIC_InitStructure);
}

void USART_Configuration(void)
{
    USART_InitTypeDef  USART_InitStructure;

	USART_InitStructure.USART_BaudRate=9600;
	USART_InitStructure.USART_WordLength=USART_WordLength_8b;
	USART_InitStructure.USART_StopBits=USART_StopBits_1;
	USART_InitStructure.USART_Parity=USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl=USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode=USART_Mode_Rx|USART_Mode_Tx;

	USART_Init(USART1,&USART_InitStructure);
	USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);
	USART_Cmd(USART1,ENABLE);
	USART_ClearFlag(USART1,USART_FLAG_TC);
}



