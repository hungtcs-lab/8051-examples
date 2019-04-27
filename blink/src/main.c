#include <mcs51/8051.h>

void delay(unsigned int t)
{
  while(t--);
}

void main()
{
  while(1)
  {
    P1_0 = !P1_0;
    delay(30000);
  }
}
