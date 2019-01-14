#include <mcs51/8051.h>
#include "config.h"
#include "lcd-tft.h"

#define RED  		0xf800
#define BLACK		0x0000

void display_text(unsigned int color)
{
  lcd_display_ascii8_16(10,10, "Hello!", color);
  lcd_display_ascii8_16(10,26, "HungTCS", color);
  lcd_display_ascii8_16(10,42, "TFT LCD 1.44'", color);
  lcd_display_ascii8_16(10,58, "ST7735", color);
  lcd_display_ascii8_16(10,74, "6K Colors", color);
  lcd_display_ascii8_16(10,90, "2019.01.14", color);
}

void main()
{
  lcd_init();
  LCD_LED = 1;
  lcd_full_screen(BLACK);
  display_text(RED);
  while(1);
}