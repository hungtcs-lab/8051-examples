#include "ds18b20.h"

uint8_t ds18b20_init(void)
{
  // 首先释放总线
  DS18B20_PIN = 1;
  ds18b20_delay_10us();
  // 拉低480us ~ 960us
  DS18B20_PIN = 0;
  ds18b20_delay_500us();
  // 拉低后释放
  DS18B20_PIN = 1;
  // 等待15～60us
  ds18b20_delay_100us();
  if(DS18B20_PIN)
  {
    // 高电平状态无从机响应
    return 1;
  }
  ds18b20_delay_100us();
  return 0;
}

uint8_t ds18b20_read_byte()
{
  uint8_t i;
  uint8_t data = 0;
  for(i=0; i<8; i++)
  {
    DS18B20_PIN = 1;
    __nop(); __nop();
    DS18B20_PIN = 0;
    data >>= 1;
    DS18B20_PIN = 1;
    if(DS18B20_PIN)
    {
      data |= 0x80;
    }
    ds18b20_delay_50us();
  }
  return data;
}

void ds18b20_write_byte(uint8_t data)
{
  uint8_t i;
  for(i=0; i<8; i++)
  {
    DS18B20_PIN = 0;
    DS18B20_PIN = data & 0x01;
    ds18b20_delay_50us();
    DS18B20_PIN = 1;
    data >>= 1;
  }
  ds18b20_delay_50us();
}

int ds18b20_get_temperature(void)
{
  uint8_t th, tl;
  ds18b20_init();
  ds18b20_write_byte(SKIP_ROM);
  ds18b20_write_byte(CONVERT_T);
  delay_ms(5);
  ds18b20_init();
  ds18b20_write_byte(SKIP_ROM);
  ds18b20_write_byte(READ_SCRATCHPAD);
  tl = ds18b20_read_byte();
  th = ds18b20_read_byte();
  return (((th & 0x0F) << 4) | (tl >> 4));
}
