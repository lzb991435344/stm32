#include "pbdata.h"

void RCC_Configuration(void);
void GPIO_Configuration(void);
void NVIC_Configuration(void);
void USART_Configuration(void);

int fputc(int ch,FILE *f)
{
	USART_SendData(USART1,(u8)ch);//��Ҫ���͵����ݷ��͵�����
	while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)==RESET);//�ȴ����
	return ch;//��������
}

int main(void)
{
   u32 d1=0;
   float d2=0;
   u8   d3=0;
   u8   d4[5];

   RCC_Configuration();	//ϵͳʱ�ӳ�ʼ��
   GPIO_Configuration();//�˿ڳ�ʼ��
   USART_Configuration();
   NVIC_Configuration();
   
   while(1)
   {
      //printf("����Ƽ�\r\n");
	  //printf("www.zxkjmcu.com\r\n");

	  //d1=123456;
	  //printf("10����������� d1=%10d\r\n",d1);

	  //d1=123456;
	  //printf("16������� d1=%X\r\n",d1);//X ��д���  xСд���

	  //d2=12.345;
	  //printf("��������� d2=%f\r\n",d2);
	  ///printf("��������� d2=%.2f\r\n",d2);
	  //printf("��������� d2=%10.2f\r\n",d2);

	  //d3='a';
	  //printf("�ַ���� d3=%c\r\n",d3);


	  d4[0]='a';
	  d4[1]='b';
	  d4[2]='c';
	  d4[3]='d';
	  d4[4]='\0';

	  printf("�ַ������ d4=%s\r\n",d4);

	  //ע�� delay_ms�������뷶Χ��1-1863
	  //���������ʱΪ1.8��
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



