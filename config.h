#include <8051.h>

/*Explainations
RS_ --> 位宽度别名宏
DataPort --> 字节宽度别名宏
Left_Backward --> 函数名
a_simple_string --> 变量名

*/

/*---------------------*\
State Configurations
\*---------------------*/
#define READY 0
#define APPROACHING 1
#define FOLLOWING 2
// #define 
// #define

/*---------------------*\
LCD Configurations
\*---------------------*/
#define RS_ P3_5
#define RW_ P3_6
#define EN_ P3_4

#define RS_CLR RS_ = 0
#define RS_SET RS_ = 1

#define RW_CLR RW_ = 0
#define RW_SET RW_ = 1

#define EN_CLR EN_ = 0
#define EN_SET EN_ = 1

#define DataPort P0

/*---------------------*\
Motor Configurations
\*---------------------*/
#define Left_Backward_ P1_3
#define Left_Forward_ P1_2
#define Left_Enable_ P1_4
#define Right_Enable_ P1_5
#define Right_Forward_ P1_7
#define Right_Backward_ P1_6

/*---------------------*\
Bluetooth Configurations
\*---------------------*/
// #define T2MOD 0xC9
// #define T2CON 0xC8
// #define TL2 0xCC
// #define TH2 0xCD
// #define RCAP2L 0xCA
// #define TCAP2H 0xCB
// #define TR2 0

/*---------------------*\
Timer Configurations
\*---------------------*/
/*
T0 -> PWM
T1 -> UAST
T2  -> SONIC
*/
__sfr __at(0x80) P0;
__sfr __at(0x81) SP;
__sfr __at(0x82) DPL;
__sfr __at(0x83) DPH;
__sfr __at(0x87) PCON;
__sfr __at(0x88) TCON;
__sfr __at(0x89) TMOD;
__sfr __at(0x8A) TL0;
__sfr __at(0x8B) TL1;
__sfr __at(0x8C) TH0;
__sfr __at(0x8D) TH1;
__sfr __at(0x90) P1;
__sfr __at(0x98) SCON;
__sfr __at(0x99) SBUF;
__sfr __at(0xA0) P2;
__sfr __at(0xA8) IE;
__sfr __at(0xB0) P3;
__sfr __at(0xB8) IP;
__sfr __at(0xD0) PSW;
__sfr __at(0xE0) ACC;
__sfr __at(0xF0) B;
__sfr __at(0x8E) AUXR;
__sfr __at(0xC8) T2CON;
__sfr __at(0xC9) T2MOD;
__sfr __at(0xCA) RCAP2L;
__sfr __at(0xCB) RCAP2H;
__sfr __at(0xCC) TL2;
__sfr __at(0xCD) TH2;
__sbit __at(0xCA) TR2;



/*---------------------*\
Sensor Configurations
\*---------------------*/
#define Seek_To_Left_ P2_6
#define Seek_To_Right_ P2_7
#define Avoid_From_Left_ P2_5
#define Avoid_From_Right_ P2_4

/*---------------------*\
Sonic Configurations
\*---------------------*/
#define TRIGER_ P2_1
#define ECHO_ P2_0

/*---------------------*\
Bee Configurations
\*---------------------*/
#define Bee_ P2_3