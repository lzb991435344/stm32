#include "pbdata.h"

void RCC_Configuration(void);
void GPIO_Configuration(void);
void TIM3_Configuration(void);

int main(void)
{
   u8 led_fx=1;
   u16 led_dt=0;

   RCC_Configuration();	//ϵͳʱ�ӳ�ʼ��
   GPIO_Configuration();//�˿ڳ�ʼ��
   TIM3_Configuration();//��ʱ����pwm���� 
   while(1)
   {
   	 delay_ms(10);
	 if(led_fx==1)
	 {
	 	led_dt++;
	 }
	 else
	 {
	   led_dt--;
	 }

	 if(led_dt>300)  led_fx=0;
   	 if(led_dt==0)	 led_fx=1;

	 TIM_SetCompare2(TIM3,led_dt);
   }	
}

void RCC_Configuration(void)
{
  SystemInit();
	/**
	void RCC_AHBPeriphClockCmd(u32 RCC_AHBPeriph,FunctionalState NewState)
	@function ʹ�ܻ���ʧ��AHB����ʱ��
	@param1 RCC_AHBPeriph: �ſ�AHB����ʱ��
	@param2 NewState��ָ������ʱ�ӵ���״̬�������������ȡ��ENABLE����DISABLE
	@return void
	*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);//GPIOBʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);//TIM3ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);//���ܸ���IOʱ��
}

//GPIOʱ�����ú���
void GPIO_Configuration(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;	
	//LED
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;//ѡ�����������
	GPIO_Init(GPIOB,&GPIO_InitStructure);
}

//TIM3ʼ������
void TIM3_Configuration(void)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStruct;
	/**
	typedef struct
  {
	u16 TIM_OCMode;//ѡ��ʱ����ģʽ
	u16 TIM_Channel;//ѡ��ͨ��
	u16 TIM_Pulse;//�����˴�װ�벶��ȽϼĴ���������ֵ������ȡֵ������0x0000��0xFFFF֮
	u16 TIM_OCPolarity;//������ԣ����Եĸߵ�
	} TIM_OCInitTypeDef;
	*/
	//����TIM_OCInitStruct��ָ���Ĳ�����ʼ������TIMx
	TIM_OCInitTypeDef TIM_OCInitStructure; 

	GPIO_PinRemapConfig(GPIO_PartialRemap_TIM3,ENABLE);

	//��ʱ����ʼ��
	TIM_TimeBaseStruct.TIM_Period=899;//��ֵ�����ý�ȥ֮�����м�1������������Ϊ899
	TIM_TimeBaseStruct.TIM_Prescaler=0;//Ԥ��Ƶ
	TIM_TimeBaseStruct.TIM_ClockDivision=0;
	TIM_TimeBaseStruct.TIM_CounterMode=TIM_CounterMode_Up;//����
	
  /**
	void TIM_TimeBaseInit(TIM_TypeDef* TIMx, TIM_TimeBaseInitTypeDef* TIM_TimeBaseInitStruct)
	
	@function ����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
	@param1 TIMx��x������2��3����4����ѡ��TIM����
	@param2 TIMTimeBase_InitStruct��ָ��ṹTIM_TimeBaseInitTypeDef��ָ�룬������TIMxʱ�������λ��������Ϣ
	@return void
	*/
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseStruct);
	

	//pwm ��ʼ��
	TIM_OCInitStructure.TIM_OCMode=TIM_OCMode_PWM1;//TIM�����ȵ���ģʽ1
	TIM_OCInitStructure.TIM_OutputState=TIM_OutputState_Enable;//����Ϊ�����ģʽ
	//TIM����Ƚϼ��Ե�,���ӵ��ǹܽ�5�͵�ƽ�ˣ�������������Ҫ����Ϊ���Ե�
	TIM_OCInitStructure.TIM_OCPolarity=TIM_OCPolarity_Low;

	TIM_OC2Init(TIM3,&TIM_OCInitStructure);
	/**
	void TIM_OC2PreloadConfig(TIM_TypeDef* TIMx, u16 TIM_OCPreload)
	@function ʹ�ܻ���ʧ��TIMx��CCR2�ϵ�Ԥװ�ؼĴ���
	@param1 TIMx��x������2��3����4����ѡ��TIM����
	@param2 TIM_OCPreload������Ƚ�Ԥװ��״̬
	@return void
	*/
	TIM_OC2PreloadConfig(TIM3,TIM_OCPreload_Enable);
	/**
	void TIM_Cmd(TIM_TypeDef* TIMx, FunctionalState NewState)
	@function ʹ�ܻ���ʧ��TIMx����
	@param1 TIMx��x������2��3����4����ѡ��TIM����
	@param2 NewState: ����TIMx����״̬,�����������ȡ��ENABLE����DISABLE
	@return void
	*/
	TIM_Cmd(TIM3,ENABLE);
		 
}
