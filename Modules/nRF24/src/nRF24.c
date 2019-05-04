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

uint8_t nrf24_read_register_byte(uint8_t address, uint8_t *data)
{
  uint8_t status;
  SPI_CS = 0;
  status = spi_transmit(address);
  *data = spi_transmit(NOP);
  SPI_CS = 1;
  return status;
}

uint8_t nrf24_write_register_byte(uint8_t address, uint8_t data)
{
  uint8_t status;
  SPI_CS = 0;
  status = spi_transmit(address);
  spi_transmit(data);
  SPI_CS = 1;
  return status;
}

uint8_t nrf24_device_check(void)
{
  uint8_t i;
  uint8_t input[5];
  uint8_t output[5] = { 0x88, 0x88, 0x88, 0x88, 0x88 };
  nrf24_write_register(W_REGISTER | TX_ADDR, output, TX_ADDR_WIDTH);
  nrf24_read_register(R_REGISTER | TX_ADDR, input, TX_ADDR_WIDTH);
  for(i=0; i<TX_ADDR_WIDTH; i++)
  {
    if(output[i] != input[i])
    {
      return 1;
    }
  }
  return 0;
}

void nrf24_listen(uint8_t *address)
{
  NRF24_CE = 0;
  nrf24_write_register(W_REGISTER | RX_ADDR_P0, address, TX_ADDR_WIDTH);
  nrf24_write_register_byte(W_REGISTER | EN_AA, 0x01);
  nrf24_write_register_byte(W_REGISTER | EN_RXADDR, 0x01);
  nrf24_write_register_byte(W_REGISTER | RF_CH, 0x00);
  nrf24_write_register_byte(W_REGISTER | RX_PW_P0, TX_PAYLOAD_WIDTH);
  nrf24_write_register_byte(W_REGISTER | RF_SETUP, 0x0F);
  nrf24_write_register_byte(W_REGISTER | CONFIG, 0x0F);
  NRF24_CE = 1;
}

void nrf24_transmit(uint8_t *address, uint8_t *data)
{
  NRF24_CE = 0;
  nrf24_write_register(W_REGISTER | TX_ADDR, address, TX_ADDR_WIDTH);
  nrf24_write_register(W_REGISTER | RX_ADDR_P0, address, TX_ADDR_WIDTH);
  nrf24_write_register_byte(W_REGISTER | EN_AA, 0x01);
  nrf24_write_register_byte(W_REGISTER | EN_RXADDR, 0x01);
  nrf24_write_register_byte(W_REGISTER | SETUP_RETR, 0x0A);
  nrf24_write_register_byte(W_REGISTER | RF_CH, 0x00);
  nrf24_write_register_byte(W_REGISTER | RF_SETUP, 0x0F);
  nrf24_write_register_byte(W_REGISTER | RX_PW_P0, TX_PAYLOAD_WIDTH);
  nrf24_write_register_byte(W_REGISTER | CONFIG, 0x0E);
  nrf24_write_register(W_TX_PAYLOAD, data, TX_PAYLOAD_WIDTH);
  NRF24_CE = 1;
}

uint8_t nrf24_available(void)
{
  uint8_t status;
  nrf24_read_register_byte(R_REGISTER | STATUS, &status);
  if(status & 0x40)
  {
    return 1;
  }
  return 0;
}

void nrf24_read_received_data(uint8_t *rx_data)
{
  uint8_t status;
  nrf24_read_register(R_RX_PAYLOAD, rx_data, RX_PAYLOAD_WIDTH);
  nrf24_read_register_byte(R_REGISTER | STATUS, &status);
  nrf24_write_register_byte(W_REGISTER | STATUS, status);
}
