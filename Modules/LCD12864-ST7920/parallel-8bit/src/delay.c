#include <stdint.h>
#include "delay.h"

void delay(unsigned int t)
{
  uint32_t i, j;
  for(i=0; i<t; i++)
  {
    for(j=0;j<103;j++);
  }
}
