#ifndef __SPI_H__
#define __SPI_H__

void spi_write(unsigned char data)
{
  unsigned char i;
  for(i=0; i<8; i++)
  {
    SPI_SDA = (data << i) & 0x80;
    SPI_SCK = 0;
    SPI_SCK = 1;
  }
}

#endif