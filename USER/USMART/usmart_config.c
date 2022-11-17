#include "usmart.h"
#include "usmart_str.h"
////////////////////////////�û�������///////////////////////////////////////////////
//������Ҫ�������õ��ĺ�����������ͷ�ļ�(�û��Լ����) 
#include "delay.h"	 	
#include "sys.h"
//#include "lcd.h"
#include "STM32_head.h"

extern void gpio_init(PIN_enum pin,uint16_t GPIO_Speed,uint16_t GPIO_Mode);
extern void show_ADC1(USART_TypeDef * USARTx,PIN_enum pin);
//�������б��ʼ��(�û��Լ����)
//�û�ֱ������������Ҫִ�еĺ�����������Ҵ�
struct _m_usmart_nametab usmart_nametab[]=
{
#if USMART_USE_WRFUNS==1 	//���ʹ���˶�д����
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
//�������ƹ�������ʼ��
//�õ������ܿغ���������
//�õ�����������
struct _m_usmart_dev usmart_dev=
{
	usmart_nametab,
	usmart_init,
	usmart_cmd_rec,
	usmart_exe,
	usmart_scan,
	sizeof(usmart_nametab)/sizeof(struct _m_usmart_nametab),//��������
	0,	  	//��������
	0,	 	//����ID
	1,		//������ʾ����,0,10����;1,16����
	0,		//��������.bitx:,0,����;1,�ַ���	    
	0,	  	//ÿ�������ĳ����ݴ��,��ҪMAX_PARM��0��ʼ��
	0,		//�����Ĳ���,��ҪPARM_LEN��0��ʼ��
};   



















