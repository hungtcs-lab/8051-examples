#include "ir-nec.h"

uint8_t ir_nec_start = 0;
uint16_t ir_nec_count = 0;
uint32_t ir_nec_data;
uint32_t ir_nec_safe_data;

void ir_nec_timer_init()
{
  EA = 1;
  ET0 = 1;
  TMOD |= 0x02;
  TH0 = 0x00;
  TL0 = 0x00;
  TR0 = 1;
}

void ir_nec_signal_interrupt_init()
{
  EA = 1;
  EX0 = 1;
  IT0 = 1;
}

void ir_nec_timer_interrupt_handler() __interrupt 1
{
  ir_nec_count++;
}

void ir_nec_signal_interrupt_handler() __interrupt 0
{
  if(ir_nec_start)
  {
    // 起始码
    if(ir_nec_count > 32)
    {
      ir_nec_data = 0;
      ir_nec_start = 1;
    }
    // 1码
    else if(ir_nec_count > 6)
    {
      ir_nec_data <<= 1;
      ir_nec_data |= 0x01;
    }
    // 0码
    else if(ir_nec_count > 3)
    {
      ir_nec_data <<= 1;
    }
    ir_nec_start++;
  }
  else
  {
    ir_nec_start = 1;
  }
  ir_nec_count = 0;
}

void ir_nec_init()
{
  ir_nec_timer_init();
  ir_nec_signal_interrupt_init();
}

uint8_t ir_nec_available()
{
  if(ir_nec_start == 34)
  {
    ir_nec_start = 0;
    ir_nec_safe_data = ir_nec_data;
    return 1;
  }
  return 0;
}

uint32_t ir_nec_get_code()
{
  return ir_nec_safe_data;
}
