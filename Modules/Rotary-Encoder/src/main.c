#include <stdio.h>
#include <mcs51/8051.h>
#include "delay.h"
#include "config.h"
#include "serial.h"

int putchar(int c)
{
	while(!(SCON & 0x02));
	SCON &= ~0x02;
	SBUF = (char)c;
  return c;
}

void main()
{
  uint8_t dt;
  uint8_t sw;
  uint8_t clk;

  serial_init();

  ROTARY_ENCODER_CLK = 1;
  ROTARY_ENCODER_DATA = 1;
  ROTARY_ENCODER_SWITCH = 1;

  dt = ROTARY_ENCODER_DATA;
  sw = ROTARY_ENCODER_SWITCH;
  clk = ROTARY_ENCODER_CLK;

  while(1)
  {
    if(sw != ROTARY_ENCODER_SWITCH) {
      printf("sw: %d\n", sw);
      sw = ROTARY_ENCODER_SWITCH;
    }
    if(clk != ROTARY_ENCODER_CLK || dt != ROTARY_ENCODER_DATA) {
      printf("clk: %d\n", ROTARY_ENCODER_CLK);
      printf("dt: %d\n", ROTARY_ENCODER_DATA);
      printf("\n");
      dt = ROTARY_ENCODER_DATA;
      clk = ROTARY_ENCODER_CLK;
    }
  }
}
