#include "pbdata.h"

void RCC_Configuration(void);
void GPIO_Configuration(void);

int main(void)
{
	 int n = 5;//�ӳٵĴ���
   RCC_Configuration();	//ϵͳʱ�ӳ�ʼ��
   GPIO_Configuration();//�˿ڳ�ʼ��
   
	while( n-- )
	{
		GPIO_SetBits(GPIOB,GPIO_Pin_5);//����ָ�������ݶ˿�λ
		delay(6000000);//0.5s
		GPIO_ResetBits(GPIOB,GPIO_Pin_5);//���ָ�������ݶ˿�λ
		delay(6000000);//0.5s
	}
}

void RCC_Configuration(void)
{
  SystemInit();//ϵͳʱ��
	//RCC_APB2PeriphClockCmd ʹ�ܻ���ʧ��APB2����ʱ��
	//����1���ſ�APB2����ʱ��
	//����2��ָ������ʱ�ӵ���״̬��ȡֵΪENABLE����DISABLE
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	//RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
}

void GPIO_Configuration(void)
{
	//����GPIO_InitStruct��ָ���Ĳ�����ʼ������GPIOx�Ĵ���
    GPIO_InitTypeDef GPIO_InitStructure;	//����ṹ�����

	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_5;//�����õ�GPIO�ܽ�
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;//����ѡ�йܽŵ�����
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;//����ѡ�йܽŵĹ���״̬��GPIO_Mode_AF_PP �����������
	//GPIO_InitStruct��ָ���Ĳ�����ʼ������GPIOx�Ĵ���
	//����1��GPIOx��x������A��B��C��D����E����ѡ��GPIO����
	//����2��GPIO_InitStruct��ָ��ṹGPIO_InitTypeDef��ָ�룬����������GPIO��������Ϣ
	GPIO_Init(GPIOB,&GPIO_InitStructure);
}

