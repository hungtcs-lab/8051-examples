#ifndef __DELAY_H__
#define __DELAY_H__

#include <stdint.h>
#include <mcs51/8051.h>

#define __nop()  __asm nop __endasm

void delay_ms(uint16_t t);

#endif
