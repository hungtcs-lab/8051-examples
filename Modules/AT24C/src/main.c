#include <stdio.h>
#include <mcs51/8051.h>
#include "delay.h"
#include "at24c.h"
#include "serial.h"

int putchar(int c)
{
	while(!(SCON & 0x02));
	SCON &= ~0x02;
	SBUF = (char)c;
  return c;
}

void main()
{
  AT24C at24c;
  at24c.page_size = AT24C_PAGE_SIZE_8;
  at24c.device_address = 0xA0;

  serial_init();

  while(1)
  {
    uint8_t word;
    uint8_t send[AT24C_PAGE_SIZE_8] = { 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07 };
    uint8_t received[AT24C_PAGE_SIZE_8] = { 0 };

    at24c_write_word(&at24c, 0x00, 0x88);
    delay_ms(5);
    at24c_read_word(&at24c, 0x00, &word);
    printf("data of address 0x00 is 0x%x\n", word);

    at24c_write_page(&at24c, 1, send);
    at24c_read_page(&at24c, 1, received);

    for(word=0; word<8; word++)
    {
      printf("data of page 1 at %d is 0x%02x\n", word, received[word]);
    }
    delay_ms(3000);
  }
}
