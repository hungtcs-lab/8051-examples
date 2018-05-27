#include <mcs51/8051.h>
#include <stdio.h>
#define __nop() __asm nop __endasm

#define TRIGGER P0_0
#define ECHO    P0_1

void delay()
{
  unsigned long int i;
  for(i = 0; i < 10000; i++);
}

int putchar(int c)
{
	while(!(SCON & 0x02));
	SCON &= ~0x02;
	SBUF = c;
	return (c);
}

void trigger()
{
  TRIGGER = 0;
  TRIGGER = 1;
  __nop(); __nop(); __nop(); __nop();
  __nop(); __nop(); __nop(); __nop();
  __nop(); __nop(); __nop(); __nop();
  __nop(); __nop(); __nop(); __nop();
  TRIGGER = 0;
}

void calc()
{
  unsigned int duration, distance;
  duration = TH0*256 + TL0;
  duration *= 12/11.0592;
  // 340m/s = 340mm/ms = 0.340mm/us 0.034cm/us 
  distance = duration * 0.017;
  printf("distance: %dcm\n", distance);
  TH0 = 0;
  TL0 = 0;
}

void setup()
{
  // configure serial for 9600 baud, 8 data bits, 1 stop bit.
	TMOD = 0x21;
	SCON = 0x40;
	// TH1 = 256 - 11.0592 * 1000 * 1000 / 12 / 32 / 9600;
  TH1 = 0xFD;
  // start the timer1
	TCON |= 0x40;
  // tell putchar() the serial is ready to send
	SCON |= 0x02;
  
  // enable timer 0 interrupt
  TH0 = 0;
  TL0 = 0;
  ET0 = 1;
  EA = 1;
}

void loop()
{
  trigger();
  while(!ECHO);
  TR0 = 1;
  while(ECHO);
  TR0 = 0;
  calc();
  delay();
}

void main(void)
{
	setup();
  while(1) loop();
}
