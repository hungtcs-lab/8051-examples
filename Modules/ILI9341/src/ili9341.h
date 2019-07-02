#ifndef __ILI9341_H__
#define __ILI9341_H__

#include <stdint.h>
#include "delay.h"
#include "config.h"

void ili9341_reset(void);
void ili9341_write_data(uint16_t data);
void ili9341_write_command(uint16_t command);
void ili9341_write_register(uint16_t address, uint16_t data);

void ili9341_set_region(uint16_t x, uint16_t y, uint16_t width, uint16_t height);
void ili9341_full(uint16_t color);

void ili9341_init(void);

#endif // __ILI9341_H__
