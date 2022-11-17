#include "usmart.h"
#include "usmart_str.h"
////////////////////////////用户配置区///////////////////////////////////////////////
//这下面要包含所用到的函数所申明的头文件(用户自己添加) 
#include "delay.h"	 	
#include "sys.h"
//#include "lcd.h"
#include "STM32_head.h"

extern void gpio_init(PIN_enum pin,uint16_t GPIO_Speed,uint16_t GPIO_Mode);
extern void show_ADC1(USART_TypeDef * USARTx,PIN_enum pin);
//函数名列表初始化(用户自己添加)
//用户直接在这里输入要执行的函数名及其查找串
struct _m_usmart_nametab usmart_nametab[]=
{
#if USMART_USE_WRFUNS==1 	//如果使能了读写操作
	(void*)read_addr,"u32 read_addr(u32 addr)",
	(void*)write_addr,"void write_addr(u32 addr,u32 val)",	 
#endif		   
	(void*)delay_ms,"void delay_ms(u16 nms)",
 	(void*)delay_us,"void delay_us(u32 nus)",	 
	(void*)USART_Get_state,"uint8_t USART_Get_state(USART_TypeDef * USARTx)", 
	(void*)USART_Sent_state,"uint8_t USART_Sent_state(USART_TypeDef * USARTx)",
	(void*)USART_Get_char,"uint8_t USART_Get_char(USART_TypeDef * USARTx)",
	(void*)USART_Sent_char,"void USART_Sent_char(USART_TypeDef * USARTx,uint8_t RT)",
	(void*)USART_Sent_String,"void USART_Sent_String(USART_TypeDef * USARTx,char *p,char q)",
	(void*)TIM_PWM_init,"void TIM_PWM_init(TIM_TypeDef * TIMx,uint8_t CHx,uint32_t psc,uint32_t arr)",
	(void*)PWM_change_CCRx,"void PWM_change_CCRx(TIM_TypeDef * TIMx,uint8_t CHx,uint16_t ccr1)",
	(void*)TIMx_irq_init,"void TIMx_irq_init(TIM_TypeDef * TIMx,u16 arr,u16 psc)",
	(void*)TIMx_irq_close,"void TIMx_irq_close(TIM_TypeDef * TIMx)",
	(void*)ADC1_init,"void ADC1_init(PIN_enum pin)",
	(void*)ADC2_init,"void ADC2_init(PIN_enum pin)",
	(void*)get_ADC1,"u16 get_ADC1(PIN_enum pin)",
	(void*)get_ADC2,"u16 get_ADC2(PIN_enum pin)",
	(void*)show_ADC1,"void show_ADC1(USART_TypeDef * USARTx,PIN_enum pin)",
	(void*)show_ADC2,"void show_ADC2(USART_TypeDef * USARTx,PIN_enum pin)",
	(void*)USART_show,"USART_TypeDef * USART_show(char i)",
};						  
///////////////////////////////////END///////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
//函数控制管理器初始化
//得到各个受控函数的名字
//得到函数总数量
struct _m_usmart_dev usmart_dev=
{
	usmart_nametab,
	usmart_init,
	usmart_cmd_rec,
	usmart_exe,
	usmart_scan,
	sizeof(usmart_nametab)/sizeof(struct _m_usmart_nametab),//函数数量
	0,	  	//参数数量
	0,	 	//函数ID
	1,		//参数显示类型,0,10进制;1,16进制
	0,		//参数类型.bitx:,0,数字;1,字符串	    
	0,	  	//每个参数的长度暂存表,需要MAX_PARM个0初始化
	0,		//函数的参数,需要PARM_LEN个0初始化
};   



















