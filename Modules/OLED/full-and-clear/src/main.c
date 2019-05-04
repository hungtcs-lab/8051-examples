#include <mcs51/8051.h>
#include "delay.h"
#include "oled.h"

void main()
{
  oled_init();
  while(1)
  {
    oled_clear();
    delay_ms(500);
    oled_full();
    delay_ms(500);
  }
}
