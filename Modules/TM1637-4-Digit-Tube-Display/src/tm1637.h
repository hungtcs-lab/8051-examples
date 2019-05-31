#ifndef __TM1637_H__
#define __TM1637_H__

#include <stdint.h>
#include "iic.h"


#define TM1637_ADDR_AUTO_INCREASE   0x40
#define TM1637_ADDR_FIXED           0x44
#define TM1637_ADDR_START           0xC0

#define TM1637_BRIGHTNESS_LEVEL_1   (0x88 | 0x00)
#define TM1637_BRIGHTNESS_LEVEL_2   (0x88 | 0x01)
#define TM1637_BRIGHTNESS_LEVEL_3   (0x88 | 0x02)
#define TM1637_BRIGHTNESS_LEVEL_4   (0x88 | 0x03)
#define TM1637_BRIGHTNESS_LEVEL_5   (0x88 | 0x04)
#define TM1637_BRIGHTNESS_LEVEL_6   (0x88 | 0x05)
#define TM1637_BRIGHTNESS_LEVEL_7   (0x88 | 0x06)
#define TM1637_BRIGHTNESS_LEVEL_8   (0x88 | 0x07)
#define tm1637_set_brightness(brightness_level) do{ tm1637_brightness_level = brightness_level; } while(0)

extern uint8_t tm1637_brightness_level;

void tm1637_send_byte(uint8_t data);

void tm1637_display(uint8_t* codes);
void tm1637_display_bit(uint8_t bit, uint8_t code);
void tm1637_clear_display();

#endif // __TM1637_H__
