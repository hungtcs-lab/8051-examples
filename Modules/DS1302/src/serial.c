#include "serial.h"

void serial_init(void)
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
}
