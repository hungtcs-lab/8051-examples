#include <string.h>
#include "defines.h"
#include "lcd1602.h"
#include "delay.h"

__bit lcd1602_busy_flag()
{
  LCD1602_DATA_PORT = 0xff;
  LCD1602_RS = 0;
  LCD1602_RW = 1;
  LCD1602_EN = 0;
  __nop();
  LCD1602_EN = 1;
  return (LCD1602_DATA_PORT & 0x80);
}

void lcd1602_write(unsigned char data, __bit type)
{
  while(!lcd1602_busy_flag());
  LCD1602_RS = type;
  LCD1602_RW = 0;
  LCD1602_EN = 1;
  LCD1602_DATA_PORT = data;
  __nop(); __nop(); __nop(); __nop();
  LCD1602_EN = 0;
}

void lcd1602_clear()
{
  lcd1602_write(0x01, LCD1602_COMMAND);
}

void lcd1602_init()
{
  // 清屏
  delay(5);
  lcd1602_write(0x01, LCD1602_COMMAND);
  delay(5);
  // 光标复位
  lcd1602_write(0x03, LCD1602_COMMAND);
  delay(5);
  // 光标右移，不移屏
  lcd1602_write(0x06, LCD1602_COMMAND);
  delay(5);
  // 开显示，开光标，光标闪烁
  // lcd1602_write(0x0e, LCD1602_COMMAND);
  lcd1602_write(0x0C, LCD1602_COMMAND);
  delay(1);
  // 光标自动右移
  lcd1602_write(0x14, LCD1602_COMMAND);
  delay(1);
  // 8位并行，两行显示，5*7字符大小
  lcd1602_write(0x38, LCD1602_COMMAND);
  delay(1);
}

void lcd1602_custom_character(unsigned index, unsigned char model[])
{
  unsigned char i;
  lcd1602_write((0x40 + index * 8), LCD1602_COMMAND);
  for(i=0; i<8; i++)
  {
    lcd1602_write(model[i], LCD1602_DATA);
  }
}

void lcd1602_print(unsigned char x, unsigned char y, unsigned char *content)
{
  unsigned char i, address;
  // 计算地址
  if(y==1)
    address = 0x80 + x;
  else if(y==2)
    address = 0xC0 + x;
  else
    return;

  lcd1602_write(address, LCD1602_COMMAND);
  for(i=0; i<strlen(content); i++)
  {
    lcd1602_write(content[i], LCD1602_DATA);
  }
}
