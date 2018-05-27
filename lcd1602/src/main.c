#include <mcs51/8051.h>
#include "delay.h"
#include "lcd1602.h"

__code unsigned char line1[] = "  hello world!  ";
__code unsigned char line2[] = " happy LCD1602! ";

void display()
{
  unsigned char i;
  lcd1602_write(0x80, LCD1602_COMMAND);
  for(i=0; i<16; i++)
  {
    lcd1602_write(line1[i], LCD1602_DATA);
  }

  lcd1602_write(0xC0, LCD1602_COMMAND);
  for(i=0; i<16; i++)
  {
    lcd1602_write(line2[i], LCD1602_DATA);
  }
}

void setup()
{
  lcd1602_init();
  lcd1602_clear();
}

void loop()
{
  lcd1602_clear();
  delay(1000);
  display();
  delay(1000);
}

void main(void)
{
  setup();
  while(1) loop();
}
