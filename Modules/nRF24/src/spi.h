#ifndef __SPI_H__
#define __SPI_H__

#include "config.h"
#include <stdint.h>

/**
 * 进行一次SPI传输
 *
 * @param data      发送的数据
 * @return uint8_t  接收到的数据
 */
uint8_t spi_transmit(uint8_t data);

#endif // __SPI_H__
