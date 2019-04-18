#include "spi.h"

/**
 * @brief 进行一次SPI传输
 *
 * @param data
 * @return uint8_t
 */
uint8_t spi_transmit(uint8_t data)
{
  uint8_t i;
  for(i=0; i<8; i++)
  {
    SPI_MOSI = data & 0x80;
    data <<= 1;
    SPI_SCK = 1;
    data |= SPI_MISO;
    SPI_SCK = 0;
  }
  return data;
}
