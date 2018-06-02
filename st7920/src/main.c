#include <mcs51/8051.h>
#include "delay.h"
#include "st7920.h"
#include <string.h>

// 你好世界！
unsigned char __code content_1[] = "hello world!";
unsigned char __code content_2[] = { 0xC4, 0xE3, 0xBA, 0xC3, 0xCA, 0xC0, 0xBD, 0xE7, 0xA3, 0xA1, ' ', ' ', '\0' };

void setup()
{
  st7920_parallel_8bit_init();
}

void loop()
{
  unsigned char time = 100;
  st7920_parallel_8bit_print(0, 1, content_1);
  delay(time);
  st7920_parallel_8bit_print(0, 2, content_1);
  delay(time);
  st7920_parallel_8bit_print(0, 3, content_1);
  delay(time);
  st7920_parallel_8bit_print(0, 4, content_1);
  delay(time);
  st7920_parallel_8bit_print(0, 1, content_2);
  delay(time);
  st7920_parallel_8bit_print(0, 2, content_2);
  delay(time);
  st7920_parallel_8bit_print(0, 3, content_2);
  delay(time);
  st7920_parallel_8bit_print(0, 4, content_2);
  delay(time);
}

void main(void)
{
  setup();
  while(1) loop();
}
