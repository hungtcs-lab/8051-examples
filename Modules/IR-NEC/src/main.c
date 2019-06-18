#include <stdio.h>
#include <stdint.h>
#include <mcs51/8051.h>
#include "config.h"
#include "serial.h"
#include "ir-nec.h"

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
  ir_nec_init();

  while(1)
  {
    if(ir_nec_available())
    {
      printf("data is 0x%08lX\n", ir_nec_get_code());
    }
  }
}
