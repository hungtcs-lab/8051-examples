#ifndef __ST7920_H__
#define __ST7920_H__

// RS 数据/指令 选择标志
#define ST7920_DATA    1
#define ST7920_COMMAND 0

/**
 * 串行方式
 * 写指令或数据
 * @param data [description]
 * @param type [description]
 */
void st7920_serial_write(unsigned char data);
void st7920_serial_write_data(unsigned char data);
void st7920_serial_write_command(unsigned char data);

void st7920_parallel_4bit_write(unsigned char data, __bit type);

/**
 * 以8bit的方式写指令或数据
 * @param data [description]
 * @param type [description]
 */
void st7920_parallel_8bit_write(unsigned char data, __bit type);
void st7920_parallel_8bit_write(unsigned char data, __bit type);

#endif
