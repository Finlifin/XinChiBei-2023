#include "lcd.h"

void Delay_Ms(unsigned char ms) {
  unsigned int count;
  for (count = 0; count < ms * 114; count++)
    ;
}
void LCD_Write_Com(unsigned char mode) {
  Delay_Ms(5);
  RS_CLR;
  RW_CLR;
  EN_SET;
  DataPort = mode;
  __asm;
  nop;
  __endasm;

  EN_CLR;
}

void LCD_Init() {
  LCD_Write_Com(0x38); // 设置显示模式
  Delay_Ms(5);
  LCD_Write_Com(0x38);
  Delay_Ms(5);
  LCD_Write_Com(0x38);
  Delay_Ms(5);
  LCD_Write_Com(0x38);
  Delay_Ms(5);
  LCD_Write_Com(0x38);
  LCD_Write_Com(0x08); // 关闭显示
  LCD_Write_Com(0x01); // 显示清屏
  LCD_Write_Com(0x06); // 设置光标位置
  Delay_Ms(5);
  LCD_Write_Com(0x0c); // 显示光标
}

void LCD_Write_Data(unsigned char data) {
  RS_SET;
  RW_CLR;
  EN_SET;
  DataPort = data;
  __asm
  nop;
  __endasm;
  EN_CLR;
}

void LCD_Clear() {
  LCD_Write_Com(0x01);
}

void LCD_Write_Char(unsigned char x, unsigned char y, unsigned char c) {
  if (y == 0)
    LCD_Write_Com(0x80 + x);
  else
    LCD_Write_Com(0xC0 + x);
  LCD_Write_Data(c);
}

void LCD_Write_String(unsigned char x, unsigned char y, unsigned char *s) {
  if (y == 0)
    LCD_Write_Com(0x80 + x);
  else
    LCD_Write_Com(0xC0 + x);
  while (*s) {
    LCD_Write_Data(*s);
    s++;
  }
}
