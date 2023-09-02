#include "sonic.h"

void Sonic_Init() {
  T2MOD = 0;     // 初始化模式寄存器
  T2CON = 0;     // 初始化控制寄存器
  TL2 = 0x00;    // 设置定时初始值
  TH2 = 0x00;    // 设置定时初始值
  RCAP2L = 0x00; // 设置定时重载值
  RCAP2H = 0x00; // 设置定时重载值
  TR2 = 0;       // 定时器2开始计时
}

void Sonic_Start() {
  TRIGER_ = 1;
  __asm
  NOP
  NOP 
  NOP 
  NOP 
  NOP 
  NOP 
  NOP 
  NOP 
  NOP 
  NOP 
  NOP 
  NOP 
  NOP 
  NOP 
  NOP 
  NOP 
  NOP 
  NOP
  NOP 
  NOP 
  NOP 
  NOP 
  NOP 
  NOP 
  NOP 
  NOP 
  __endasm;
  TRIGER_ = 0;
}

void Count(unsigned int *time, unsigned int *distance, unsigned char *flag) {
  *time = TH2 * 0xff + TL2;
  __asm
  CLR TH2 
  CLR TL2 
  __endasm;
  *distance = ((*time) * 1.7) / 100; // 计算距离， 单位cm

  if (*distance >= 700) {
    *flag = 0;
  }
}

float Explore()
{
    float len;
    TRIGER_ = 0;
    TRIGER_ = 1;
    __asm;
    NOP
    NOP 
    NOP 
    NOP 
    NOP 
    NOP 
    NOP 
    NOP 
    NOP 
    NOP 
    NOP 
    NOP 
    // NOP 
    // NOP 
    // NOP 
    // NOP 
    // NOP 
    // NOP
    // NOP 
    // NOP 
    // NOP 
    // NOP 
    // NOP 
    // NOP 
    // NOP 
    // NOP 
  __endasm;
    TRIGER_ = 0;
    while (!ECHO_)
        ;
    TH2 = 0x00;
    TL2 = 0x00;
    TR2 = 1;
    while (ECHO_)
        ;
    TR2 = 0;
    len = (float)TH2 * 256 + TL2;
    return (len * 0.00034 / 2) * 100;
}