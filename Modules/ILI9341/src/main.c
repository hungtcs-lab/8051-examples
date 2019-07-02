#include <stdio.h>
#include <stdint.h>
#include <mcs51/8051.h>
#include "config.h"
#include "serial.h"
#include "ili9341.h"

int putchar(int c)
{
	while(!(SCON & 0x02));
	SCON &= ~0x02;
	SBUF = (char)c;
  return c;
}

void main()
{
  serial_init();
  ili9341_init();

  while(1)
  {
    ili9341_full(0XF81F);
    delay_ms(500);
  }
}
