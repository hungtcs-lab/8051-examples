#ifndef __HC_SR04_H__
#define __HC_SR04_H__

void hc_sr04_init_timer0();

/**
 * trigger ultrasonic sensor
 */
void hc_sr04_trigger();

/**
 * get the echo pulse time
 * @return [description]
 */
int  hc_sr04_echo_pulse();

/**
 * calculation the distance
 */
unsigned int hc_sr04_get_distance();

#endif
