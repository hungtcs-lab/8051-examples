#include <stdio.h>
#include <stdint.h>
#include <mcs51/8051.h>
#include "delay.h"
#include "serial.h"
#include "ds1302.h"

int putchar(int c)
{
	while(!(SCON & 0x02));
	SCON &= ~0x02;
	SBUF = (char)c;
  return c;
}

void main(void)
{
  DS1302_DATETIME datetime;

  serial_init();

  datetime.second = 0;
  datetime.minute = 0;
  datetime.hour = 0;
  datetime.date = 1;
  datetime.month = 1;
  datetime.day = 2;
  datetime.year = 19;
  ds1302_set_datetime(&datetime);
  ds1302_trickle_charger_disable();
  ds1302_start();

  while(1)
  {
    ds1302_get_datetime(&datetime);
    printf("20%02d/%02d/%02d %02d:%02d:%02d - Wk.%d\n", datetime.year, datetime.month, datetime.date, datetime.hour, datetime.minute, datetime.second, datetime.day);
    delay_ms(500);
  }
}
