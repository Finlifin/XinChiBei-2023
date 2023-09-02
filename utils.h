#include "config.h"

#define NOP                                                                    \
  __asm;                                                                       \
  nop;                                                                         \
  __endasm

void delay(unsigned char ms);
void Bee(unsigned char ms);

void Enable_Left();
void Enable_Right();
void Disable_Left();
void Disable_Right();

inline void Forward();
inline void Backward();

void Left_Rotate();
void Right_Rotate();
void Left_Rotate_Fast();
void Right_Rotate_Fast();

void Show_Float (unsigned char *buf, float num);

inline void Stop();
