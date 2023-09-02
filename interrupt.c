#include "interrupt.h"

void PWM_Init() {
  TH0 = (0xFFFF - 6) / 256;
  TL0 = (0xFFFF - 6) % 256; // 11.0592M晶振下占空比最大比值是256,输出100HZ
  TMOD = 0x01;              // 8位自动重装模块
  EA = 1;                   // 总中断允许
  ET0 = 1;                  // 允许定时器0中断
  TR0 = 1;                  // 启动定时器0
}
