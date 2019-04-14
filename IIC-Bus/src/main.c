#include "iic.h"
#include "delay.h"
#include "stdio.h"
#include <mcs51/8051.h>

int putchar(int c)
{
	while(!(SCON & 0x02));
	SCON &= ~0x02;
	SBUF = (char)c;
  return c;
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

uint8_t at24c_write()
{
  iic_start();
  iic_send_byte(0xA0);
  if(iic_read_ack() == IIC_NACK)
  {
    return 1;
  }
  iic_send_byte(0x01);
  if(iic_read_ack() == IIC_NACK)
  {
    return 2;
  }
  iic_send_byte(0x88);
  if(iic_read_ack() == IIC_NACK)
  {
    return 3;
  }
  iic_stop();
  delay_ms(5);
  return 0;
}

uint8_t at24c_read(uint8_t *data)
{
  iic_start();
  iic_send_byte(0xA0);
  if(iic_read_ack() == IIC_NACK)
  {
    return 1;
  }
  iic_send_byte(0x01);
  if(iic_read_ack() == IIC_NACK)
  {
    return 2;
  }
  iic_start();
  iic_send_byte(0xA1);
  if(iic_read_ack() == IIC_NACK)
  {
    return 3;
  }
  *data = iic_read_byte();
  iic_nack();
  iic_stop();
  return 0;
}

void main()
{
  uint8_t data;
  uint8_t result;
  uart_init();

  IIC_SCL = 1;
  IIC_SDA = 1;

  while(1)
  {
    data = 0x00;
    result = 0xFF;

    result = at24c_write();
    printf("write result: %d\n", result);

    result = at24c_read(&data);
    printf("read result: %d, value is: %x\n", result, data);

    delay_ms(3000);
  }
}
