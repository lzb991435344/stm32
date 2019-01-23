#include "pbdata.h"

void RCC_Configuration(void);
void GPIO_Configuration(void);

int main(void)
{
   RCC_Configuration();	//ϵͳʱ�ӳ�ʼ��
   GPIO_Configuration();//�˿ڳ�ʼ��
   
	while(1)
	{
		//GPIO_ReadInputDataBit��ȡָ���˿ڹܽŵ�����
		//����1��GPIOx��x������A��B��C��D����E����ѡ��GPIO����
		//����2��GPIO_Pin������ȡ�Ķ˿�λ
		/*
		typedef enum
   { Bit_RESET = 0,
     Bit_SET
     }BitAction;
		*/
		if(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_5) == Bit_RESET)
		{
			//LED1 ����
			GPIO_ResetBits(GPIOB,GPIO_Pin_5);
		}
		else
		{
		   //LED1 Ϩ��
		   GPIO_SetBits(GPIOB,GPIO_Pin_5);
		}
		
		//LED2,KEY2
		if(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_1) == Bit_RESET)
		{
			GPIO_ResetBits(GPIOD,GPIO_Pin_6);
		}
		else
		{
		  GPIO_SetBits(GPIOD,GPIO_Pin_6);
		}
		
		//LED3,KEY3
		if(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_2) == Bit_RESET)
		{
			GPIO_ResetBits(GPIOD,GPIO_Pin_3);
		}
		else
		{
		  GPIO_SetBits(GPIOD,GPIO_Pin_3);
		}
		
		//LDE1,2,3
		if(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_3)  == Bit_RESET)
		{
			GPIO_ResetBits(GPIOB,GPIO_Pin_5);
			GPIO_ResetBits(GPIOD,GPIO_Pin_6);
			GPIO_ResetBits(GPIOD,GPIO_Pin_3);
		}
		else
		{
			//GPIO_SetBits(GPIOB,GPIO_Pin_5);
			//GPIO_SetBits(GPIOD,GPIO_Pin_6);
		  GPIO_SetBits(GPIOC,GPIO_Pin_3);
		}
	}
}

void RCC_Configuration(void)
{
  SystemInit();
	//RCC_APB2PeriphClockCmd ʹ�ܻ���ʧ��APB2����ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);//B�˿�
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);//C�˿�
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD,ENABLE);//D�˿�
}

void GPIO_Configuration(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;	
	//LED1
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_Init(GPIOB,&GPIO_InitStructure);

	//KEY1����������
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;//��������ģʽ
	GPIO_Init(GPIOC,&GPIO_InitStructure);
	
	
	//LED2
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_Init(GPIOD,&GPIO_InitStructure);

	//KEY2����������
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;//��������ģʽ
	GPIO_Init(GPIOC,&GPIO_InitStructure);
	
	
	//LED3
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_Init(GPIOD,&GPIO_InitStructure);

	//KEY3����������
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;//��������ģʽ
	GPIO_Init(GPIOC,&GPIO_InitStructure);
	
	//LED1,2,3
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_Init(GPIOD,&GPIO_InitStructure);
	
	//KEY4
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;//��������ģʽ
	GPIO_Init(GPIOC,&GPIO_InitStructure);
}

