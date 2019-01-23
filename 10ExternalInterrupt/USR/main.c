#include "pbdata.h"

void RCC_Configuration(void);
void GPIO_Configuration(void);
void EXTI_Configuration(void);
void NVIC_Configuration(void);

int main(void)
{
   RCC_Configuration();	//ϵͳʱ�ӳ�ʼ��
   GPIO_Configuration();//�˿ڳ�ʼ��
   EXTI_Configuration();
   NVIC_Configuration();
   
   while(1);	
}

void RCC_Configuration(void)
{
    SystemInit();
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);//RCC_APB2Periph_GPIOA GPIOAʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);//RCC_APB2Periph_AFIO ���ܸ���IOʱ��
}

void GPIO_Configuration(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;	
	//LED
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_Init(GPIOB,&GPIO_InitStructure);

	//KEY
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;
	GPIO_Init(GPIOC,&GPIO_InitStructure);
}

void EXTI_Configuration(void)
{
	/**�ṹ������
  typedef struct { u32 EXTI_Line;
	  EXTIMode_TypeDef EXTI_Mode; 
	  EXTIrigger_TypeDef EXTI_Trigger; 
	  FunctionalState EXTI_LineCmd; } EXTI_InitTypeDef; 
	*/
	EXTI_InitTypeDef EXTI_InitStructure; 

	//�����·
	//void EXTI_ClearITPendingBit(u32 EXTI_Line)  ���EXTI��·����λ
	EXTI_ClearITPendingBit(EXTI_Line5);
	
	//GPIO_EXTILineConfig ѡ��GPIO�ܽ������ⲿ�ж���·
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOC, GPIO_PinSource5); 

	EXTI_InitStructure.EXTI_Line=EXTI_Line5;//�ⲿ�ж���5
	
	//EXTI_Mode_Interrupt ����EXTI��·Ϊ�ж����� ;EXTI_Mode_Event ����EXTI��·Ϊ�¼�����
	EXTI_InitStructure.EXTI_Mode=EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger=EXTI_Trigger_Falling;//����������·�½���Ϊ�ж�����
	EXTI_InitStructure.EXTI_LineCmd=ENABLE;//EXTI_LineCmd��������ѡ����·����״̬�������Ա���ΪENABLE����DISABLE��

	 //EXTI_InitTypeDef ����EXTI_InitStruct��ָ���Ĳ�����ʼ������EXTI�Ĵ���
	 //������ָ��ṹEXTI_InitTypeDef��ָ�룬����������EXTI��������Ϣ
	EXTI_Init(&EXTI_InitStructure);
}

void NVIC_Configuration(void)
{
	/**
	  typedef struct
   {
    u8 NVIC_IRQChannel;
    u8 NVIC_IRQChannelPreemptionPriority;
    u8 NVIC_IRQChannelSubPriority;
    FunctionalState NVIC_IRQChannelCmd;
   } NVIC_InitTypeDef;
	*/
  NVIC_InitTypeDef NVIC_InitStructure; 

	//NVIC_PriorityGroupConfig���õ���ռ���ȼ��ʹ����ȼ���ȡ��ֵ
	//������NVIC_PriorityGroup_1 0-1(��ռ���ȼ�) 0-7(�����ȼ�) ��ռ���ȼ�1λ �����ȼ�3λ
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1); 

	NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn; //EXTI9_5_IRQChannel �ⲿ�ж���9-5�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; 
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1; 
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 
	
	/**
	 ����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���
   �������
   NVIC_InitStruct��ָ��ṹNVIC_InitTypeDef��ָ�룬����������GPIO��������Ϣ
	*/
	NVIC_Init(&NVIC_InitStructure);
}


