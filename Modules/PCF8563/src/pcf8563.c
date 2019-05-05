#include "pcf8563.h"

uint8_t pcf9563_to_bcd(uint8_t value)
{
  return ((value / 10) << 4 | (value % 10));
}

uint8_t pcf8563_from_bcd(uint8_t bcd)
{
  return ((bcd & 0x70) >> 4) * 10 + (bcd & 0x0F);
}

void pcf8563_get_datetime(uint8_t device_address, PCF8563_DATETIME *datetime)
{
  iic_start();
  iic_send_byte(device_address);            iic_read_ack();
  iic_send_byte(PCF8563_ADDR_SECONDS);      iic_read_ack();

  iic_start();
  iic_send_byte(device_address | 0x01);     iic_read_ack();

  datetime -> seconds = iic_read_byte();    iic_ack();
  datetime -> minutes = iic_read_byte();    iic_ack();
  datetime -> hours = iic_read_byte();      iic_ack();
  datetime -> days = iic_read_byte();       iic_ack();
  datetime -> weekdays = iic_read_byte();   iic_ack();
  datetime -> months = iic_read_byte();     iic_ack();
  datetime -> years = iic_read_byte();      iic_nack();
  iic_stop();

  // 处理读取到的寄存器数据，转换成时间格式
  datetime -> _VL = datetime -> seconds & 0x80;
  datetime -> century = datetime -> months & 0x80;
  datetime -> seconds = pcf8563_from_bcd(datetime -> seconds & 0x7F);
  datetime -> minutes = pcf8563_from_bcd(datetime -> minutes & 0x7F);
  datetime -> hours = pcf8563_from_bcd(datetime -> hours & 0x3F);
  datetime -> days = pcf8563_from_bcd(datetime -> days  & 0x3F);
  datetime -> weekdays = datetime -> weekdays & 0x07;
  datetime -> months = pcf8563_from_bcd(datetime -> months & 0x1F);
  datetime -> years = pcf8563_from_bcd(datetime -> years);
}

void pcf8563_set_datetime(uint8_t device_address, PCF8563_DATETIME *datetime)
{
  datetime -> _VL = 0;
  datetime -> months |= (uint8_t)(datetime -> century << 7);

  iic_start();
  iic_send_byte(device_address);                        iic_read_ack();
  iic_send_byte(PCF8563_ADDR_SECONDS);                  iic_read_ack();

  iic_send_byte(pcf9563_to_bcd(datetime -> seconds));   iic_read_ack();
  iic_send_byte(pcf9563_to_bcd(datetime -> minutes));   iic_read_ack();
  iic_send_byte(pcf9563_to_bcd(datetime -> hours));     iic_read_ack();
  iic_send_byte(pcf9563_to_bcd(datetime -> days));      iic_read_ack();
  iic_send_byte(datetime -> weekdays);                  iic_read_ack();
  iic_send_byte(pcf9563_to_bcd(datetime -> months));    iic_read_ack();
  iic_send_byte(pcf9563_to_bcd(datetime -> years));     iic_read_ack();

  iic_stop();
}

void pcf8563_set_clkout(uint8_t device_address, uint8_t clkout_frequency)
{
  iic_single_byte_write(device_address, PCF8563_CLKOUT_FREQUENCY, clkout_frequency);
}

void pcf8563_set_countdown(uint8_t device_address, uint8_t clock_frequency, uint8_t value)
{
  iic_single_byte_write(device_address, PCF8563_TIMER_COUNTDOWN_VALUE, value);
  iic_single_byte_write(device_address, PCF8563_TIMER_CONTROL, clock_frequency);
}

void pcf8563_set_interrupt_flag(uint8_t device_address, uint8_t interrupt_flag)
{
  uint8_t data;
  iic_single_byte_read(device_address, PCF8563_ADDR_CONTROL_STATUS_2, &data);
  iic_single_byte_write(device_address, PCF8563_ADDR_CONTROL_STATUS_2, data | interrupt_flag);
}

void pcf8563_clear_interrupt_flag(uint8_t device_address, uint8_t interrupt_flag)
{
  uint8_t data;
  iic_single_byte_read(device_address, PCF8563_ADDR_CONTROL_STATUS_2, &data);
  iic_single_byte_write(device_address, PCF8563_ADDR_CONTROL_STATUS_2, data & ~interrupt_flag);
}

uint8_t pcf8563_get_interrupt_flag(uint8_t device_address, uint8_t interrupt_flag)
{
  uint8_t data;
  iic_single_byte_read(device_address, PCF8563_ADDR_CONTROL_STATUS_2, &data);
  return data & 0x1F & interrupt_flag;
}

void pcf8563_set_alarm(uint8_t device_address, uint8_t minute, uint8_t hour, uint8_t day, uint8_t weekday)
{
  iic_start();
  iic_send_byte(device_address);                  iic_read_ack();
  iic_send_byte(PCF8563_ADDR_MINUTE_ALARM);       iic_read_ack();
  iic_send_byte(pcf9563_to_bcd(minute));          iic_read_ack();
  iic_send_byte(pcf9563_to_bcd(hour) & 0xBF);     iic_read_ack();
  iic_send_byte(pcf9563_to_bcd(day) & 0xBF);      iic_read_ack();
  iic_send_byte(weekday & 0x87);                  iic_read_ack();
  iic_stop();
}
