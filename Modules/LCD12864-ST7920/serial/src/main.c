#include <mcs51/8051.h>
#include "st7920.h"

// 你好世界！
unsigned char __code content_1[] = "hello world!";
unsigned char __code content_2[] = { 0xC4, 0xE3, 0xBA, 0xC3, 0xCA, 0xC0, 0xBD, 0xE7, 0xA3, 0xA1, '\0' };

void setup()
{
  st7920_parallel_8bit_init();
  st7920_parallel_8bit_print(0, 1, content_1);
  st7920_parallel_8bit_print(0, 2, content_2);
  st7920_parallel_8bit_print(0, 3, "Hello LCD12864!");
}

void loop()
{

}

void main(void)
{
  setup();
  while(1) loop();
}
