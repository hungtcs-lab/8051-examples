#include <mcs51/8051.h>
#include "delay.h"
#include "lcd1602.h"
#include "hc-sr04.h"

unsigned char template[] = "distance: 000cm ";
unsigned char overstep[] = "overstep!       ";

void setup()
{
  lcd1602_init();
  lcd1602_clear();
}

void loop()
{
  unsigned char i;
  unsigned int distance;
  distance = (int)hc_sr04_get_distance();

  lcd1602_write(0x80, LCD1602_COMMAND);
  if(distance > 450)
  {
    for(i=0; i<16; i++)
    {
      lcd1602_write(overstep[i], LCD1602_DATA);
    }
  }
  else
  {
    template[10] = (distance / 100) + 0x30;
    template[11] = (distance % 100 / 10) + 0x30;
    template[12] = (distance % 100 % 10) + 0x30;
    for(i=0; i<16; i++)
    {
      lcd1602_write(template[i], LCD1602_DATA);
    }
  }
  delay(300);
}

void main(void)
{
  setup();
  while(1) loop();
}
