#include <mcs51/8051.h>
#include "delay.h"

#ifndef __LCD1602_H__
#define __LCD1602_H__


#define __nop() __asm nop __endasm

#define LCD1602_DATA    1
#define LCD1602_COMMAND 0

#define RS        P1_0
#define RW        P1_1
#define EN        P1_2
#define DATA_PORT P0

__bit lcd1602_status();
void lcd1602_write(unsigned char data, __bit type);
void lcd1602_clear();
void lcd1602_init();

#endif
