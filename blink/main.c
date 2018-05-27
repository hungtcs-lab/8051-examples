#include <mcs51/8051.h>

void delay(unsigned int t)
{
  while(t--);
}

void main()
{
  __bit status = 0;
  while(1)
  {
    P0_0 = status;
    status = !status;
    delay(1000);
  }
}
