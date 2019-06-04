#include "pbdata.h"

void RCC_Configuration(void);
void GPIO_Configuration(void);
void NVIC_Configuration(void);
void USART_Configuration(void);
void CAN_Configuration(void);

int fputc(int ch,FILE *f)
{
	USART_SendData(USART1,(u8)ch);
	while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)==RESET);
	return ch;
}

int main(void)
{
	CanTxMsg TxMessage;
	
	RCC_Configuration();	//ϵͳʱ�ӳ�ʼ��
	GPIO_Configuration();//�˿ڳ�ʼ��
	USART_Configuration();
	NVIC_Configuration();
	CAN_Configuration();
	
	while(1)
	{
		//TxMessage.StdId=0xFE00>>5;
		//TxMessage.ExtId=0;
		//TxMessage.IDE=CAN_ID_STD;//��׼֡
   		TxMessage.StdId=0;
		TxMessage.ExtId=0xFFFFFFFF>>3;
		
    //��չ֡
		TxMessage.IDE=CAN_ID_EXT;
		
		//����֡
		TxMessage.RTR=CAN_RTR_DATA;
		
		//Զ��֡
		TxMessage.RTR=CAN_RTR_REMOTE;
		TxMessage.DLC=8;//����8���ֽ�
		TxMessage.Data[0]=0x11;
		
		TxMessage.Data[1]=0x22;
		TxMessage.Data[2]=0x33;
		TxMessage.Data[3]=0x44;
		TxMessage.Data[4]=0x55;
		TxMessage.Data[5]=0x66;
		TxMessage.Data[6]=0x77;
		TxMessage.Data[7]=0x88;
		//CAN ��������
		CAN_Transmit(CAN1,&TxMessage);		
		delay_ms(1000);   
	}	
}

void RCC_Configuration(void)
{
  SystemInit();//72m
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN1,ENABLE);
}

void GPIO_Configuration(void)//GPIO������
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

	//�˿�ӳ��
	GPIO_PinRemapConfig(GPIO_Remap1_CAN1,ENABLE);

	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_8;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;
	GPIO_Init(GPIOB,&GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_9;//TX
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
}

void NVIC_Configuration(void) //�ж�����
{
  NVIC_InitTypeDef NVIC_InitStructure; 

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1); 

	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn; 
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; 
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1; 
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 
	NVIC_Init(&NVIC_InitStructure);

	NVIC_InitStructure.NVIC_IRQChannel = USB_LP_CAN1_RX0_IRQn; 
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; 
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0; 
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 
	NVIC_Init(&NVIC_InitStructure);
}

void USART_Configuration(void) //���ڵ�����
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

void CAN_Configuration(void) //CAN������
{
	
	/**
	typedef struct {
	FunctionnalState CAN_TTCM;
	FunctionnalState CAN_ABOM;
	FunctionnalState CAN_AWUM;
	FunctionnalState CAN_NART; 
	FunctionnalState CAN_RFLM; 
	FunctionnalState CAN_TXFP;
	u8 CAN_Mode; 
	u8 CAN_SJW; 
	u8 CAN_BS1; 
	u8 CAN_BS2;
	u16 CAN_Prescaler; 
	} CAN_InitTypeDef;
	
	
	*/
   CAN_InitTypeDef CAN_InitStructure;
   CAN_FilterInitTypeDef CAN_FilterInitStructure;

   CAN_DeInit(CAN1);
   CAN_StructInit(&CAN_InitStructure);

   //�ر�ʱ�䴥��ģʽ
   CAN_InitStructure.CAN_TTCM=DISABLE;
   //�ر��Զ����߹���
   CAN_InitStructure.CAN_ABOM=DISABLE;
   //�ر��Զ�����ģʽ
   CAN_InitStructure.CAN_AWUM=DISABLE;
   //��ֹ�����Զ��ش�
   CAN_InitStructure.CAN_NART=DISABLE;
   //FIFO ���ʱ���ĸ���Դ�ļ�
   CAN_InitStructure.CAN_RFLM=DISABLE;
   //���ķ������ȼ�ȡ����ID��
   CAN_InitStructure.CAN_TXFP=DISABLE;
   //�����Ĺ���ģʽ
   CAN_InitStructure.CAN_Mode=CAN_Mode_Normal;

   // ����CAN ������  125 KBPS

   CAN_InitStructure.CAN_SJW=CAN_SJW_1tq;
   CAN_InitStructure.CAN_BS1=CAN_BS1_3tq;
   CAN_InitStructure.CAN_BS2=CAN_BS2_2tq;
   CAN_InitStructure.CAN_Prescaler = 48;


   //��ʼ��CAN
   CAN_Init(CAN1,&CAN_InitStructure);

   //�����˲�
   CAN_FilterInitStructure.CAN_FilterNumber=0;
   //����ģʽ
   CAN_FilterInitStructure.CAN_FilterMode=CAN_FilterMode_IdMask;
   //32λ�Ĵ���
   CAN_FilterInitStructure.CAN_FilterScale=CAN_FilterScale_32bit;
	 
   //��16λ
   CAN_FilterInitStructure.CAN_FilterIdHigh=0x0000;
   //��16λ
   CAN_FilterInitStructure.CAN_FilterIdLow=0;
   //����λ��16λ
   CAN_FilterInitStructure.CAN_FilterMaskIdHigh=0x0000;
   //����λ��16λ
   CAN_FilterInitStructure.CAN_FilterMaskIdLow=0;
	 
   //������ 0 ������ FIFO0���������������ض��Ļ�����
   CAN_FilterInitStructure.CAN_FilterFIFOAssignment=CAN_Filter_FIFO0;
   //ʹ�ܹ�����
   CAN_FilterInitStructure.CAN_FilterActivation=ENABLE;
   //��ʼ��������
   CAN_FilterInit(&CAN_FilterInitStructure);

   //ʹ�ܽ����ж�
   CAN_ITConfig(CAN1,CAN_IT_FMP0,ENABLE);
}
