#ifndef __PCF9563_H__
#define __PCF9563_H__

#include <stdint.h>
#include "iic.h"
#include "config.h"

typedef struct __PCF8563_DATETIME
{
  uint8_t seconds;
  uint8_t minutes;
  uint8_t hours;
  uint8_t days;
  uint8_t weekdays;
  uint8_t months;
  uint8_t years;

  uint8_t _VL;
  uint8_t _CENTURY;
} PCF8563_DATETIME;

void pcf8563_get_datetime(uint8_t device_address, PCF8563_DATETIME *datetime);
void pcf8563_set_datetime(uint8_t device_address, PCF8563_DATETIME *datetime);

#endif // __PCF9563_H__
