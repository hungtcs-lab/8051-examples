#include "delay.h"

void delay(unsigned int t)
{
  unsigned int i, j;
  for(i=0; i<t; i++)
  {
    for(j=200;j>0;j--);
    for(j=102;j>0;j--);
  }
}
