#include <mcs51/8051.h>
#include "stdio.h"
#include "delay.h"
#include "dht22.h"

/**
 * 注意: 当前方法适用的sdcc版本为 3.5.0
 */
void putchar(char c)
{
	while(!(SCON & 0x02));
	SCON &= ~0x02;
	SBUF = c;
}

void uart_init()
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

void main()
{
  DHT22MeasurementResult result;

  uart_init();
  delay_ms(3000);

  while(1)
  {
    printf("start measuring...\n");
    dht22_measuring(&result);
    if(result.state == 0)
    {
      printf("humidity: %d.%d%%\n", (int)result.humidity, (int)((result.humidity - ((int)result.humidity)) * 10));
      printf("temperature: %d.%d`C\n", (int)result.temperature, (int)((result.temperature - ((int)result.temperature)) * 10));
    }
    else
    {
      printf("error: %d\n", result.state);
    }
    printf("\n\n");
    delay_ms(3000);
  }
}
