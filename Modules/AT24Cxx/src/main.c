#include "iic.h"
#include "delay.h"
#include "stdio.h"
#include "serial.h"
#include "at24cxx.h"
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
  uint8_t data;
  AT24Cxx at24cxx;
  at24cxx.deviceAddress = 0xA0;

  serial_init();

  IIC_SCL = 1;
  IIC_SDA = 1;

  while(1)
  {
    at24cxx_write_byte(&at24cxx, 0x00, 0x88);
    delay_ms(5);
    at24cxx_read_byte(&at24cxx, 0x00, &data);
    printf("data of address 0x00 is 0x%x\n", data);
    delay_ms(3000);
  }
}
