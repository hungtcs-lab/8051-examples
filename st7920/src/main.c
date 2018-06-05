#include <mcs51/8051.h>
#include <string.h>
#include "delay.h"
#include "st7920.h"
#include "serial.h"

// 你好世界！
unsigned char __code content_1[] = "hello world!";
unsigned char __code content_2[] = { 0xC4, 0xE3, 0xBA, 0xC3, 0xCA, 0xC0, 0xBD, 0xE7, 0xA3, 0xA1, ' ', ' ', '\0' };

int putchar(int c)
{
  while(!(SCON & 0x02));
  SCON &= ~0x02;
  SBUF = c;
  return (c);
}

void setup()
{
  unsigned char i, j;
  serial_init();
  st7920_parallel_8bit_init();

  // // 上半屏
  for(j=0; j<32; j++)
  {
    for(i=0; i<8; i++)
    {
      st7920_parallel_8bit_write(0x34, ST7920_COMMAND);
      st7920_parallel_8bit_write(0x80 + j, ST7920_COMMAND);
      st7920_parallel_8bit_write(0x80 + i, ST7920_COMMAND);
      st7920_parallel_8bit_write(0x30, ST7920_COMMAND);
      st7920_parallel_8bit_write(0x00, ST7920_DATA);
      st7920_parallel_8bit_write(0x00, ST7920_DATA);
    }
  }
  st7920_parallel_8bit_write(0x36, ST7920_COMMAND);

  st7920_parallel_8bit_draw_point(3, 3);
}

void loop()
{

}

void main(void)
{
  setup();
  while(1) loop();
}
