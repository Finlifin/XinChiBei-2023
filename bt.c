#include "bt.h"
#include "utils.h"

/**
 * @brief 串口初始化
 */

void Bluetooth_Init() {
  SCON = 0x50;  // 串行控制寄存器
  PCON |= 0x00; // 电源控制寄存器，里面SMOD位是控制倍频
  TMOD &= 0x0F; // 定时器控制寄存器
  TMOD |= 0x20;
  TL1 = 0xFd; // 设置波特率9600@11.0592MHz
  TH1 = 0xFd;
  ET1 = 0; // 打开定时器1的中断
  TR1 = 1; //  打开定时器1
  EA = 1;  //  总中断
  ES = 1;  //  串行口中断允许位
  PS = 1;  // 中断优先级
           // PT2 = 0; //定时器2中断优先级
}


