#include "hc-sr04.h"
#include "defines.h"

void hc_sr04_init_timer0()
{
  // max distance is 4.5m
  // max duration is 4.5m / 340m/s ~= 13235us
  // 65536 - (13235us / ( 12 / 11.0592)) ~= 53338.62
  // make more loose
  // 65536 - (15000 / ( 12 / 11.0592)) = 51712 = CA00H
  TMOD |= 0x01;
  TH0 = 0x00;
  TL0 = 0x00;
  // enable timer0 interrupt
  ET0 = 1;
  // enable all interrupts
  EA = 1;
}

void hc_sr04_trigger()
{
  HC_SR04_TRIGGER = 0;
  HC_SR04_TRIGGER = 1;
  __nop(); __nop(); __nop(); __nop(); __nop();
  __nop(); __nop(); __nop(); __nop(); __nop();
  __nop(); __nop(); __nop(); __nop(); __nop();
  HC_SR04_TRIGGER = 0;
}

int hc_sr04_echo_pulse()
{
  // REVIEW 检查初始化定时器的代码放在这里是否合适
  hc_sr04_init_timer0();
  while(!HC_SR04_ECHO);
  TR0 = 1;
  while(HC_SR04_ECHO);
  TR0 = 0;
  return (TH0 * 256 + TL0) * (12 / CRYSTAL_FREQUENCY);
}

unsigned int hc_sr04_get_distance()
{
  unsigned int duration;
  hc_sr04_trigger();
  duration = hc_sr04_echo_pulse();
  return duration * 0.017;
}
