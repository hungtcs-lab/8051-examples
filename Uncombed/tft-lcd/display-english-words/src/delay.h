#ifndef __DELAY_H__
#define __DELAY_H__

void delay(unsigned int time)
{
  while(time--) {
    __asm nop __endasm;
  }
}

#endif