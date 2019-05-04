#include "at24cxx.h"

uint8_t at24cxx_read_byte(AT24Cxx *at24cxx, uint8_t wordAddress, uint8_t *data)
{
  iic_start();
  iic_send_byte(at24cxx -> deviceAddress & 0xFE);
  if(iic_read_ack() == IIC_NACK)
  {
    return 1;
  }
  iic_send_byte(wordAddress);
  if(iic_read_ack() == IIC_NACK)
  {
    return 2;
  }
  iic_start();
  iic_send_byte(at24cxx -> deviceAddress | 0x01);
  if(iic_read_ack() == IIC_NACK)
  {
    return 3;
  }
  *data = iic_read_byte();
  iic_nack();
  iic_stop();
  return 0;
}

uint8_t at24cxx_write_byte(AT24Cxx *at24cxx, uint8_t wordAddress, uint8_t data)
{
  iic_start();
  iic_send_byte(at24cxx -> deviceAddress & 0xFE);
  if(iic_read_ack() == IIC_NACK)
  {
    return 1;
  }
  iic_send_byte(wordAddress);
  if(iic_read_ack() == IIC_NACK)
  {
    return 2;
  }
  iic_send_byte(data);
  if(iic_read_ack() == IIC_NACK)
  {
    return 3;
  }
  iic_stop();
  return 0;
}
