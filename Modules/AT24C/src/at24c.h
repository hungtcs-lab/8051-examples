#ifndef __AT24C_H__
#define __AT24C_H__

#include <stdint.h>
#include "iic.h"

#define AT24C_PAGE_SIZE_8   8
#define AT24C_PAGE_SIZE_16  16

typedef struct _AT24C
{
  uint8_t page_size;
  uint8_t device_address;
} AT24C;

uint8_t at24c_read_word(AT24C *at24c, uint8_t word_address, uint8_t *data);
uint8_t at24c_write_word(AT24C *at24c, uint8_t word_address, uint8_t data);

uint8_t at24c_read_page(AT24C *at24c, uint8_t page, uint8_t *data);
uint8_t at24c_write_page(AT24C *at24c, uint8_t page, uint8_t *data);

#endif // __AT24C_H__
