#include "dht22.h"

void delay_10us()
{
  __nop();
  __nop();
  __nop();
  __nop();
  // __nop();
  // __nop();
}

uint32_t dht22_read_data(void)
{
  uint8_t i;
  uint8_t checkCode = 0;
  uint32_t value = 0;
  for (i = 0; i < 32; i++)
  {
    while(!DHT22_PIN);

    delay_10us();
    delay_10us();
    delay_10us();

    value <<= 1;
    if(DHT22_PIN)
    {
      value |= 0x01;
      while(DHT22_PIN);
    }
  }
  for (i = 0; i < 8; i++)
  {
    while(!DHT22_PIN);

    delay_10us();
    delay_10us();
    delay_10us();

    checkCode <<= 1;
    if(DHT22_PIN)
    {
      checkCode |= 0x01;
      while(DHT22_PIN);
    }
  }

  if(((uint8_t)((uint8_t)(value >> 24) + (((uint8_t)(value >> 16)) & 0xFF) + (((uint8_t)(value >> 8)) & 0xFF) + (((uint8_t)value) & 0xFF))) == checkCode)
  {
    return value;
  }
  else
  {
    return 0;
  }
}

void dht22_measuring(DHT22MeasurementResult *result)
{
  float humidity;
  float temperature;
  uint8_t subzero = 0;
  uint32_t value;

  DHT22_PIN = 1;
  delay_ms(1);
  DHT22_PIN = 0;
  delay_ms(10);
  DHT22_PIN = 1;

  delay_10us();
  delay_10us();
  delay_10us();
  delay_10us();
  delay_10us();

  if(DHT22_PIN)
  {
    result -> state = 1;
    return;
  }
  while(!DHT22_PIN);
  while(DHT22_PIN);

  value = dht22_read_data();
  if(value)
  {
    result -> state = 0;

    humidity = (value >> 28 & 0x0F) * 4096 + (value >> 24 & 0x0F) * 256 + (value >> 20 & 0x0F) * 16 + (value >> 16 & 0x0F);
    result -> humidity = humidity / 10;

    if(value & 0x8000)
    {
      subzero = 1;
      value &= 0x00007FFF;
    }
    temperature = ((value >> 12) & 0x0F) * 4096 + ((value >> 8) & 0x0F) * 256 + ((value >> 4) & 0x0F) * 16 + (value & 0x0F);
    if(subzero)
    {
      result -> temperature = -(temperature / 10);
    }
    else
    {
      result -> temperature = temperature / 10;
    }
  }
  else
  {
    result -> state = 2;
  }
}
