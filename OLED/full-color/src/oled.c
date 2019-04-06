#include "oled.h"

void oled_reset()
{
  OLED_RESET = 0;
  delay_ms(50);
  OLED_RESET = 1;
}

void oled_send_data(uint8_t data)
{
  SPI_CS = 0;
  OLED_DC = 1;
  spi_read_write(data);
  SPI_CS = 1;
}

void oled_send_command(uint8_t command)
{
  SPI_CS = 0;
  OLED_DC = 0;
  spi_read_write(command);
  SPI_CS = 1;
}

void oled_set_position(uint8_t x, uint8_t y)
{
  oled_send_command(0xb0 + y);
  oled_send_command((x & 0x0f) | 0x00);
  oled_send_command(((x & 0xf0) >> 4) | 0x10);
}

void oled_init(void)
{
  SPI_CS = 1;
  SPI_SCK = 1;
  oled_reset();

  oled_send_command(0xAE); // 关闭显示
  oled_send_command(0x00); // set low column address
  oled_send_command(0x10); // set high column address
  oled_send_command(0x40); // set display start line
  // oled_send_command(0x81); // 设置对比度命令
  // oled_send_command(0x00);
  oled_send_command(0xA1); // 设置细分重映射 (0xA1正常,0xA0左右反置)
  oled_send_command(0xC8); // 设置列输出扫描方向 (0xC8正常,0xC0上下反置)
  oled_send_command(0xA6); // 设置正常/反向 (0xA6正常显示, 0xA7反向显示)
  oled_send_command(0xA8); // 设置多路复用比率
  oled_send_command(0x3F);
  oled_send_command(0xD3); // 设置显示偏移(垂直偏移)
  oled_send_command(0x00);
  oled_send_command(0xD5); // 设置显示时钟分频
  oled_send_command(0x80);
  oled_send_command(0xD9); // 设置预充电期
  oled_send_command(0xF1); // 将预充电设置为15个时钟并将其放电设置为1个时钟
  oled_send_command(0xDA); // 设置COM引脚硬件配置
  oled_send_command(0x12); // 启用备用COM引脚配置
  oled_send_command(0xDB); // 设置Vcomh取消选择级别
  oled_send_command(0x00); // ~ 0.65 x VCC
  oled_send_command(0x20); // 设置内存寻址模式
  oled_send_command(0x02); // 页面寻址模式
  oled_send_command(0x8d); // 充电凹凸设置
  oled_send_command(0x14); // 在显示期间启用电荷泵
  oled_send_command(0xA4); // entire display on
  oled_send_command(0xA6); // set Normal display
  oled_send_command(0xaf); // 开启显示
  oled_set_position(0, 0);
}

void oled_clear(void)
{
  uint8_t y, x;

  for (y = 0; y < 8; y++)
  {
    oled_send_command(0xb0 + y);
    oled_send_command(0x01);
    oled_send_command(0x10);
    for (x = 0; x < OLED_WIDTH; x++)
    {
      oled_send_data(0x00);
    }
  }
}

void oled_full(void)
{
  uint8_t y, x;

  for (y = 0; y < 8; y++)
  {
    oled_send_command(0xb0 + y);
    oled_send_command(0x01);
    oled_send_command(0x10);
    for (x = 0; x < OLED_WIDTH; x++)
    {
      oled_send_data(0xFF);
    }
  }
}
