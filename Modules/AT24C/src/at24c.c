#include "at24c.h"

uint8_t at24c_read_word(AT24C *at24c, uint8_t word_address, uint8_t *data)
{
  return iic_single_byte_read(at24c -> device_address, word_address, data);
}

uint8_t at24c_write_word(AT24C *at24c, uint8_t word_address, uint8_t data)
{
  return iic_single_byte_write(at24c -> device_address, word_address, data);
}

uint8_t at24c_read_page(AT24C *at24c, uint8_t page, uint8_t *data)
{
  uint8_t i;
  iic_start();
  iic_send_byte(at24c -> device_address);
  if(iic_read_ack() == IIC_NACK) return 1;
  iic_send_byte(page * at24c -> page_size);
  if(iic_read_ack() == IIC_NACK) return 2;

  iic_start();
  iic_send_byte(at24c -> device_address | 0x01);
  if(iic_read_ack() == IIC_NACK) return 3;

  for(i=0; i<(at24c->page_size); i++)
  {
    *(data + i) = iic_read_byte();
    if(i == (at24c->device_address)-1)
      iic_nack();
    else
      iic_ack();
  }
  iic_stop();
  return 0;
}

uint8_t at24c_write_page(AT24C *at24c, uint8_t page, uint8_t *data)
{
  uint8_t i;
  iic_start();
  iic_send_byte(at24c -> device_address);
  if(iic_read_ack() == IIC_NACK) return 1;
  iic_send_byte(page * at24c -> page_size);
  if(iic_read_ack() == IIC_NACK) return 2;

  for(i=0; i<(at24c->page_size); i++)
  {
    iic_send_byte(*(data+i));
    if(iic_read_ack() == IIC_NACK)
      return i + 3;
  }
  iic_stop();
  return 0;
}
