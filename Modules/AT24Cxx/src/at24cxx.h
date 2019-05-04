#ifndef __AT24Cxx_H__
#define __AT24Cxx_H__

#include "iic.h"

typedef struct __AT24Cxx
{
  uint8_t deviceAddress;
} AT24Cxx;

uint8_t at24cxx_read_byte(AT24Cxx *at24cxx, uint8_t wordAddress, uint8_t *data);
uint8_t at24cxx_write_byte(AT24Cxx *at24cxx, uint8_t wordAddress, uint8_t data);

#endif // __AT24Cxx_H__
