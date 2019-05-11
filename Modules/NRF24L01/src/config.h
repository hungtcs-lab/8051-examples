#ifndef __CONFIG_H__
#define __CONFIG_H__

#include <mcs51/8051.h>

// spi pins
#define SPI_CS          P2_4
#define SPI_SCK         P2_3
#define SPI_MOSI        P2_2
#define SPI_MISO        P2_1

// nRF24L01 pins
#define NRF24_CE        P2_5
#define NRF24_IRQ       P2_0

// #define NRF24_RECEIVER
#define NRF24_TRANSMITTER

#endif
