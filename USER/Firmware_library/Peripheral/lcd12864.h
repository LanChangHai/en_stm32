#ifndef __12864_H
#define __12864_H
#include "stm32f10x.h"

#define CMD  0
#define DATA 1

#define LCD12864_Dir_Right 0x14
#define LCD12864_Dir_Left  0x10
#define LCD12864_Cur_ENA   0x0E
#define LCD12864_Cur_ENAF  0x0F
#define LCD12864_Cur_Dis   0x0C

void LCD12864_Init(void);
void LCD12864_Write(uint8_t cmd,uint8_t data);
void LCD12864_PhotoShow(unsigned char *bmp);
void LCD12864_WriteByte(uint8_t Dbyte);
void LCD12864_WriteString(char data[]);
void LCD12864_SetCur(uint8_t row,uint8_t col);
void LCD12864_Cls(void);
void LCD12864_Config(uint8_t Dir,uint8_t Cur);
void LCD12864_WriteChar(uint8_t data);
void LCD12864_Reverse(uint8_t line);

#endif

