#ifndef __BMP280_H__
#define __BMP280_H__

#include <stdint.h>
#include "iic.h"

#define BMP280_CALIB00          0x88
#define BMP280_ID               0xD0
#define BMP280_RESET            0xE0
#define BMP280_STATUS           0xF3
#define BMP280_CTRL_MEAS        0xF4
#define BMP280_CONFIG           0xF5
#define BMP280_PRESS_MSB        0xF7
#define BMP280_PRESS_LSB        0xF8
#define BMP280_PRESS_XLSB       0xF9
#define BMP280_TEMP_MSB         0xFA
#define BMP280_TEMP_LSB         0xFB
#define BMP280_TEMP_XLSB        0xFC

extern uint16_t bmp280_dig_T1;
extern int16_t bmp280_dig_T2;
extern int16_t bmp280_dig_T3;
extern uint16_t bmp280_dig_P1;
extern int16_t bmp280_dig_P2;
extern int16_t bmp280_dig_P3;
extern int16_t bmp280_dig_P4;
extern int16_t bmp280_dig_P5;
extern int16_t bmp280_dig_P6;
extern int16_t bmp280_dig_P7;
extern int16_t bmp280_dig_P8;
extern int16_t bmp280_dig_P9;

typedef struct _BMP280_PTR
{
  uint8_t status;
  float pressure;
  float temperature;
} BMP280_PTR;

void bmp280_init(uint8_t device_address);
uint8_t bmp280_reset(uint8_t device_address);
uint8_t bmp280_get_chip_id(uint8_t device_address, uint8_t *chip_id);
uint8_t bmp280_get_pressure(uint8_t device_address, BMP280_PTR *result);


#endif // __BMP280_H__
