#ifndef __OLED_H__
#define __OLED_H__

#include "spi.h"
#include "delay.h"
#include "stdint.h"
#include "characters.h"

#define OLED_WIDTH  128
#define OLED_HEIGHT 64

void oled_reset(void);
void oled_send_data(uint8_t data);
void oled_send_command(uint8_t command);
void oled_set_position(uint8_t x, uint8_t y);
void oled_init(void);
void oled_full(void);
void oled_clear(void);
void oled_put_char_8x16(uint8_t x, uint8_t y, char character);
void oled_put_chars_8x16(uint8_t x, uint8_t y, const char *characters);

#endif // __OLED_H__
