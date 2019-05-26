#include "pbdata.h"

void RCC_Configuration(void);
void GPIO_Configuration(void);
void NVIC_Configuration(void);
void USART_Configuration(void);

#define FLASH_ADR 0x0807F800  //д�����ݵĵ�ַ
int fputc(int ch,FILE *f)
{
	/**
	 void USART_SendData(USART_TypeDef* USARTx, u8 Data)
	  @function  ͨ������USARTx���͵�������
	  @param1  USARTx��x������1��2����3����ѡ��USART����
	  @param2  Data: �����͵�����
		@return void
	*/
	USART_SendData(USART1,(u8)ch);
	/*
	FlagStatus USART_GetFlagStatus(USART_TypeDef* USARTx, u16 USART_FLAG)
	 @function:���ָ����USART��־λ�������
	 @param1  USARTx��x������1��2����3����ѡ��USART����
	 @param2  USART_FLAG��������USART��־λ
	 @return :USART_FLAG����״̬��SET����RESET��	
	*/
	while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)==RESET);
	return ch;
}

int main(void)
{
   u32 data=12345678;

   RCC_Configuration();	//ϵͳʱ�ӳ�ʼ��
   GPIO_Configuration();//�˿ڳ�ʼ��
   USART_Configuration();
   NVIC_Configuration();

	//����
	FLASH_Unlock();
	//�����־λ
	//��־λ�ֱ�Ϊ æ��־λ������������־λ����д�����־λ��ҳ��д���������־λ
	FLASH_ClearFlag(FLASH_FLAG_BSY|FLASH_FLAG_EOP|
					FLASH_FLAG_PGERR|FLASH_FLAG_WRPRTERR);
	
	//Ҫ����ҳ����ʼ��ַ
	FLASH_ErasePage(FLASH_ADR);  //#define FLASH_ADR 0x0807F800
	//д����
	FLASH_ProgramWord(FLASH_ADR,data);

	//FLASH_ProgramWord(FLASH_ADR+4,data);

	//����
	FLASH_Lock();

	data=0;//����ֵΪ0
	data=(*(__IO uint32_t*)(FLASH_ADR)); //���ض��ĵ�ַȡֵ
	printf("��� data=%d\r\n",data);   
    while(1); //ѭ���ȴ�
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



