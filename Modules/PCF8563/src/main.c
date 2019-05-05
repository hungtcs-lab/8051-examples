#include <stdio.h>
#include <stdint.h>
#include <mcs51/8051.h>
#include "iic.h"
#include "delay.h"
#include "config.h"
#include "serial.h"
#include "pcf8563.h"

PCF8563_DATETIME datetime;

int putchar(int c)
{
	while(!(SCON & 0x02));
	SCON &= ~0x02;
	SBUF = (char)c;
  return c;
}

void interrupt_init()
{
  // 开总中断
  EA = 1;
  // 开外部中断
  EX0 = 1;
  EX1 = 1;
  // 设置下降沿触发
  IT0 = 1;
  IT1 = 1;
}

void main(void)
{
  serial_init();
  interrupt_init();

  datetime.seconds = 0;
  datetime.minutes = 0;
  datetime.hours = 0;
  datetime.days = 1;
  datetime.weekdays = 1;
  datetime.months = 1;
  datetime.years = 19;

  // 设置初始时间日期
  pcf8563_set_datetime(PCF8563_DEVICE_ADDRESS, &datetime);
  // 设置中断
  pcf8563_set_interrupt_flag(PCF8563_DEVICE_ADDRESS, PCF8563_INTERRUPT_FLAG_TI_TP | PCF8563_INTERRUPT_FLAG_TIE | PCF8563_INTERRUPT_FLAG_AIE);
  // 设置闹钟
  pcf8563_set_alarm(PCF8563_DEVICE_ADDRESS, 1, PCF8563_ALARM_DISABLE, PCF8563_ALARM_DISABLE, PCF8563_ALARM_DISABLE);
  // 设置时钟输出
  pcf8563_set_clkout(PCF8563_DEVICE_ADDRESS, PCF8563_CLKOUT_FREQUENCY_1_HZ);
  // 设置倒计时
  pcf8563_set_countdown(PCF8563_DEVICE_ADDRESS, PCF8563_TIMER_SOURCE_CLOCK_FREQUENCY_1_HZ, 5);

  while(1);
}

void interrupt_ex0() __interrupt 0
{
  uint8_t flags;
  flags = pcf8563_get_interrupt_flag(PCF8563_DEVICE_ADDRESS, 0xFF);
  if(flags & PCF8563_INTERRUPT_FLAG_TF)
  {
    printf("countdown triggered\n");
    pcf8563_clear_interrupt_flag(PCF8563_DEVICE_ADDRESS, PCF8563_INTERRUPT_FLAG_TF);
  }
  if(flags & PCF8563_INTERRUPT_FLAG_AF)
  {
    printf("alarm triggered\n");
    pcf8563_clear_interrupt_flag(PCF8563_DEVICE_ADDRESS, PCF8563_INTERRUPT_FLAG_AF);
  }

  printf("interrupt flags: 0x%02x\n", flags);
}

void interrupt_ex1() __interrupt 2
{
  pcf8563_get_datetime(PCF8563_DEVICE_ADDRESS, &datetime);
  printf("20%02d/%02d/%02d %02d:%02d:%02d Wk.%d\n", datetime.years, datetime.months, datetime.days, datetime.hours, datetime.minutes, datetime.seconds, datetime.weekdays);
}
