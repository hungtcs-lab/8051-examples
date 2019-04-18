#include "delay.h"
#include "stdio.h"
#include "serial.h"
#include <mcs51/8051.h>

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

  while(1)
  {
    delay_ms(3000);
  }
}
