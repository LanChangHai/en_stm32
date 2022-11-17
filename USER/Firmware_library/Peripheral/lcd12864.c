#include "STM32_head.h"
#include "STM32_gpio.h"
/***********************************
file：lcd12864.c
作者：杨帆
时间：2019/7/20
本代码仅供北华大学嵌入式系统实验室使用
***********************************/
#define RST  A3
#define CS   A4
#define SCLK A5
#define SID  A7
//此处修改使用的引脚

static uint8_t nrow=0,ncol=0;
/************************************
函数名:LCD12864_Init
描述： 屏幕初始化
输入： 无
输出： 无
样例： LCD12864_Init();
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
函数名:LCD12864_WriteChar
描述： 写入单个字符
输入： data要写入的字符
输出： 无
样例： LCD12864_WriteChar('A');//显示A
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
函数名:LCD12864_WriteString
描述： 写入字符串
输入： *data字符串地址
输出： 无
样例： LCD12864_WriteString(":(");//显示:(
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
函数名:LCD12864_SetCur
描述： 设置游标位置
输入： row 行,col 列
输出： 无
样例： LCD12864_SetCur(0,0);//游标设置到第0行第0列
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
(系统自动调用，用户不需要查看)
函数名:LCD12864_WriteByte
描述： 向lcd写入1字节数据
输入： Dbyte要写入的数据
输出： 无
样例： LCD12864_WriteByte(0x04);
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
(系统自动调用，用户不需要查看)
函数名:LCD12864_Write
描述： 向lcd写入数据或命令
输入： cmd: 输入CMD(命令)或DATA(数据),
	   data: 要输入的数据或命令 
输出： 无
样例： LCD12864_Write(CMD,0x01);//清屏
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
函数名:LCD12864_PhotoShow
描述： 显示照片
输入： *bmp 照片地址
输出： 无
样例： LCD12864_PhotoShow(bmp1);
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
函数名:LCD12864_Cls
描述： 清屏
输入： 无
输出： 无
样例： LCD12864_Cls();
***********************************/
void LCD12864_Cls()
{
	LCD12864_Write(CMD,0x01);
	delay_ms(5);
}
/************************************
函数名:LCD12864_Config
描述： 设置游标状态和位移方向
输入： Dir: 输入LCD12864_Dir_Right(向右位移)
	   	    输入LCD12864_Dir_Left (向左位移)
	   Cur: LCD12864_Cur_ENA (显示游标)
		    LCD12864_Cur_ENAF(显示游标且游标闪烁)
		    LCD12864_Cur_Dis (不显示游标)	   
输出： 无
样例： LCD12864_WriteByte(LCD1602_Dir_Right,LCD1602_Cur_ENAF);//游标显示且闪烁，向右位移
***********************************/
void LCD12864_Config(uint8_t Dir,uint8_t Cur)
{
	LCD12864_Write(CMD,Dir);
	LCD12864_Write(CMD,Cur);
}
/************************************
函数名:LCD12864_Reverse
描述： 反白
输入： line 要反白的行
输出： 无
样例： LCD12864_Reverse(0);//反白第0行
***********************************/
void LCD12864_Reverse(uint8_t line)
{
	LCD12864_Write(CMD,0x40&line);
}

