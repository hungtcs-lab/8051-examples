#ifndef __ST7920_H__
#define __ST7920_H__

// RS 数据/指令 选择标志
#define ST7920_DATA    1
#define ST7920_COMMAND 0

__bit st7920_parallel_8bit_busy_flag();
void st7920_parallel_8bit_write(unsigned char data, __bit type);
void st7920_parallel_8bit_init();
void st7920_parallel_8bit_clear();
void st7920_parallel_8bit_print(unsigned char x, unsigned char y, unsigned char * content);

#endif
