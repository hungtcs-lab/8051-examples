#ifndef __PCF9563_H__
#define __PCF9563_H__

#include <stdint.h>
#include "iic.h"
#include "config.h"

// 寄存器地址定义
#define PCF8563_ADDR_CONTROL_STATUS_1                 0x00
#define PCF8563_ADDR_CONTROL_STATUS_2                 0x01
#define PCF8563_ADDR_SECONDS                          0x02
#define PCF8563_ADDR_MINUTES                          0x03
#define PCF8563_ADDR_HOURS                            0x04
#define PCF8563_ADDR_DAYS                             0x05
#define PCF8563_ADDR_WEEKDAYS                         0x06
#define PCF8563_ADDR_MONTHS_CENTURY                   0x07
#define PCF8563_ADDR_YEARS                            0x08
#define PCF8563_ADDR_MINUTE_ALARM                     0x09
#define PCF8563_ADDR_HOUR_ALARM                       0x0A
#define PCF8563_ADDR_DAY_ALARM                        0x0B
#define PCF8563_ADDR_WEEKDAY_ALARM                    0x0C
#define PCF8563_CLKOUT_FREQUENCY                      0x0D
#define PCF8563_TIMER_CONTROL                         0x0E
#define PCF8563_TIMER_COUNTDOWN_VALUE                 0x0F

// 时钟输出速率定义
#define PCF8563_CLKOUT_FREQUENCY_OFF                  0x00
#define PCF8563_CLKOUT_FREQUENCY_32768_KHZ            0x80
#define PCF8563_CLKOUT_FREQUENCY_1024_HZ              0x81
#define PCF8563_CLKOUT_FREQUENCY_32_HZ                0x82
#define PCF8563_CLKOUT_FREQUENCY_1_HZ                 0x83

// 定时器时钟源定义
#define PCF8563_TIMER_SOURCE_CLOCK_FREQUENCY_OFF      0x00
#define PCF8563_TIMER_SOURCE_CLOCK_FREQUENCY_4096_HZ  0x80
#define PCF8563_TIMER_SOURCE_CLOCK_FREQUENCY_64_HZ    0x81
#define PCF8563_TIMER_SOURCE_CLOCK_FREQUENCY_1_HZ     0x82
#define PCF8563_TIMER_SOURCE_CLOCK_FREQUENCY_1_60_HZ  0x83

// 中断标志位定义
#define PCF8563_INTERRUPT_FLAG_TIE                    0x01
#define PCF8563_INTERRUPT_FLAG_AIE                    0x02
#define PCF8563_INTERRUPT_FLAG_TF                     0x04
#define PCF8563_INTERRUPT_FLAG_AF                     0x08
#define PCF8563_INTERRUPT_FLAG_TI_TP                  0x10

// 闹钟相关定义
#define PCF8563_ALARM_DISABLE                         0x80

typedef struct __PCF8563_DATETIME
{
  // 时钟/日历信息可靠
  uint8_t _VL;
  uint8_t seconds;
  uint8_t minutes;
  uint8_t hours;
  uint8_t days;
  uint8_t weekdays;
  uint8_t months;
  uint8_t years;
  uint8_t century;
} PCF8563_DATETIME;

/**
 * @brief 获取时间日期
 *
 * @param device_address  设备地址
 * @param datetime        日期时间结构体
 */
void pcf8563_get_datetime(uint8_t device_address, PCF8563_DATETIME *datetime);

/**
 * @brief 设置时间日期
 *
 * @param device_address  设备地址
 * @param datetime        日期时间结构体
 */
void pcf8563_set_datetime(uint8_t device_address, PCF8563_DATETIME *datetime);

/**
 * @brief 设置时钟输出
 *
 * @param device_address  设备地址
 * @param frequency       时钟速率，设置为PCF8563_CLKOUT_FREQUENCY_OFF关闭输出
 */
void pcf8563_set_clkout(uint8_t device_address, uint8_t frequency);

/**
 * @brief 设置倒计时
 *
 * @param device_address    设备地址
 * @param clock_frequency   时钟源速率，设置为PCF8563_TIMER_SOURCE_CLOCK_FREQUENCY_OFF禁用倒计时
 * @param value             递减数值，时钟源速率设置为PCF8563_TIMER_SOURCE_CLOCK_FREQUENCY_OFF时可为任意值
 */
void pcf8563_set_countdown(uint8_t device_address, uint8_t clock_frequency, uint8_t value);

/**
 * @brief 置位中断寄存器标志位
 *
 * @param device_address  设备地址
 * @param interrupt_flag  中断标志
 */
void pcf8563_set_interrupt_flag(uint8_t device_address, uint8_t interrupt_flag);

/**
 * @brief 清楚中断标志位
 *
 * @param device_address  设备地址
 * @param interrupt_flag  中断标志
 */
void pcf8563_clear_interrupt_flag(uint8_t device_address, uint8_t interrupt_flag);

/**
 * @brief 读取中断标志位
 *
 * @param device_address  设备地址
 * @param interrupt_flag  中断标志
 * @return uint8_t        中断标志
 */
uint8_t pcf8563_get_interrupt_flag(uint8_t device_address, uint8_t interrupt_flag);

/**
 * @brief 设置闹钟
 *
 * @param device_address  设备地址
 * @param minute          分钟，设置为PCF8563_ALARM_DISABLE禁用此项
 * @param hour            小时，设置为PCF8563_ALARM_DISABLE禁用此项
 * @param day             日期，设置为PCF8563_ALARM_DISABLE禁用此项
 * @param weekday         星期，设置为PCF8563_ALARM_DISABLE禁用此项
 */
void pcf8563_set_alarm(uint8_t device_address, uint8_t minute, uint8_t hour, uint8_t day, uint8_t weekday);

#endif // __PCF9563_H__
