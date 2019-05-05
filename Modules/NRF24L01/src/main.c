#include <stdio.h>
#include <mcs51/8051.h>
#include "delay.h"
#include "serial.h"
#include "nrf24l01.h"

int putchar(int c)
{
	while(!(SCON & 0x02));
	SCON &= ~0x02;
	SBUF = (char)c;
  return c;
}

void main()
{
  #if defined(NRF24_TRANSMITTER)
    uint8_t address[] = { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF };
    uint8_t tx_data[32] = { 0x01, 'A' };

    SPI_CS = 1;
    NRF24_CE = 0;
    SPI_SCK = 0;

    serial_init();

    printf("device check result: %d\n", nrf24_device_check());

    while(1)
    {
      nrf24_transmit(address, tx_data);
      delay_ms(3000);
    }
  #elif defined(NRF24_RECEIVER)
    uint8_t i;
    uint8_t address[] = { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF };
    uint8_t rx_data[32];

    SPI_CS = 1;
    NRF24_CE = 0;
    SPI_SCK = 0;

    serial_init();

    printf("device check result: %d\n", nrf24_device_check());
    nrf24_listen(address);

    while(1)
    {
      if(nrf24_available())
      {
        nrf24_read_received_data(rx_data);
        for(i=0; i<RX_PAYLOAD_WIDTH; i++)
        {
          printf("%c", rx_data[i]);
        }
        printf("\n");
      }
    }
  #endif
}
