#include "bmp280.h"

uint16_t bmp280_dig_T1;
int16_t bmp280_dig_T2;
int16_t bmp280_dig_T3;
uint16_t bmp280_dig_P1;
int16_t bmp280_dig_P2;
int16_t bmp280_dig_P3;
int16_t bmp280_dig_P4;
int16_t bmp280_dig_P5;
int16_t bmp280_dig_P6;
int16_t bmp280_dig_P7;
int16_t bmp280_dig_P8;
int16_t bmp280_dig_P9;

uint16_t bmp280_read_uint16()
{
  uint8_t msb, lsb;
  lsb = iic_read_byte();
  iic_ack();
  msb = iic_read_byte();
  return ((uint16_t)msb) << 8 | lsb;
}

void bmp280_init(uint8_t device_address)
{
  iic_start();
  iic_send_byte(device_address);      iic_read_ack();
  iic_send_byte(0x88);                iic_read_ack();

  iic_start();
  iic_send_byte(device_address | 0x01);   iic_read_ack();

  bmp280_dig_T1 = bmp280_read_uint16();   iic_ack();
  bmp280_dig_T2 = bmp280_read_uint16();   iic_ack();
  bmp280_dig_T3 = bmp280_read_uint16();   iic_ack();
  bmp280_dig_P1 = bmp280_read_uint16();   iic_ack();
  bmp280_dig_P2 = bmp280_read_uint16();   iic_ack();
  bmp280_dig_P3 = bmp280_read_uint16();   iic_ack();
  bmp280_dig_P4 = bmp280_read_uint16();   iic_ack();
  bmp280_dig_P5 = bmp280_read_uint16();   iic_ack();
  bmp280_dig_P6 = bmp280_read_uint16();   iic_ack();
  bmp280_dig_P7 = bmp280_read_uint16();   iic_ack();
  bmp280_dig_P8 = bmp280_read_uint16();   iic_ack();
  bmp280_dig_P9 = bmp280_read_uint16();   iic_nack();

  iic_stop();
}

uint8_t bmp280_reset(uint8_t device_address)
{
  return iic_single_byte_write(device_address, BMP280_RESET, 0xB6);
}

uint8_t bmp280_get_chip_id(uint8_t device_address, uint8_t *chip_id)
{
  return iic_single_byte_read(device_address, BMP280_ID, chip_id);
}

uint8_t bmp280_get_pressure(uint8_t device_address, BMP280_PTR *result)
{
  uint8_t msb, lsb, xlsb;
  // uint8_t p_msb, p_lsb, p_xlsb;
  int32_t adc_T, adc_P;
  int32_t var1, var2, t_fine;

  iic_start();
  iic_send_byte(device_address);
  if(iic_read_ack() != 0) return 1;

  iic_send_byte(BMP280_TEMP_MSB);
  if(iic_read_ack() != 0) return 2;

  iic_start();
  iic_send_byte(device_address | 0x01);
  if(iic_read_ack() != 0) return 3;

  msb = iic_read_byte();    iic_ack();
  lsb = iic_read_byte();    iic_ack();
  xlsb = iic_read_byte();   iic_ack();

  adc_T = ((uint32_t)msb << 12) | (((uint32_t)lsb) << 4) | (xlsb >> 4);

  msb = iic_read_byte();    iic_ack();
  lsb = iic_read_byte();    iic_ack();
  xlsb = iic_read_byte();   iic_nack();
  adc_P = ((uint32_t)msb << 12) | (((uint32_t)lsb) << 4) | (xlsb >> 4);

  iic_stop();


  var1 = (adc_T / 16384.0 - bmp280_dig_T1 / 1024.0) * bmp280_dig_T2;
  var2 = ((adc_T / 131072.0 - bmp280_dig_T1 / 8192.0) * (adc_T / 131072.0 - bmp280_dig_T1 / 8192.0)) * bmp280_dig_T3;
  t_fine = (uint32_t)(var1 + var2);
  result -> temperature = (var1 + var2) / 5120.0;

  var1 = ((double)t_fine / 2.0) - 64000.0;
  var2 = var1 * var1 * ((double)bmp280_dig_P6) / 32768.0;
  var2 = var2 + var1 * ((double)bmp280_dig_P5) * 2.0;
  var2 = (var2/4.0) + (((double)bmp280_dig_P4) * 65536.0);
  var1 = (((double)bmp280_dig_P3) * var1 * var1 / 524288.0 + ((double)bmp280_dig_P2) * var1) / 524288.0;
  var1 = (1.0 + var1 / 32768.0) * ((double)bmp280_dig_P1);
  result -> pressure = 1048576.0 - (double)adc_P;
  result -> pressure = (result -> pressure - (var2 / 4096.0)) * 6250.0 / var1;
  var1 = ((double)bmp280_dig_P9) * result -> pressure * result -> pressure / 2147483648.0;
  var2 = result -> pressure * ((double)bmp280_dig_P8) / 32768.0;
  result -> pressure = result -> pressure + (var1 + var2 + ((double)bmp280_dig_P7)) / 16.0;

  return 0;
}
