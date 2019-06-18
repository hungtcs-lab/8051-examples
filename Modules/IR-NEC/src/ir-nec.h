#ifndef __IR_NEC_H__
#define __IR_NEC_H__

#include <stdint.h>
#include <stdio.h>
#include "config.h"

extern uint8_t ir_nec_start;
extern uint16_t ir_nec_count;
extern uint32_t ir_nec_data;
extern uint32_t ir_nec_safe_data;

void ir_nec_timer_init();
void ir_nec_signal_interrupt_init();
void ir_nec_timer_interrupt_handler() __interrupt 1;
void ir_nec_signal_interrupt_handler() __interrupt 0;
void ir_nec_init();
uint8_t ir_nec_available();
uint32_t ir_nec_get_code();

#endif // __IR_NEC_H__
