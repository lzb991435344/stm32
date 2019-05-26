#include "pbdata.h"

void RCC_Configuration(void);
void GPIO_Configuration(void);
void NVIC_Configuration(void);
void USART_Configuration(void);
int main(void)
{
   RCC_Configuration();	//ϵͳʱ�ӳ�ʼ��
   GPIO_Configuration();//�˿ڳ�ʼ��
   USART_Configuration();
   NVIC_Configuration();//�ж����ȼ�����
   
   while(1);	
}

void RCC_Configuration(void)
{
    SystemInit();//72m
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);//GPIOAʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);//USART1ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);//���ܸ���IOʱ��
}

void GPIO_Configuration(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;	
	//LED
	//TX
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_9;//TX
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;//������������������ǿ
	GPIO_Init(GPIOA,&GPIO_InitStructure);

	//RX
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_10;//RX
	//�������룬�������ĵ�ѹ�仯���仯����ȡ�����ź�
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
}

void NVIC_Configuration(void)
{
	/**
	typedef struct
	{
		u8 NVIC_IRQChannel;//�ò�������ʹ�ܻ���ʧ��ָ����IRQͨ��
		u8 NVIC_IRQChannelPreemptionPriority;//�ò��������˳�ԱNVIC_IRQChannel�е���ռ����
		u8 NVIC_IRQChannelSubPriority;//�ò��������˳�ԱNVIC_IRQChannel�еĴ�����
		FunctionalState NVIC_IRQChannelCmd;//�ò���ָ�����ڳ�ԱNVIC_IRQChannel�ж����IRQͨ����ʹ�ܻ���ʧ�ܡ��������ȡֵΪENABLE����DISABLE��
	} NVIC_InitTypeDef;
	
	*/
   	NVIC_InitTypeDef NVIC_InitStructure; 
  //��ռ���ȼ�1λ�������ȼ�3λ
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
u32 USART_BaudRate;//�ó�Ա������USART����Ĳ�����
u16 USART_WordLength;//��ʾ����һ��֡�д�����߽��յ�������λ��
u16 USART_StopBits;//SART_StopBits�����˷��͵�ֹͣλ��
u16 USART_Parity;//USART_Parity��������żģʽ
u16 USART_HardwareFlowControl;//USART_HardwareFlowControlָ����Ӳ��������ģʽʹ�ܻ���ʧ��
u16 USART_Mode;//USART_Modeָ����ʹ�ܻ���ʧ�ܷ��ͺͽ���ģʽ
u16 USART_Clock;//USART_CLOCK��ʾ��USARTʱ��ʹ�ܻ���ʧ��
u16 USART_CPOL;//USART_CPOLָ������SLCK������ʱ������ļ���
u16 USART_CPHA;//USART_CPHAָ������SLCK������ʱ���������λ����CPOLλһ������������û�ϣ����ʱ��/���ݵĲ�����ϵ��
u16 USART_LastBit;//SART_LastBit�������Ƿ���ͬ��ģʽ�£���SCLK�������������͵��Ǹ������� (MSB)��Ӧ��ʱ������
} USART_InitTypeDef;
	*/
  USART_InitTypeDef  USART_InitStructure;

	USART_InitStructure.USART_BaudRate=9600;//1������ = 1bps(λ/��)
	USART_InitStructure.USART_WordLength=USART_WordLength_8b;
	USART_InitStructure.USART_StopBits=USART_StopBits_1;
	USART_InitStructure.USART_Parity=USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl=USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode=USART_Mode_Rx|USART_Mode_Tx;

	USART_Init(USART1,&USART_InitStructure);
	/**
	void USART_ITConfig(USART_TypeDef* USARTx, u16 USART_IT, FunctionalState NewState)
	@function ʹ�ܻ���ʧ��ָ����USART�ж�
	@param1 USARTx��x������1��2����3����ѡ��USART����
	@param2 USART_IT����ʹ�ܻ���ʧ�ܵ�USART�ж�Դ
	@param3 NewState��USARTx�жϵ���״̬,�����������ȡ��ENABLE����DISABLE
	@return  void
	*/
	USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);
	
	USART_Cmd(USART1,ENABLE);
	/**
	void USART_ClearFlag(USART_TypeDef* USARTx, u16 USART_FLAG)
	@function ���USARTx�Ĵ������־λ
	@param1 USARTx��x������1��2����3����ѡ��USART����
	@param2 USART_FLAG���������USART��־λ,ͨ��FlagStatus USART_GetFlagStatus(USART_TypeDef* USARTx, u16 USART_FLAG)��������ȡ
	@return void
	*/
	USART_ClearFlag(USART1,USART_FLAG_TC);//�������ֱ�ӽ��뷢�͵�״̬�������һ����ĸ�޷����ͳ�ȥ
}



