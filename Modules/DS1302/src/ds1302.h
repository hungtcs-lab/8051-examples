#ifndef __DS1302_H__
#define __DS1302_H__

#include <stdint.h>
#include "delay.h"
#include "config.h"

#define DS1302_ADDR_SEC         0x80
#define DS1302_ADDR_MIN         0x82
#define DS1302_ADDR_HR          0x84
#define DS1302_ADDR_DATE        0x86
#define DS1302_ADDR_MONTH       0x88
#define DS1302_ADDR_DAY         0x8A
#define DS1302_ADDR_YEAR        0x8C
#define DS1302_ADDR_CONTROL     0x8E
#define DS1302_TRICKLE_CHARGER  0x90
#define DS1302_CLOCK_BURST      0xBE

#define ds1302_write_enable()               ds1302_write_register(DS1302_ADDR_CONTROL, 0x00)
#define ds1302_write_disable()              ds1302_write_register(DS1302_ADDR_CONTROL, 0x80)
#define ds1302_trickle_charger_disable()    ds1302_write_register(DS1302_TRICKLE_CHARGER, 0x00)

typedef struct __DS1302_DATETIME
{
  // 秒钟
  uint8_t second;
  // 分钟
  uint8_t minute;
  // 小时
  uint8_t hour;
  // 日期
  uint8_t date;
  // 月份
  uint8_t month;
  // 星期
  uint8_t day;
  // 年分
  uint8_t year;
} DS1302_DATETIME;

uint8_t ds1302_to_bcd(uint8_t value);
uint8_t ds1302_from_bcd(uint8_t bcd);

uint8_t ds1302_read();
void ds1302_write(uint8_t data);
uint8_t ds1302_read_register(uint8_t addr);
void ds1302_write_register(uint8_t addr, uint8_t data);
void ds1302_get_datetime(DS1302_DATETIME *datetime);
void ds1302_set_datetime(DS1302_DATETIME *datetime);

void ds1302_halt();
void ds1302_start();

#endif // __DS1302_H__
