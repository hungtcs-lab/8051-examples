#include <math.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <mcs51/8051.h>
#include "delay.h"
#include "serial.h"
#include "ds18b20.h"

int putchar(int c)
{
	while(!(SCON & 0x02));
	SCON &= ~0x02;
	SBUF = (char)c;
  return c;
}

void main(void)
{
  uint8_t i;
  DS18B20_ROM rom;
  float temperature;

  serial_init();

  if(!ds18b20_read_rom(&rom))
  {
    printf("crc: %x\n", rom.crc);
    printf("family code: %x\n", rom.family_code);
    for(i=0; i<6; i++)
    {
      printf("%x, ", rom.serial_number[i]);
    }
    printf("\n");
  }
  else
  {
    printf("read rom error!\n");
  }

  while(1)
  {
    if(ds18b20_measuring(&temperature, DS18B20_RESOLUTION_12_BIT))
    {
      printf("temperature measuring error!\n");
      continue;
    }
    printf("temperature: %d.%d`C\n", (int)temperature, (int)((fabsf(temperature) - abs((int)temperature)) * 10000));
    delay_ms(1000);
  }
}
