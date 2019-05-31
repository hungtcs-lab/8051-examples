#include "tm1637.h"

uint8_t tm1637_brightness_level = TM1637_BRIGHTNESS_LEVEL_8;

void tm1637_send_byte(uint8_t data)
{
  uint8_t i;
  for(i=0; i<8; i++)
  {
    IIC_SCL = 0;
    __nop(); __nop();
    IIC_SDA = (data >> i) & 0x01;
    __nop(); __nop();
    IIC_SCL = 1;
  }
}

void tm1637_display(uint8_t* codes)
{
  uint8_t i;
  iic_start();
  tm1637_send_byte(TM1637_ADDR_AUTO_INCREASE);
  iic_read_ack();
  iic_stop();

  iic_start();
  tm1637_send_byte(TM1637_ADDR_START);
  iic_read_ack();
  for(i=0; i<4; i++)
  {
    tm1637_send_byte(*(codes + i));
    iic_read_ack();
  }
  iic_stop();

  iic_start();
  tm1637_send_byte(tm1637_brightness_level);
  iic_read_ack();
  iic_stop();
}

void tm1637_display_bit(uint8_t bit, uint8_t code)
{
  iic_start();
  tm1637_send_byte(TM1637_ADDR_FIXED);
  iic_read_ack();
  iic_stop();

  iic_start();
  tm1637_send_byte(TM1637_ADDR_START | bit);
  iic_read_ack();
  tm1637_send_byte(code);
  iic_read_ack();
  iic_stop();

  iic_start();
  tm1637_send_byte(tm1637_brightness_level);
  iic_read_ack();
  iic_stop();
}

void tm1637_clear_display()
{
  tm1637_display_bit(0, 00);
  tm1637_display_bit(1, 00);
  tm1637_display_bit(2, 00);
  tm1637_display_bit(3, 00);
}
