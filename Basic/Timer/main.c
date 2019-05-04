#include <mcs51/8051.h>

unsigned char count = 0;

void setup()
{
  // set timer 0 mode 1
  TMOD = 0x01;
  TH0 = 0x4C;
  TL0 = 0x00;

  // start timer 0
  TR0 = 1;
  // enable timer 0 interrupt
  ET0 = 1;
  // enable all interrupt
  EA = 1;
}

void loop()
{
  if(count%20 == 0)
  {
    P0_0 = !P0_0;
    count = 0;
  }
}

void main()
{
  setup();
  while(1) loop();
}

void timer0() __interrupt 1
{
  count++;
}