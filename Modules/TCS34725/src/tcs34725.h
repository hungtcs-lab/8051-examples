#ifndef __TCS34725_H__
#define __TCS34725_H__

#include <stdio.h>
#include <stdint.h>
#include "iic.h"
#include "config.h"

#define TCS34725_ADDRESS          (0x29 << 1)
#define TCS34725_COMMAND_BIT      0x80

#define TCS34725_ENABLE           0x00
#define TCS34725_ATIME            0x01
#define TCS34725_WTIME            0x03
#define TCS34725_AILTL            0x04
#define TCS34725_AILTH            0x05
#define TCS34725_AIHTL            0x06
#define TCS34725_AIHTH            0x07
#define TCS34725_PERS             0x0C
#define TCS34725_CONFIG           0x0D
#define TCS34725_CONTROL          0x0F
#define TCS34725_ID               0x12
#define TCS34725_STATUS           0x13
#define TCS34725_CDATAL           0x14
#define TCS34725_CDATAH           0x15
#define TCS34725_RDATAL           0x16
#define TCS34725_RDATAH           0x17
#define TCS34725_GDATAL           0x18
#define TCS34725_GDATAH           0x19
#define TCS34725_BDATAL           0x1A
#define TCS34725_BDATAH           0x1B


#define TCS34725_ENABLE_PON       0x01
#define TCS34725_ENABLE_AEN       0x02
#define TCS34725_ENABLE_WEN       0x08
#define TCS34725_ENABLE_AIEN      0x10

#define tcs34725_led_on()         do{ TCS34725_LED = 1; } while(0)
#define tcs34725_led_off()        do{ TCS34725_LED = 0; } while(0)

typedef enum {
  TCS34725_INTEGRATION_TIME_2_4MS = 0xFF,
  TCS34725_INTEGRATION_TIME_24MS = 0xF6,
  TCS34725_INTEGRATION_TIME_50MS = 0xEB,
  TCS34725_INTEGRATION_TIME_101MS = 0xD5,
  TCS34725_INTEGRATION_TIME_154MS = 0xC0,
  TCS34725_INTEGRATION_TIME_700MS = 0x00,
} TCS34725_INTEGRATION_TIME;

typedef enum {
  TCS34725_GAIN_1X = 0x00,
  TCS34725_GAIN_4X = 0x01,
  TCS34725_GAIN_16X = 0x02,
  TCS34725_GAIN_60X = 0x03,
} TCS34725_GAIN;

typedef struct {
  TCS34725_GAIN gain;
  TCS34725_INTEGRATION_TIME integration_time;
} TCS34725;

uint8_t tcs34725_read_id(uint8_t *id);
uint8_t tcs34725_init(TCS34725* tcs34725);
uint8_t tcs34725_enable(TCS34725* tcs34725);
uint8_t tcs34725_disable();
uint8_t tcs34725_get_raw_data(TCS34725* tcs34725, uint16_t* r, uint16_t* g, uint16_t* b, uint16_t* c);
uint8_t tcs34725_get_rgb(TCS34725* tcs34725, float *r, float *g, float *b);

uint8_t tcs34725_set_interrupt(uint8_t enable);

#endif // __TCS3472_H__
