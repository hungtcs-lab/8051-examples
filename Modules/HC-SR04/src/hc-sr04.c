#include "hc-sr04.h"

uint8_t hc_sr04_get_distance(uint16_t *distance)
{
  uint16_t duration;

  TR0 = 0;
  TF0 = 0;
  TMOD &= 0xF0;
  TMOD |= 0x01;
  TH0 = 0;
  TL0 = 0;

  HC_SR04_TRIGGER = 0;
  HC_SR04_TRIGGER = 1;
  __nop(); __nop(); __nop(); __nop(); __nop();
  __nop(); __nop(); __nop(); __nop(); __nop();
  HC_SR04_TRIGGER = 0;

  while(!HC_SR04_ECHO);
  TR0 = 1;
  while(HC_SR04_ECHO);
  TR0 = 0;

  if(TF0) {
    TF0 = 0;
    return HC_SR04_OUT_OF_RANGE;
  }

  duration = (((uint16_t)TH0) << 8) | TL0;
  *distance = (duration * (12 / CLOCK_FREQUENCY) * 0.017);

  return HC_SR04_SUCCESS;
}
