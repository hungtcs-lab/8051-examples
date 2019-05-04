#include "pcf8563.h"

uint8_t pcf8563pcf9563_to_bcd(uint8_t value)
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
  iic_send_byte(device_address);
  iic_read_ack();
  iic_send_byte(0x02);
  iic_read_ack();

  iic_start();
  iic_send_byte(device_address | 0x01);
  iic_read_ack();

  datetime -> seconds = iic_read_byte();    iic_ack();
  datetime -> minutes = iic_read_byte();    iic_ack();
  datetime -> hours = iic_read_byte();      iic_ack();
  datetime -> days = iic_read_byte();       iic_ack();
  datetime -> weekdays = iic_read_byte();   iic_ack();
  datetime -> months = iic_read_byte();     iic_ack();
  datetime -> years = iic_read_byte();      iic_nack();
  iic_stop();

  datetime -> _VL = datetime -> seconds & 0x80;
  datetime -> _CENTURY = datetime -> months & 0x80;
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
  datetime -> months |= (uint8_t)(datetime -> _CENTURY << 7);

  iic_start();

  iic_send_byte(device_address);
  iic_read_ack();

  iic_send_byte(0x02);
  iic_read_ack();

  iic_send_byte(pcf8563pcf9563_to_bcd(datetime -> seconds));  iic_read_ack();
  iic_send_byte(pcf8563pcf9563_to_bcd(datetime -> minutes));  iic_read_ack();
  iic_send_byte(pcf8563pcf9563_to_bcd(datetime -> hours));    iic_read_ack();
  iic_send_byte(pcf8563pcf9563_to_bcd(datetime -> days));     iic_read_ack();
  iic_send_byte(datetime -> weekdays);                        iic_read_ack();
  iic_send_byte(pcf8563pcf9563_to_bcd(datetime -> months));   iic_read_ack();
  iic_send_byte(pcf8563pcf9563_to_bcd(datetime -> years));    iic_read_ack();

  iic_stop();
}
