#include "oled.h"
#include "stdio.h"
#include "delay.h"
#include "serial.h"
#include "ds18b20.h"
#include <mcs51/8051.h>

const char celsius_symbol[] = { 95 + 32, 'C', '\0' };

int putchar(int c)
{
	while(!(SCON & 0x02));
	SCON &= ~0x02;
	SBUF = (char)c;
  return c;
}

void ds18b20_read_rom(uint8_t *rom)
{
  uint8_t i;
  ds18b20_init();
  ds18b20_write_byte(READ_ROM);
  for(i=0; i<8; i++)
  {
    *(rom + i) = ds18b20_read_byte();
  }
}

void main(void)
{
  uint8_t i;
  int temperature;

  oled_init();
  serial_init();

  ds18b20_get_temperature();

  while(1)
  {
    temperature = ds18b20_get_temperature();

    oled_clear();
    i = 0;
    oled_put_chars_8x16(0, 0, "Temperature:");

    oled_put_char_8x16(i++, 1, (temperature / 10) + 48);
    oled_put_char_8x16(i++, 1, (((int)temperature) % 10) + 48);
    oled_put_char_8x16(i++, 1, '.');
    oled_put_char_8x16(i++, 1, ((int)((temperature - ((int)temperature)) * 10)) + 48);
    oled_put_chars_8x16(i, 1, celsius_symbol);
    delay_ms(3000);
  }
}
