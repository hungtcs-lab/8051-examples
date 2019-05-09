#include "ds1302.h"

uint8_t ds1302_to_bcd(uint8_t value)
{
  return ((value / 10) << 4 | (value % 10));
}

uint8_t ds1302_from_bcd(uint8_t bcd)
{
  return ((bcd & 0xF0) >> 4) * 10 + (bcd & 0x0F);
}

uint8_t ds1302_read()
{
  uint8_t i;
  uint8_t data = 0;
  for(i=0; i<8; i++)
  {
    DS1302_SCK = 0;
    data >>= 1;
    if(DS1302_SDA)
    {
      data |= 0x80;
    }
    DS1302_SCK = 1;
    __nop();
  }
  return data;
}

void ds1302_write(uint8_t data)
{
  uint8_t i;
  for(i=0; i<8; i++)
  {
    DS1302_SCK = 0;
    DS1302_SDA = (data >> i) & 0x01;
    DS1302_SCK = 1;
  }
}

uint8_t ds1302_read_register(uint8_t addr)
{
  uint8_t data;
  DS1302_RST = 0;
  DS1302_SCK = 0;
  DS1302_RST = 1;
  ds1302_write(addr | 0x01);
  data = ds1302_read();
  DS1302_SCK = 0;
  DS1302_RST = 0;
  return data;
}

void ds1302_write_register(uint8_t addr, uint8_t data)
{
  DS1302_RST = 0;
  DS1302_SCK = 0;
  DS1302_RST = 1;
  ds1302_write(addr);
  ds1302_write(data);
  DS1302_SCK = 0;
  DS1302_RST = 0;
}

void ds1302_get_datetime(DS1302_DATETIME *datetime)
{
  DS1302_RST = 0;
  DS1302_SCK = 0;
  DS1302_RST = 1;
  ds1302_write(DS1302_CLOCK_BURST | 0x01);
  datetime -> second = ds1302_from_bcd(ds1302_read());
  datetime -> minute = ds1302_from_bcd(ds1302_read());
  datetime -> hour = ds1302_from_bcd(ds1302_read());
  datetime -> date = ds1302_from_bcd(ds1302_read());
  datetime -> month = ds1302_from_bcd(ds1302_read());
  datetime -> day = ds1302_from_bcd(ds1302_read());
  datetime -> year = ds1302_from_bcd(ds1302_read());
  ds1302_read();
  DS1302_RST = 0;
}

void ds1302_set_datetime(DS1302_DATETIME *datetime)
{
  ds1302_write_enable();
  DS1302_RST = 0;
  DS1302_SCK = 0;
  DS1302_RST = 1;
  ds1302_write(DS1302_CLOCK_BURST);
  ds1302_write(ds1302_to_bcd(datetime -> second) | 0x80);
  ds1302_write(ds1302_to_bcd(datetime -> minute));
  ds1302_write(ds1302_to_bcd(datetime -> hour));
  ds1302_write(ds1302_to_bcd(datetime -> date));
  ds1302_write(ds1302_to_bcd(datetime -> month));
  ds1302_write(ds1302_to_bcd(datetime -> day));
  ds1302_write(ds1302_to_bcd(datetime -> year));
  ds1302_write(0x80);
  DS1302_RST = 0;
}

void ds1302_halt()
{
  ds1302_write_enable();
  ds1302_write_register(DS1302_ADDR_SEC, ds1302_read_register(DS1302_ADDR_SEC) | 0x80);
  ds1302_write_disable();
}

void ds1302_start()
{
  ds1302_write_enable();
  ds1302_write_register(DS1302_ADDR_SEC, ds1302_read_register(DS1302_ADDR_SEC) & 0x7F);
  ds1302_write_disable();
}
