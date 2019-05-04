#include <stdio.h>
#include <stdint.h>
#include <mcs51/8051.h>
#include "iic.h"
#include "delay.h"
#include "config.h"
#include "serial.h"
#include "pcf8563.h"

int putchar(int c)
{
	while(!(SCON & 0x02));
	SCON &= ~0x02;
	SBUF = (char)c;
  return c;
}

void io_init()
{
  IIC_SCL = 1;
  IIC_SDA = 1;
}

void main(void)
{
  PCF8563_DATETIME datetime;
  io_init();
  serial_init();

  datetime.seconds = 0;
  datetime.minutes = 0;
  datetime.hours = 0;
  datetime.days = 1;
  datetime.weekdays = 1;
  datetime.months = 1;
  datetime.years = 19;

  pcf8563_set_datetime(PCF8563_DEVICE_ADDRESS, &datetime);

  while(1)
  {
    pcf8563_get_datetime(PCF8563_DEVICE_ADDRESS, &datetime);
    printf("%02d/%02d/%02d %02d:%02d:%02d Wk.%d\n", datetime.years, datetime.months, datetime.days, datetime.hours, datetime.minutes, datetime.seconds, datetime.weekdays);
    delay_ms(500);
  }
}
