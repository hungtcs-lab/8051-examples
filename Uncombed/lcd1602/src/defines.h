#include <mcs51/8051.h>

#ifndef __DEFINES_H__
#define __DEFINES_H__

#define __nop() __asm nop __endasm

// 定义LCD1602引脚
#define LCD1602_RS        P1_0
#define LCD1602_RW        P1_1
#define LCD1602_EN        P1_2
#define LCD1602_DATA_PORT P0

#endif
