#ifndef __DHT22_H__
#define __DHT22_H__

#include "config.h"
#include "delay.h"

typedef struct __DHT22MeasurementResult {
  uint8_t state;
  float humidity;
  float temperature;
} DHT22MeasurementResult;

void dht22_measuring(DHT22MeasurementResult *result);

#endif // __DHT22_H__
