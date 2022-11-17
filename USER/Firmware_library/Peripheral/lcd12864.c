#include "STM32_head.h"
#include "STM32_gpio.h"
/***********************************
file��lcd12864.c
���ߣ��
ʱ�䣺2019/7/20
���������������ѧǶ��ʽϵͳʵ����ʹ��
***********************************/
#define RST  A3
#define CS   A4
#define SCLK A5
#define SID  A7
//�˴��޸�ʹ�õ�����

static uint8_t nrow=0,ncol=0;
/************************************
������:LCD12864_Init
������ ��Ļ��ʼ��
���룺 ��
����� ��
������ LCD12864_Init();
***********************************/
void LCD12864_Init()
{
	gpio_init(RST,3,0);
	gpio_init(CS,3,0);
	gpio_init(SCLK,3,0);
	gpio_init(SID,3,0);
	
	gpio_Setstate(RST,0);
	delay_ms(20);
	gpio_Setstate(RST,1);
	LCD12864_Write(CMD,0x30);
	delay_ms(6);
	LCD12864_Write(CMD,0x0D);
	delay_ms(6);
	LCD12864_Write(CMD,0x01);
	delay_ms(6);
	LCD12864_Write(CMD,0x06);
	delay_ms(6);
}
/************************************
������:LCD12864_WriteChar
������ д�뵥���ַ�
���룺 dataҪд����ַ�
����� ��
������ LCD12864_WriteChar('A');//��ʾA
***********************************/
void LCD12864_WriteChar(uint8_t data)
{
	LCD12864_Write(DATA,data);
	if(ncol==15)
	{
		if(nrow == 3)
			nrow = 0;
		else
			nrow++;
		ncol = 0;
		LCD12864_SetCur(nrow,0);
	}
	else
		ncol++;
}
/************************************
������:LCD12864_WriteString
������ д���ַ���
���룺 *data�ַ�����ַ
����� ��
������ LCD12864_WriteString(":(");//��ʾ:(
***********************************/
void LCD12864_WriteString(char *data)
{
	while(*data != '\0')
	{
		LCD12864_Write(DATA,*data);
		data++;
		if(ncol==15)
		{
			if(nrow == 3)
				nrow = 0;
			else
				nrow++;
			ncol = 0;
			LCD12864_SetCur(nrow,0);
		}
		else
		{		
			ncol++;	
		}
	}
}
/************************************
������:LCD12864_SetCur
������ �����α�λ��
���룺 row ��,col ��
����� ��
������ LCD12864_SetCur(0,0);//�α����õ���0�е�0��
***********************************/
void LCD12864_SetCur(uint8_t row,uint8_t col)
{
	nrow = row;
	ncol = col*2;
	if(row%2)
	{
		LCD12864_Write(CMD,0x90+col+row/2*8);
	}
	else
	{
		LCD12864_Write(CMD,0x80+col+row/2*8);
	}
}
/************************************
(ϵͳ�Զ����ã��û�����Ҫ�鿴)
������:LCD12864_WriteByte
������ ��lcdд��1�ֽ�����
���룺 DbyteҪд�������
����� ��
������ LCD12864_WriteByte(0x04);
***********************************/
void LCD12864_WriteByte(uint8_t Dbyte)   
{   
	uint8_t i;   
	for(i=0;i<8;i++)   
    {   
		
		gpio_Setstate(SCLK,0); 
		if(Dbyte&0x80)
			gpio_Setstate(SID,1);
        else
            gpio_Setstate(SID,0);
        Dbyte=Dbyte<<1;       
        delay_us(10);        
        gpio_Setstate(SCLK,1); 
        delay_us(10);      
		gpio_Setstate(SCLK,0);
        delay_us(10);
	}   
}  
/************************************
(ϵͳ�Զ����ã��û�����Ҫ�鿴)
������:LCD12864_Write
������ ��lcdд�����ݻ�����
���룺 cmd: ����CMD(����)��DATA(����),
	   data: Ҫ��������ݻ����� 
����� ��
������ LCD12864_Write(CMD,0x01);//����
***********************************/
void LCD12864_Write(uint8_t cmd,uint8_t data)
{
	gpio_Setstate(CS,1);
	if(!cmd)
		LCD12864_WriteByte(0xF8);
	else
		LCD12864_WriteByte(0xFA);
	delay_us(50);
	LCD12864_WriteByte(data&0xF0);
	delay_us(50);
	LCD12864_WriteByte(data<<4);
	delay_us(50);
	
	gpio_Setstate(CS,0);
	delay_us(80);
}
/************************************
������:LCD12864_PhotoShow
������ ��ʾ��Ƭ
���룺 *bmp ��Ƭ��ַ
����� ��
������ LCD12864_PhotoShow(bmp1);
***********************************/
void LCD12864_PhotoShow(uint8_t *bmp)
{
	uint8_t i,j;
	LCD12864_Write(CMD,0x34);
	for(i=0;i<32;i++)
	{
		LCD12864_Write(CMD,0x80+i);
		LCD12864_Write(CMD,0x80);
		for(j=0;j<16;j++)
		{
			LCD12864_Write(DATA,*bmp++);
		}
		delay_us(200);
	}
	for(i=0;i<32;i++)
	{
		LCD12864_Write(CMD,0x80+i);
		LCD12864_Write(CMD,0x88);
		for(j=0;j<16;j++)
			LCD12864_Write(DATA,*bmp++);
	delay_us(200);
	}
	LCD12864_Write(CMD,0x36);
}
/************************************
������:LCD12864_Cls
������ ����
���룺 ��
����� ��
������ LCD12864_Cls();
***********************************/
void LCD12864_Cls()
{
	LCD12864_Write(CMD,0x01);
	delay_ms(5);
}
/************************************
������:LCD12864_Config
������ �����α�״̬��λ�Ʒ���
���룺 Dir: ����LCD12864_Dir_Right(����λ��)
	   	    ����LCD12864_Dir_Left (����λ��)
	   Cur: LCD12864_Cur_ENA (��ʾ�α�)
		    LCD12864_Cur_ENAF(��ʾ�α����α���˸)
		    LCD12864_Cur_Dis (����ʾ�α�)	   
����� ��
������ LCD12864_WriteByte(LCD1602_Dir_Right,LCD1602_Cur_ENAF);//�α���ʾ����˸������λ��
***********************************/
void LCD12864_Config(uint8_t Dir,uint8_t Cur)
{
	LCD12864_Write(CMD,Dir);
	LCD12864_Write(CMD,Cur);
}
/************************************
������:LCD12864_Reverse
������ ����
���룺 line Ҫ���׵���
����� ��
������ LCD12864_Reverse(0);//���׵�0��
***********************************/
void LCD12864_Reverse(uint8_t line)
{
	LCD12864_Write(CMD,0x40&line);
}

