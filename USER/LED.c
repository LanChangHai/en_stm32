#include "STM32_head.h"
#include "stm32f10x.h"
#include <string.h>
#include "usmart.h"
#include "usmart_str.h"
#include <STM32_ADC.h>
unsigned int Timer2_Counter=0; //Timer2定时器计数变量(ms)
unsigned int W5500_Send_Delay_Counter=0; //W5500发送延时计数变量(ms)
extern unsigned char http_Buff[2048];

int main(void){
	Stm32_Clock_Init(9);//系统时钟初始化 8M主频 9M倍频 72M系统时钟频率
		delay_init(72);//延时函数初始化 8*9=72M
	gpio_init(B5,GPIO_OUT,Push_pull_output);
		gpio_init(A0,0,2);	
	EXTIX_Init();
		delay_ms(500);		
			gpio_SetIO(B5);
	while(1){
			

		}




}
