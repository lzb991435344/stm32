#include "pbdata.h"

void RCC_Configuration(void);
void GPIO_Configuration(void);

int main(void)
{
	 int n = 5;
   RCC_Configuration();	//ϵͳʱ�ӳ�ʼ��
   RCC_HSE_Configuration();	//ϵͳʱ�ӳ�ʼ��(�Զ���)
   GPIO_Configuration();//�˿ڳ�ʼ��
   
	while(n--)
	{
		GPIO_SetBits(GPIOE,GPIO_Pin_2);
		delay_ms(1000);//0.5S
		GPIO_ResetBits(GPIOE,GPIO_Pin_2);
		delay_ms(1000);//0.5S
	}
}

void RCC_Configuration(void)
{
    SystemInit();
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE,ENABLE);
}

void GPIO_Configuration(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;	

	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_Init(GPIOE,&GPIO_InitStructure);
}

