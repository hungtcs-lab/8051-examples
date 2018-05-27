#include "delay.h"

void delay(unsigned int t)
{
  unsigned int i;
  unsigned char j;
  for(i=0; i<t; i++)
  {
    for(j=0;j<200;j++);
    for(j=0;j<102;j++);
  }
}
