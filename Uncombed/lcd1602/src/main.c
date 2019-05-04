#include <stdint.h>
#include <string.h>
#include <mcs51/8051.h>
#include "delay.h"
#include "lcd1602.h"

const unsigned char __data CENTIGRADE[] = { 0x18, 0x18, 0x07, 0x08, 0x08, 0x08, 0x07, 0x00 };

void setup()
{
  lcd1602_init();
  lcd1602_clear();

  // 注册自定义字符
  lcd1602_custom_character(0, CENTIGRADE);

  // 显示自定义字符
  lcd1602_write(0x80, LCD1602_COMMAND);
  lcd1602_write(0, LCD1602_DATA);

  // 直接显示字符串
  lcd1602_print(0, 2, "hello world!");
}

void loop()
{

}

void main(void)
{
  setup();
  while(1) loop();
}
