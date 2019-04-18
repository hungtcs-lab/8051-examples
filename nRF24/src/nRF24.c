#include "nRF24.h"

uint8_t nrf24_read_register(uint8_t address, uint8_t *data, uint8_t length)
{
  uint8_t i;
  uint8_t status;
  SPI_CS = 0;
  status = spi_transmit(address);
  for(i=0; i<length; i++)
  {
    *(data + i) = spi_transmit(NOP);
  }
  SPI_CS = 1;
  return status;
}

uint8_t nrf24_write_register(uint8_t address, uint8_t *data, uint8_t length)
{
  uint8_t i;
  uint8_t status;
  SPI_CS = 0;
  status = spi_transmit(address);
  for(i=0; i<length; i++)
  {
    spi_transmit(data[i]);
  }
  SPI_CS = 1;
  return status;
}

// uint8_t nrf24_read_register_l1(uint8_t address, uint8_t *data)
// {
//   uint8_t status;
//   SPI_CS = 0;
//   status = spi_transmit(address);
//   *data = spi_transmit(NOP);
//   SPI_CS = 1;
//   return status;
// }

// uint8_t nrf24_write_register_l1(uint8_t address, uint8_t data)
// {
//   uint8_t status;
//   SPI_CS = 0;
//   status = spi_transmit(address);
//   spi_transmit(data);
//   SPI_CS = 1;
//   return status;
// }
