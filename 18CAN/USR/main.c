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
	
	RCC_Configuration();	//系统时钟初始化
	GPIO_Configuration();//端口初始化
	USART_Configuration();
	NVIC_Configuration();
	CAN_Configuration();
	
	while(1)
	{
		//TxMessage.StdId=0xFE00>>5;
		//TxMessage.ExtId=0;
		//TxMessage.IDE=CAN_ID_STD;//标准帧
   		TxMessage.StdId=0;
		TxMessage.ExtId=0xFFFFFFFF>>3;
		
    //扩展帧
		TxMessage.IDE=CAN_ID_EXT;
		
		//数据帧
		TxMessage.RTR=CAN_RTR_DATA;
		
		//远程帧
		TxMessage.RTR=CAN_RTR_REMOTE;
		TxMessage.DLC=8;//发送8个字节
		TxMessage.Data[0]=0x11;
		
		TxMessage.Data[1]=0x22;
		TxMessage.Data[2]=0x33;
		TxMessage.Data[3]=0x44;
		TxMessage.Data[4]=0x55;
		TxMessage.Data[5]=0x66;
		TxMessage.Data[6]=0x77;
		TxMessage.Data[7]=0x88;
		//CAN 发送数据
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

void GPIO_Configuration(void)//GPIO的设置
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

	//端口映射
	GPIO_PinRemapConfig(GPIO_Remap1_CAN1,ENABLE);

	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_8;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;
	GPIO_Init(GPIOB,&GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_9;//TX
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
}

void NVIC_Configuration(void) //中断配置
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

void USART_Configuration(void) //串口的配置
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

void CAN_Configuration(void) //CAN的配置
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

   //关闭时间触发模式
   CAN_InitStructure.CAN_TTCM=DISABLE;
   //关闭自动离线管理
   CAN_InitStructure.CAN_ABOM=DISABLE;
   //关闭自动唤醒模式
   CAN_InitStructure.CAN_AWUM=DISABLE;
   //禁止报文自动重传
   CAN_InitStructure.CAN_NART=DISABLE;
   //FIFO 溢出时报文覆盖源文件
   CAN_InitStructure.CAN_RFLM=DISABLE;
   //报文发送优先级取决于ID号
   CAN_InitStructure.CAN_TXFP=DISABLE;
   //正常的工作模式
   CAN_InitStructure.CAN_Mode=CAN_Mode_Normal;

   // 设置CAN 波特率  125 KBPS

   CAN_InitStructure.CAN_SJW=CAN_SJW_1tq;
   CAN_InitStructure.CAN_BS1=CAN_BS1_3tq;
   CAN_InitStructure.CAN_BS2=CAN_BS2_2tq;
   CAN_InitStructure.CAN_Prescaler = 48;


   //初始化CAN
   CAN_Init(CAN1,&CAN_InitStructure);

   //屏蔽滤波
   CAN_FilterInitStructure.CAN_FilterNumber=0;
   //屏蔽模式
   CAN_FilterInitStructure.CAN_FilterMode=CAN_FilterMode_IdMask;
   //32位寄存器
   CAN_FilterInitStructure.CAN_FilterScale=CAN_FilterScale_32bit;
	 
   //高16位
   CAN_FilterInitStructure.CAN_FilterIdHigh=0x0000;
   //低16位
   CAN_FilterInitStructure.CAN_FilterIdLow=0;
   //屏蔽位高16位
   CAN_FilterInitStructure.CAN_FilterMaskIdHigh=0x0000;
   //屏蔽位低16位
   CAN_FilterInitStructure.CAN_FilterMaskIdLow=0;
	 
   //过滤器 0 关联到 FIFO0，过滤器关联到特定的缓冲区
   CAN_FilterInitStructure.CAN_FilterFIFOAssignment=CAN_Filter_FIFO0;
   //使能过滤器
   CAN_FilterInitStructure.CAN_FilterActivation=ENABLE;
   //初始化过滤器
   CAN_FilterInit(&CAN_FilterInitStructure);

   //使能接收中断
   CAN_ITConfig(CAN1,CAN_IT_FMP0,ENABLE);
}
