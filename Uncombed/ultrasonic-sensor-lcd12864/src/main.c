#include <stdio.h>
#include "delay.h"
#include "st7920.h"
#include "hc-sr04.h"

// 距离是：
const char __code str_1[] = { 0xBE, 0xE0, 0xC0, 0xEB, 0xCA, 0xC7, '\0' };
// 厘米
const char __code str_2[] = { 0xC0, 0xE5, 0xC3, 0xD7, '\0' };
// 超出范围
const char __code str_3[] = { 0xB3, 0xAC, 0xB3, 0xF6, 0xB7, 0xB6, 0xCE, 0xA7, '\0' };

void main()
{
  int distance = 12;

  char display_content[20];

  st7920_parallel_8bit_init();
  while(1)
  {
    distance = hc_sr04_get_distance();
    if(distance <= 400)
    {
      sprintf(display_content, "%3d", distance);
      st7920_parallel_8bit_print(0, 1, str_1);
      st7920_parallel_8bit_print(3, 1, display_content);
      st7920_parallel_8bit_print(5, 1, str_2);
    }
    else
    {
      st7920_parallel_8bit_clear();
      st7920_parallel_8bit_print(0, 1, str_3);
    }
    delay(200);
  }
}
