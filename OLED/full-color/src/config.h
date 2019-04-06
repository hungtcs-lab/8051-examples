#ifndef __CONFIG_H__
#define __CONFIG_H__

#include <mcs51/8051.h>

// SPI pins
#define SPI_CS     P1_0
#define SPI_SCK    P1_1
#define SPI_MOSI   P1_2
#define SPI_MISO   P1_3

// OLED pins
#define OLED_DC    P1_4
#define OLED_RESET P1_5

#endif
