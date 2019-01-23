#include "pbdata.h"

void RCC_Configuration(void);
void GPIO_Configuration(void);
void NVIC_Configuration(void);
void TIM3_Configuration(void);

int main(void)
{
   RCC_Configuration();	//ϵͳʱ�ӳ�ʼ��
   GPIO_Configuration();//�˿ڳ�ʼ��
   TIM3_Configuration();
   NVIC_Configuration();
   
   while(1);	
}

void RCC_Configuration(void)
{
  SystemInit();
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
}

void GPIO_Configuration(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;	
	//LED
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
}

void TIM3_Configuration(void)
{
	/**
	    typedef struct
      {
         u16 TIM_Period;
         u16 TIM_Prescaler;
         u8 TIM_ClockDivision;
         u16 TIM_CounterMode;
      } TIM_TimeBaseInitTypeDef;
	*/
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStruct;
	
	//���TIMx���жϴ�����λ
	TIM_ClearITPendingBit(TIM3,TIM_IT_Update);
	
  //��ֵ,TIM_Period����������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ������ȡֵ������0x0000��0xFFFF֮�䡣
	TIM_TimeBaseStruct.TIM_Period=2000;
	
	//TIM_Prescaler������������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ������ȡֵ������0x0000��0xFFFF֮�䡣
	TIM_TimeBaseStruct.TIM_Prescaler=35999;//Ԥ��Ƶ
	
	//TIM_ClockDivision������ʱ�ӷָ�
	TIM_TimeBaseStruct.TIM_ClockDivision=0;
	
	//TIM_CounterModeѡ���˼�����ģʽ
	TIM_TimeBaseStruct.TIM_CounterMode=TIM_CounterMode_Up;//����

  //����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
	//����1��TIMx��x������2��3����4����ѡ��TIM����
	//����2��TIMTimeBase_InitStruct��ָ��ṹTIM_TimeBaseInitTypeDef��ָ�룬������TIMxʱ�������λ��������Ϣ
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseStruct);
   
	 //ʹ�ܻ���ʧ��ָ����TIM�ж�
	 //����1��TIMx��x������2��3����4����ѡ��TIM����
	 //����2��TIM_IT����ʹ�ܻ���ʧ�ܵ�TIM�ж�Դ
	 //����3��NewState��TIMx�жϵ���״̬
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE);
	
	//ʹ�ܻ���ʧ��TIMx����
	TIM_Cmd(TIM3,ENABLE);	 
}

void NVIC_Configuration(void)
{
   	NVIC_InitTypeDef NVIC_InitStructure; 

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1); 

	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn; 
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; 
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1; 
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 
	NVIC_Init(&NVIC_InitStructure);
}


