#include "bt.h"
#include "config.h"
#include "interrupt.h"
#include "lcd.h"
#include "sonic.h"
#include "utils.h"

#include <stdio.h>

unsigned char state = 0xff;
unsigned char num[16];
unsigned char flag;
char rec;
unsigned int INTNUM;

// for PWM
unsigned char PWM;
unsigned char DIRECTION;

// for Sonic
unsigned int time = 0;
float distance = 0;
unsigned char flag_sonic = 0;

void Seek() {
  // 1->left, 2->right, 3->stop, 4-> ahead
  if (Seek_To_Left_ == 0 && Seek_To_Right_ == 1) {
    flag = 2;
  } else if (Seek_To_Left_ == 1 && Seek_To_Right_ == 0) {
    flag = 1;
  } else if (Seek_To_Right_ == 0 && Seek_To_Left_ == 0) {
    flag = 3;
  } else {
    flag = 4;
  }

  switch (flag) {
  case 1:
    PWM = 50;
    Left_Rotate();
    DIRECTION = 0;
    break;
  case 2:
    PWM = 50;
    Right_Rotate();
    DIRECTION = 1;
    break;
  case 3:
    PWM = 40;
    if (DIRECTION == 1) {
      Right_Rotate_Fast();
    } else {
      Left_Rotate_Fast();
    }
    break;
  default:
    PWM = 90;
    Forward();
    break;
  }
}

void Follow() {
  distance = Explore();
  if (distance < 13.0) {
    PWM = 30;
    Backward();
  } else if (distance > 15.0 && distance < 40.0) {
    PWM = 30;
    Forward();
  } else {
    Stop();
  }
}

void Measure_Distance() {
  distance = Explore();

  LCD_Init();
  LCD_Clear();
  num[0] = (unsigned int)(distance / 100) % 10 + 48;
  num[1] = (unsigned int)(distance / 10) % 10 + 48;
  num[2] = (unsigned int)distance % 10 + 48;
  num[3] = '.';
  num[4] = (unsigned int)(distance * 10) % 10 + 48;
  num[5] = 'c';
  num[6] = 'm';
  LCD_Write_String(0, 0, num);
}

void Avoid() {
  if (Avoid_From_Left_ == 0 && Avoid_From_Right_ == 1) {
    PWM = 40;
    Right_Rotate_Fast();
  } else if (Avoid_From_Left_ == 1 && Avoid_From_Right_ == 0) {
    PWM = 40;
    Left_Rotate_Fast();
  } else if (Avoid_From_Right_ == 0 && Avoid_From_Left_ == 0) {
    PWM = 40;
    Backward();
  } else {
    Forward();
  }
}

void When_Recieved() __interrupt(4) {
  rec = SBUF;
  SBUF = rec;
  while (!TI)
    ;
  TI = 0;
  RI = 0;

  switch (rec) {
  case 'a':
    state = APPROACHING;
    break;
  case 'r':
    state = 'r';
    break;
  case 'l':
    state = 'l';
    break;
  case 'b':
    state = 'b';
    break;
  case 'f':
    state = FOLLOWING;
    break;
  case 'u':
    state = 'u';
    break;
  case 'g':
    state = 'g';
    break;
  case 't':
    state = 't';
    break;
  default:
    PWM = 100;
    state = READY;
    break;
  }
}

void PWM_Interrupt() __interrupt(1) {
  TR0 = 0;
  TH0 = (0xFFFF - 6) / 256;
  TL0 = (0xFFFF - 6) % 256; // 11.0592M晶振下占空比最大比值是256,输出100HZ
  INTNUM++;
  if (INTNUM > 100) {
    INTNUM = 0;
  }

  TR0 = 1;
}

void main() {
  PWM_Init();
  Bluetooth_Init();
  PWM = 80;
  Sonic_Init();
  while (1) {
    if (INTNUM < PWM) {
      switch (state) {
      case READY:
        Stop();
        break;
      case APPROACHING:
        Seek();
        break;
      case 'u':
        Forward();
        break;
      case 'r':
        Right_Rotate_Fast();
        break;
      case 'l':
        Left_Rotate_Fast();
        break;
      case 'b':
        Backward();
        break;
      case 'g':
        Avoid();
        break;
      case FOLLOWING:
        Follow();
        break;
      case 't':
        Measure_Distance();
        break;
      default:
        PWM = 80;
        break;
      }
    } else {
      Stop();
    }
  }
}
