#include <mcs51/8051.h>
#include "config.h"
#include "lcd-tft.h"

#define RED  		0xf800
#define BLUE 		0x001f
#define GREEN		0x07e0
#define WHITE		0xffff
#define BLACK		0x0000
#define YELLOW  0xFFE0

void main()
{
  lcd_init();
  LCD_LED = 1;

  lcd_full_screen(GREEN);
  while(1)
  {
    lcd_full_rect(42, 42, 42, 42, RED);
    delay(1000);
    lcd_full_rect(42, 42, 42, 42, WHITE);
    delay(1000);
    lcd_full_rect(42, 42, 42, 42, BLACK);
    delay(1000);
    lcd_full_rect(42, 42, 42, 42, YELLOW);
    delay(1000);
  }
}
