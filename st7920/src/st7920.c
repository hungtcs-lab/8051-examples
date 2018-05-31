#include "st7920.h"
#include "defines.h"

void st7920_serial_write(unsigned char data)
{
  unsigned char i;
  for(i=0; i<8; i++)
  {
    ST7920_SCK = 0;
    ST7920_SID = (data << i) & 0x80;
    ST7920_SCK = 1;
  }
}
void st7920_serial_write_data(unsigned char data)
{
  // 0b 1 1 1 1 1 RW RS 0
  // 0b 1 1 1 1 1 0  1  0
  st7920_serial_write(0xFA);
  st7920_serial_write(data & 0xF0);
  st7920_serial_write((data << 4) & 0xF0);
}

void st7920_serial_write_command(unsigned char command)
{
  // 0b 1 1 1 1 1 RW RS 0
  // 0b 1 1 1 1 1 0  0  0
  st7920_serial_write(0xF8);
  st7920_serial_write(data & 0xF0);
  st7920_serial_write((data << 4) & 0xF0);
}

void st7920_parallel_4bit_write(unsigned char data, __bit type)
{
  // pass
}

void st7920_parallel_8bit_write(unsigned char data, __bit type)
{
  ST7920_RS = type;
  ST7920_RW = 0;
  ST7920_EN = 1;
  __nop();
  ST7920_DATA_PORT = data;
  __nop();
  ST7920_EN = 0;
}
