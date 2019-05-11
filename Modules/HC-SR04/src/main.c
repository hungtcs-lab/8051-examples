#include <stdio.h>
#include <stdint.h>
#include <mcs51/8051.h>
#include "delay.h"
#include "config.h"
#include "serial.h"
#include "hc-sr04.h"

int putchar(int c)
{
	while(!(SCON & 0x02));
	SCON &= ~0x02;
	SBUF = (char)c;
  return c;
}

void main()
{
  uint16_t distance;

  serial_init();

  while(1)
  {
    if(hc_sr04_get_distance(&distance) == HC_SR04_SUCCESS)
    {
      printf("distance: %dcm\n", distance);
    }
    else
    {
      printf("out of range\n");
    }
    delay_ms(500);
  }
}
