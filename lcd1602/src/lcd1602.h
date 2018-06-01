#ifndef __LCD1602_H__
#define __LCD1602_H__

#define LCD1602_DATA    1
#define LCD1602_COMMAND 0

/**
 * 读忙标志位
 */
__bit lcd1602_busy_flag();

/**
 * 写数据或指令
 */
void lcd1602_write(unsigned char data, __bit type);

/**
 * 清屏指令
 */
void lcd1602_clear();

/**
 * 初始化设置指令
 */
void lcd1602_init();

/**
 * 自定义字符
 */
void lcd1602_custom_character(unsigned index, unsigned char *model);

/**
 * 打印字符串
 * @param x       [description]
 * @param y       [description]
 * @param content [description]
 */
void lcd1602_print(unsigned char x, unsigned char y, unsigned char *content);

#endif
