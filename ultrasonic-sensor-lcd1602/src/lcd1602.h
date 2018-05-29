#ifndef __LCD1602_H__
#define __LCD1602_H__

#define LCD1602_DATA    1
#define LCD1602_COMMAND 0

__bit lcd1602_status();
void lcd1602_write(unsigned char data, __bit type);
void lcd1602_clear();
void lcd1602_init();

#endif
