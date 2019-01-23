#include "pbdata.h"

void RCC_Configuration(void);
void GPIO_Configuration(void);

int main(void)
{
	 int n = 5;//延迟的次数
   RCC_Configuration();	//系统时钟初始化
   GPIO_Configuration();//端口初始化
   
	while( n-- )
	{
		GPIO_SetBits(GPIOB,GPIO_Pin_5);//设置指定的数据端口位
		delay(6000000);//0.5s
		GPIO_ResetBits(GPIOB,GPIO_Pin_5);//清除指定的数据端口位
		delay(6000000);//0.5s
	}
}

void RCC_Configuration(void)
{
  SystemInit();//系统时钟
	//RCC_APB2PeriphClockCmd 使能或者失能APB2外设时钟
	//参数1：门控APB2外设时钟
	//参数2：指定外设时钟的新状态，取值为ENABLE或者DISABLE
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	//RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
}

void GPIO_Configuration(void)
{
	//根据GPIO_InitStruct中指定的参数初始化外设GPIOx寄存器
    GPIO_InitTypeDef GPIO_InitStructure;	//定义结构体变量

	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_5;//待设置的GPIO管脚
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;//设置选中管脚的速率
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;//设置选中管脚的工作状态，GPIO_Mode_AF_PP 复用推挽输出
	//GPIO_InitStruct中指定的参数初始化外设GPIOx寄存器
	//参数1：GPIOx：x可以是A，B，C，D或者E，来选择GPIO外设
	//参数2：GPIO_InitStruct：指向结构GPIO_InitTypeDef的指针，包含了外设GPIO的配置信息
	GPIO_Init(GPIOB,&GPIO_InitStructure);
}

