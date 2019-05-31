#include <stdio.h>
#include <mcs51/8051.h>
#include "delay.h"
#include "serial.h"
#include "tm1637.h"

const uint8_t __code TUBE_TAB[] = {
  0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f, 0x6f,
};

int putchar(int c)
{
	while(!(SCON & 0x02));
	SCON &= ~0x02;
	SBUF = (char)c;
  return c;
}

void main()
{
  uint8_t i = 0;
  serial_init();
  tm1637_clear_display();

  while(1)
  {
    uint8_t v = i%8;
    switch(v)
    {
      case 0:
      {
        tm1637_set_brightness(TM1637_BRIGHTNESS_LEVEL_1);
        break;
      }
      case 1:
      {
        tm1637_set_brightness(TM1637_BRIGHTNESS_LEVEL_2);
        break;
      }
      case 2:
      {
        tm1637_set_brightness(TM1637_BRIGHTNESS_LEVEL_3);
        break;
      }
      case 3:
      {
        tm1637_set_brightness(TM1637_BRIGHTNESS_LEVEL_4);
        break;
      }
      case 4:
      {
        tm1637_set_brightness(TM1637_BRIGHTNESS_LEVEL_5);
        break;
      }
      case 5:
      {
        tm1637_set_brightness(TM1637_BRIGHTNESS_LEVEL_6);
        break;
      }
      case 6:
      {
        tm1637_set_brightness(TM1637_BRIGHTNESS_LEVEL_7);
        break;
      }
      case 7:
      {
        tm1637_set_brightness(TM1637_BRIGHTNESS_LEVEL_8);
        break;
      }
      default:
      {
        break;
      }
    }
    tm1637_display_bit(0, TUBE_TAB[v]);
    tm1637_display_bit(1, TUBE_TAB[v]);
    tm1637_display_bit(2, TUBE_TAB[v]);
    tm1637_display_bit(3, TUBE_TAB[v]);
    delay_ms(1000);
    i++;
  }
}
