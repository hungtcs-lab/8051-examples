#include <mcs51/8052.h>

unsigned char direction = 1;
unsigned short count = 0;
unsigned short count2 = 0;

void main()
{
  TMOD = 0x01;
  TH0 = 0xFE;
  TL0 = 0x0B;

  // 总中断
  EA = 1;
  // 定时器0中断
  ET0 = 1;
  // 打开定时器0
  TR0 = 1;

  P0_0 = 1;

  while(1);
}

void timer0() __interrupt 1 {
  TH0 = 0xFE;
  TL0 = 0x0B;
  count++;
  count2++;
  if(count2%1000 == 0) {
    direction++;
    if(direction > 4) {
      direction = 1;
    }
  }
  if(count == direction) {
    P0_0 = 0;
  }
  if(count == 40) {
    count = 0;
    P0_0 = 1;
  }
}
