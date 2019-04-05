#ifndef __DELAY_H__
#define __DELAY_H__

#include <mcs51/8051.h>
#include <stdint.h>

#define CRYSTAL_FREQUENCY   11.0592
#define FS                  (1 / (CRYSTAL_FREQUENCY / 12))

void delay_ms(uint16_t t);

#endif
