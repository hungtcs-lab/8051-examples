#ifndef __HC_SR04_H__
#define __HC_SR04_H__

#include <stdint.h>
#include "delay.h"
#include "config.h"

#define HC_SR04_SUCCESS         0
#define HC_SR04_OUT_OF_RANGE    1

/**
 * @brief 调用HC-SR04测量距离
 *
 * @param distance    距离
 * @return uint8_t    测量状态
 */
uint8_t hc_sr04_get_distance(uint16_t *distance);

#endif // __HC_SR04_H__
