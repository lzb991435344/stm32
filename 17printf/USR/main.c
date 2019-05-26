#include "pbdata.h"

void RCC_Configuration(void);
void GPIO_Configuration(void);
void NVIC_Configuration(void);
void USART_Configuration(void);

int fputc(int ch,FILE *f)
{
	USART_SendData(USART1,(u8)ch);//将要发送的数据发送到串口
	while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)==RESET);//等待完成
	return ch;//返回数据
}

int main(void)
{
   u32 d1=0;
   float d2=0;
   u8   d3=0;
   u8   d4[5];

   RCC_Configuration();	//系统时钟初始化
   GPIO_Configuration();//端口初始化
   USART_Configuration();
   NVIC_Configuration();
   
   while(1)
   {
      //printf("众想科技\r\n");
	  //printf("www.zxkjmcu.com\r\n");

	  //d1=123456;
	  //printf("10进制整型输出 d1=%10d\r\n",d1);

	  //d1=123456;
	  //printf("16进制输出 d1=%X\r\n",d1);//X 大写输出  x小写输出

	  //d2=12.345;
	  //printf("浮点数输出 d2=%f\r\n",d2);
	  ///printf("浮点数输出 d2=%.2f\r\n",d2);
	  //printf("浮点数输出 d2=%10.2f\r\n",d2);

	  //d3='a';
	  //printf("字符输出 d3=%c\r\n",d3);


	  d4[0]='a';
	  d4[1]='b';
	  d4[2]='c';
	  d4[3]='d';
	  d4[4]='\0';

	  printf("字符串输出 d4=%s\r\n",d4);

	  //注意 delay_ms函数输入范围是1-1863
	  //所以最大延时为1.8秒
	  delay_ms(1000);   
	  delay_ms(1000);   
	  delay_ms(1000);   
   }	
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



