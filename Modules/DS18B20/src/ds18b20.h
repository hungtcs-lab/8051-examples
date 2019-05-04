#ifndef __DS18B20_H__
#define __DS18B20_H__

// 分辨率
// 09: Math.pow(2, -1)   0.5
// 10: Math.pow(2, -2)   0.25
// 11: Math.pow(2, -3)   0.125
// 12: Math.pow(2, -4)   0.0625

#include "delay.h"
#include "config.h"
#include <stdint.h>
#include <string.h>

// 功能命令
#define CONVERT_T                   0x44 // 温度转换
#define RECALL_EEPROM               0xB8 // 将存储在非易失性存储器中的值调用到暂存器（温度触发器）。
#define COPY_SCRATCHPAD             0x48 // 复制暂存器
#define READ_SCRATCHPAD             0xBE // 读取暂存器
#define WRITE_SCRATCHPAD            0x4E // 写入暂存器
#define READ_POWER_SUPPLY           0xB4 // 读取供电方式

// ROM操作命令
#define READ_ROM                    0x33 // 读取ROM
#define SKIP_ROM                    0xCC // 跳过ROM
#define MATCH_ROM                   0x55 // 匹配ROM
#define SEARCH_ROM                  0xF0 // 搜索ROM
#define ALARM_SEARCH                0xEC // 警报搜索

#define DS18B20_RESOLUTION_9_BIT    0
#define DS18B20_RESOLUTION_10_BIT   1
#define DS18B20_RESOLUTION_11_BIT   2
#define DS18B20_RESOLUTION_12_BIT   3

// 移植需根据实际情况修改次宏定义
#define ds18b20_delay_10us()        __nop(); __nop(); __nop(); __nop(); __nop(); __nop(); __nop(); __nop(); __nop()
#define ds18b20_delay_50us()        ds18b20_delay_10us(); ds18b20_delay_10us(); ds18b20_delay_10us(); ds18b20_delay_10us(); ds18b20_delay_10us()
#define ds18b20_delay_100us()       ds18b20_delay_50us(); ds18b20_delay_50us()
#define ds18b20_delay_500us()       ds18b20_delay_100us(); ds18b20_delay_100us(); ds18b20_delay_100us(); ds18b20_delay_100us(); ds18b20_delay_100us()

typedef struct __DS18B20_ROM
{
  uint8_t crc;
  uint8_t family_code;
  uint8_t serial_number[6];
} DS18B20_ROM;

uint8_t ds18b20_init(void);
uint8_t ds18b20_read_byte();
void ds18b20_write_byte(uint8_t data);

uint8_t ds18b20_read_rom(DS18B20_ROM *rom);
uint8_t ds18b20_measuring(float *temperature, uint8_t resolution);

#endif // __DS18B20_H__
