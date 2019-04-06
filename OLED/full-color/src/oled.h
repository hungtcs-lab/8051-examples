#ifndef __OLED_H__
#define __OLED_H__

#include "stdint.h"
#include "spi.h"
#include "delay.h"

#define OLED_WIDTH  128
#define OLED_HEIGHT 64

// typedef struct __OLED {
//   unsigned char x;
// } OLED;

void oled_reset(void);
void oled_send_data(uint8_t data);
void oled_send_command(uint8_t command);
void oled_set_position(uint8_t x, uint8_t y);
void oled_init(void);
void oled_clear(void);
void oled_full(void);


#endif // __OLED_H__
