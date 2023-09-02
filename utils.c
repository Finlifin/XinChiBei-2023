#include "utils.h"

void delay(unsigned char ms) {
  unsigned char i, j;
  for (i = 0; i < ms; i++) {
    for (j = 0; j < 111; j++)
      ;
  }
}

void Bee(unsigned char ms) {
  Bee_ = 0;
  delay(ms);
  Bee_ = 1;
}

void Enable_Left() { Left_Enable_ = 1; }

void Enable_Right() { Right_Enable_ = 1; }

void Disable_Left() { Left_Enable_ = 0; }

void Disale_Right() { Right_Enable_ = 0; }

inline void Forward() {
  Right_Enable_ = 1;
  Left_Enable_ = 1;
  Left_Backward_ = 1;
  Right_Backward_ = 1;
  Left_Forward_ = 0;
  Right_Forward_ = 0;
}

inline void Backward() {
  Right_Enable_ = 1;
  Left_Enable_ = 1;
  Left_Forward_ = 1;
  Right_Forward_ = 1;
  Right_Backward_ = 0;
  Left_Backward_ = 0;
}

inline void Stop() {
  Left_Enable_ = 0;
  Right_Enable_ = 0;
}

void Right_Rotate() {
  Left_Enable_ = 1;
  Right_Enable_ = 0;
  Left_Forward_ = 0;
  Left_Backward_ = 1;
}

void Right_Rotate_Fast() {
  Right_Enable_ = 1;
  Left_Enable_ = 1;
  Left_Forward_ = 0;
  Left_Backward_ = 1;
  Right_Backward_ = 0;
  Right_Forward_ = 1;
}

void Left_Rotate() {
  Left_Enable_ = 0;
  Right_Enable_ = 1;
  Right_Forward_ = 0;
  Right_Backward_ = 1;
}

void Left_Rotate_Fast() {
  Left_Enable_ = 1;
  Right_Enable_ = 1;
  Left_Forward_ = 1;
  Left_Backward_ = 0;
  Right_Backward_ = 1;
  Right_Forward_ = 0;
}

void Show_Float(unsigned char *buf, float num)
{
    int integerPart = (int)num;               
    float fractionalPart = num - integerPart;

    // 将整数部分转换为字符串，并拼接到buf
    int digitCount = 0;
    do
    {
        buf[digitCount++] = '0' + integerPart % 10;
        integerPart /= 10;
    } while (integerPart > 0);

    // 反转整数部分的字符串
    for (int i = 0; i < digitCount / 2; i++)
    {
        unsigned char temp = buf[i];
        buf[i] = buf[digitCount - i - 1];
        buf[digitCount - i - 1] = temp;
    }

   
    buf[digitCount++] = '.';

   
    for (int i = 0; i < 6; i++)
    {
        fractionalPart *= 10;
        buf[digitCount++] = '0' + ((int)fractionalPart % 10);
    }

  
    buf[digitCount] = '\0';
}