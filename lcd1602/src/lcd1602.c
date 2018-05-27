#include "lcd1602.h"

__bit lcd1602_status()
{
  DATA_PORT = 0xff;
  RS = 0;
  RW = 1;
  EN = 0;
  __nop();
  EN = 1;
  return (DATA_PORT & 0x80);
}

void lcd1602_write(unsigned char data, __bit type)
{
  while(lcd1602_status());
  RS = type;
  RW = 0;
  EN = 1;
  DATA_PORT = data;
  __nop(); __nop(); __nop(); __nop();
  EN = 0;
}

void lcd1602_clear()
{
  lcd1602_write(0x01, LCD1602_COMMAND);
}

void lcd1602_init()
{
  lcd1602_write(0x38, LCD1602_COMMAND);
  delay(5);
  lcd1602_write(0x38, LCD1602_COMMAND);
  delay(5);
  lcd1602_write(0x38, LCD1602_COMMAND);
  delay(5);
  lcd1602_write(0x38, LCD1602_COMMAND);
  lcd1602_write(0x08, LCD1602_COMMAND);
  lcd1602_write(0x01, LCD1602_COMMAND);
  lcd1602_write(0x06, LCD1602_COMMAND);
  delay(5);
  lcd1602_write(0x0c, LCD1602_COMMAND);
}
