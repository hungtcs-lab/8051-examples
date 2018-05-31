#include <mcs51/8051.h>

#ifndef __DEFINES_H__
#define __DEFINES_H__

#define __nop() __asm nop __endasm

// 数据指令选择
#define ST7920_RS        P1_0
// 读写模式选择
#define ST7920_RW        P1_1
// 允许信号
#define ST7920_EN        P1_2
// 数据
#define ST7920_DATA_PORT P0

// 片选
#define ST7920_CS        P0_0
// 数据
#define ST7920_SID       P0_1
// 时钟
#define ST7920_SCK       P0_2

#endif
