#include <string.h>
#include "st7920.h"
#include "defines.h"
#include "delay.h"

__bit st7920_parallel_8bit_busy_flag()
{
  ST7920_DATA_PORT = 0xFF;
  ST7920_RS = 0;
  ST7920_RW = 1;
  ST7920_EN = 1;
  return ST7920_DATA_PORT & 0x80;
}

void st7920_parallel_8bit_write(unsigned char data, __bit type)
{
  while(!st7920_parallel_8bit_busy_flag());
  ST7920_RS = type;
  ST7920_RW = 0;
  ST7920_EN = 1;
  __nop();
  ST7920_DATA_PORT = data;
  __nop();
  ST7920_EN = 0;
}

unsigned char st7920_parallel_8bit_read(__bit type)
{
  unsigned char data;
  while(!st7920_parallel_8bit_busy_flag());
  ST7920_RS = type;
  ST7920_RW = 1;
  ST7920_EN = 1;
  __nop();
  data = ST7920_DATA_PORT;
  __nop();
  ST7920_EN = 0;
  return data;
}

void st7920_parallel_8bit_clear()
{
  st7920_parallel_8bit_write(0x01, ST7920_COMMAND);
  delay(10);
}

void st7920_parallel_8bit_init()
{
  // 功能设置
  st7920_parallel_8bit_write(0x30, ST7920_COMMAND);
  delay(1);
  st7920_parallel_8bit_write(0x30, ST7920_COMMAND);
  delay(1);
  // 显示开，不显示游标和反白
  st7920_parallel_8bit_write(0x0C, ST7920_COMMAND);
  delay(1);
  // 清屏
  st7920_parallel_8bit_write(0x01, ST7920_COMMAND);
  delay(20);
  st7920_parallel_8bit_write(0x06, ST7920_COMMAND);
}

void st7920_parallel_8bit_print(unsigned char x, unsigned char y, unsigned char * content)
{
  unsigned char i;
  if(y == 1)
  {
    i = 0x80 + x;
  }
  else if(y == 2)
  {
    i = 0x90 + x;
  }
  else if(y == 3)
  {
    i = 0x88 + x;
  }
  else if(y == 4)
  {
    i = 0x98 + x;
  }
  else
  {
    return;
  }
  st7920_parallel_8bit_write(i, ST7920_COMMAND);
  for(i=0; i<strlen(content); i++)
  {
    st7920_parallel_8bit_write(content[i], ST7920_DATA);
  }
}

void st7920_parallel_8bit_clear_rect(unsigned char x, unsigned char y, unsigned char width, unsigned char height)
{
  unsigned char i, j, d1, d2;

  for(j=y; j<y+height; j++)
  {
    for(i=x; i<x+width; i++)
    {
      st7920_parallel_8bit_write(0x30, ST7920_COMMAND);
      st7920_parallel_8bit_write(0x80 + j, ST7920_COMMAND);
      // st7920_parallel_8bit_write(0x80 + i, ST7920_COMMAND);
      st7920_parallel_8bit_read(1);
      d1 = st7920_parallel_8bit_read(1);
      // d2 = st7920_parallel_8bit_read(1);
      d1 |= 0x7F >> i;


      st7920_parallel_8bit_write(0x34, ST7920_COMMAND);
      st7920_parallel_8bit_write(0x80 + j, ST7920_COMMAND);
      st7920_parallel_8bit_write(0x80 + i, ST7920_COMMAND);
      st7920_parallel_8bit_write(0x30, ST7920_COMMAND);

      st7920_parallel_8bit_write(d1, ST7920_DATA);
      st7920_parallel_8bit_write(0xFF, ST7920_DATA);
      // redraw
      st7920_parallel_8bit_write(0x36, ST7920_COMMAND);
    }
  }
}

void st7920_parallel_8bit_draw_point(unsigned char x, unsigned char y)
{
  unsigned int bt, read;
  unsigned char addr_x, addr_y, h_bit, l_bit;
  addr_y = 0x80 + y % 32;
  addr_x = y < 32 ? (0x80 + x / 16) : (0x88 + x / 16);

  bt = 0x80000 >> (x % 16);
  st7920_parallel_8bit_write(0x34, ST7920_COMMAND);
  st7920_parallel_8bit_write(addr_y, ST7920_COMMAND);
  st7920_parallel_8bit_write(addr_x, ST7920_COMMAND);
  st7920_parallel_8bit_read(1);
  read = st7920_parallel_8bit_read(1);
  read << 8;
  read |= st7920_parallel_8bit_read(1);
  bt |= read;
  h_bit = bt >> 8;
  l_bit = bt;

  st7920_parallel_8bit_write(addr_y, ST7920_COMMAND);
  st7920_parallel_8bit_write(addr_x, ST7920_COMMAND);
  st7920_parallel_8bit_write(h_bit, ST7920_DATA);
  st7920_parallel_8bit_write(l_bit, ST7920_DATA);

  st7920_parallel_8bit_write(0x36, ST7920_COMMAND);
}
