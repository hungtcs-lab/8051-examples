#include "tcs34725.h"

uint8_t tcs34725_read_16_bit(uint8_t register_address, uint16_t *data)
{
  uint16_t low, high;
  iic_start();
  iic_send_byte(TCS34725_ADDRESS);
  if(iic_read_ack() == IIC_NACK)
  {
    return 1;
  }
  iic_send_byte(register_address);
  if(iic_read_ack() == IIC_NACK)
  {
    return 2;
  }

  iic_start();
  iic_send_byte(TCS34725_ADDRESS | 0x01);
  if(iic_read_ack() == IIC_NACK)
  {
    return 3;
  }

  low = iic_read_byte();    iic_ack();
  high = iic_read_byte();   iic_nack();
  iic_stop();

  // printf("low: %x, high: %x\n", low, high);

  *data = (high << 8) | low;

  return 0;
}

void tcs34725_integration_time_delay(TCS34725* tcs34725)
{
  switch(tcs34725 -> integration_time) {
    case TCS34725_INTEGRATION_TIME_2_4MS: {
      delay_ms(3);
      break;
    }
    case TCS34725_INTEGRATION_TIME_24MS: {
      delay_ms(24);
      break;
    }
    case TCS34725_INTEGRATION_TIME_50MS: {
      delay_ms(50);
      break;
    }
    case TCS34725_INTEGRATION_TIME_101MS: {
      delay_ms(101);
      break;
    }
    case TCS34725_INTEGRATION_TIME_154MS: {
      delay_ms(154);
      break;
    }
    case TCS34725_INTEGRATION_TIME_700MS: {
      delay_ms(700);
      break;
    }
  }
}

uint8_t tcs34725_read_id(uint8_t *id)
{
  return iic_single_byte_read(TCS34725_ADDRESS, TCS34725_COMMAND_BIT | TCS34725_ID, id);
}

uint8_t tcs34725_enable(TCS34725* tcs34725)
{
  if(iic_single_byte_write(TCS34725_ADDRESS, TCS34725_COMMAND_BIT | TCS34725_ENABLE, TCS34725_ENABLE_PON))
  {
    return 1;
  }
  delay_ms(3);
  if(iic_single_byte_write(TCS34725_ADDRESS, TCS34725_COMMAND_BIT | TCS34725_ENABLE, TCS34725_ENABLE_PON | TCS34725_ENABLE_AEN))
  {
    return 2;
  }
  tcs34725_integration_time_delay(tcs34725);
  return 0;
}

uint8_t tcs34725_disable()
{
  uint8_t data;
  if(iic_single_byte_read(TCS34725_ADDRESS, TCS34725_COMMAND_BIT | TCS34725_ENABLE, &data))
  {
    return 1;
  }
  if(iic_single_byte_write(TCS34725_ADDRESS, TCS34725_COMMAND_BIT | TCS34725_ENABLE, data & ~(TCS34725_ENABLE_PON | TCS34725_ENABLE_AEN)))
  {
    return 2;
  }
  return 0;
}

uint8_t tcs34725_init(TCS34725* tcs43725)
{
  uint8_t id;
  if(tcs34725_read_id(&id)) {
    return 1;
  }
  if(id != 0x44) {
    return 2;
  }
  if(iic_single_byte_write(TCS34725_ADDRESS, TCS34725_COMMAND_BIT | TCS34725_ATIME, tcs43725 -> integration_time))
  {
    return 3;
  }
  if(iic_single_byte_write(TCS34725_ADDRESS, TCS34725_COMMAND_BIT | TCS34725_CONTROL, tcs43725 -> gain))
  {
    return 4;
  }
  if(tcs34725_enable(tcs43725))
  {
    return 5;
  }
  return 0;
}

uint8_t tcs34725_get_raw_data(TCS34725* tcs34725, uint16_t* r, uint16_t* g, uint16_t* b, uint16_t* c)
{
  if(tcs34725_read_16_bit(TCS34725_COMMAND_BIT | TCS34725_CDATAL, c))
  {
    return 1;
  }
  if(tcs34725_read_16_bit(TCS34725_COMMAND_BIT | TCS34725_RDATAL, r))
  {
    return 2;
  }
  if(tcs34725_read_16_bit(TCS34725_COMMAND_BIT | TCS34725_GDATAL, g))
  {
    return 3;
  }
  if(tcs34725_read_16_bit(TCS34725_COMMAND_BIT | TCS34725_BDATAL, b))
  {
    return 4;
  }
  tcs34725_integration_time_delay(tcs34725);
  return 0;
}

uint8_t tcs34725_get_rgb(TCS34725* tcs34725, float *r, float *g, float *b)
{
  uint32_t sum;
  uint16_t red, green, blue, clear;
  if(tcs34725_get_raw_data(tcs34725, &red, &green, &blue, &clear))
  {
    return 1;
  }
  sum = clear;
  if(clear == 0)
  {
    *r = *g = *b = 0;
    return 0;
  }

  *r = (float)red / sum * 255.0;
  *g = (float)green / sum * 255.0;
  *b = (float)blue / sum * 255.0;

  return 0;
}

uint8_t tcs34725_set_interrupt(uint8_t enable)
{
  uint8_t data;
  if(iic_single_byte_read(TCS34725_ADDRESS, TCS34725_COMMAND_BIT | TCS34725_ENABLE, &data))
  {
    return 1;
  }
  if(enable)
  {
    data |= TCS34725_ENABLE_AIEN;
  }
  else
  {
    data &= ~TCS34725_ENABLE_AIEN;
  }
  if(iic_single_byte_write(TCS34725_ADDRESS, TCS34725_COMMAND_BIT | TCS34725_ENABLE, data))
  {
    return 2;
  }
  return 0;
}

// uint8_t tcs34725_clear_interrupt()
// {
//   iic_single_byte_write(TCS34725_ADDRESS, TCS34725_COMMAND_BIT | 0x66)


// }
