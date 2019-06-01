#include <stdio.h>
#include <mcs51/8051.h>
#include "delay.h"
#include "serial.h"
#include "tcs34725.h"

int putchar(int c)
{
	while(!(SCON & 0x02));
	SCON &= ~0x02;
	SBUF = (char)c;
  return c;
}

void main()
{
  float r;
  float g;
  float b;
  TCS34725 tcs34725;

  tcs34725.gain = TCS34725_GAIN_1X;
  tcs34725.integration_time = TCS34725_INTEGRATION_TIME_700MS;

  serial_init();
  tcs34725_led_on();
  tcs34725_init(&tcs34725);
  delay_ms(3);

  while(1)
  {
    uint8_t code;
    code = tcs34725_get_rgb(&tcs34725, &r, &g, &b);
    if(code)
    {
      printf("get rgb failed, code is %d\n", code);
    }
    else {
      printf("rgb(%d, %d, %d)\n", (int)r, (int)g, (int)b);
    }
  }
}
