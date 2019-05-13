#include <stdio.h>
#include <mcs51/8051.h>
#include "delay.h"
#include "serial.h"
#include "bmp280.h"

int putchar(int c)
{
	while(!(SCON & 0x02));
	SCON &= ~0x02;
	SBUF = (char)c;
  return c;
}

void main()
{
  uint8_t status;
  uint8_t chip_id;
  serial_init();

  bmp280_init(BMP280_DEVICE_ADDRESS);
  bmp280_reset(BMP280_DEVICE_ADDRESS);

  printf("bmp280_dig_T1: %d\n", bmp280_dig_T1);
  printf("bmp280_dig_T2: %d\n", bmp280_dig_T2);
  printf("bmp280_dig_T3: %d\n", bmp280_dig_T3);

  status = bmp280_get_chip_id(BMP280_DEVICE_ADDRESS, &chip_id);
  printf("status: 0x%02x, chip id is 0x%02x\n", status, chip_id);

  iic_single_byte_write(BMP280_DEVICE_ADDRESS, BMP280_CTRL_MEAS, 0xFF);
  iic_single_byte_write(BMP280_DEVICE_ADDRESS, BMP280_CONFIG, 0x00);

  while(1)
  {
    BMP280_PTR result;
    bmp280_get_pressure(BMP280_DEVICE_ADDRESS, &result);

    printf("p: %d, t: %d\n", result.pressure, result.temperature);
    delay_ms(500);
  }
}
