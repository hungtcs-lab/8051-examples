#ifndef __LCD_TFT_H__
#define __LCD_TFT_H__

#include <spi.h>
#include <delay.h>

#define COMMAND_SLEEP_EXIT          0x11
#define COMMAND_CASET               0x2A
#define COMMAND_RASET               0x2B
#define COMMAND_RAMWR               0x2C
#define COMMAND_DISPON              0x29
#define COMMAND_MADCTL              0x36
#define COMMAND_COLMOD              0x3A
#define COMMAND_FRMCTR1             0xB1
#define COMMAND_FRMCTR2             0xB2
#define COMMAND_FRMCTR3             0xB3
#define COMMAND_INVCTR              0xB4
#define COMMAND_PWCTR1              0xC0
#define COMMAND_PWCTR2              0xC1
#define COMMAND_PWCTR3              0xC2
#define COMMAND_PWCTR4              0xC3
#define COMMAND_PWCTR5              0xC4
#define COMMAND_VMCTR1              0xC5
#define COMMAND_GMCTRP1             0xE0
#define COMMAND_GMCTRN1             0xE1

void lcd_write_data(unsigned char data)
{
  SPI_CS = 0;
  LCD_RS = 1;
  spi_write(data);
  SPI_CS = 1;
}

void lcd_write_data_16bit(unsigned int data)
{
  SPI_CS = 0;
  LCD_RS = 1;
  spi_write(data >> 8);
  spi_write(data);
  SPI_CS = 1;
}

void lcd_write_command(unsigned char command)
{
  SPI_CS = 0;
  LCD_RS = 0;
  spi_write(command);
  SPI_CS = 1;
}

void lcd_reset()
{
  LCD_RESET = 0;
  delay(100);
  LCD_RESET = 1;
  delay(100);
}

void lcd_init()
{
  lcd_reset();

  lcd_write_command(COMMAND_SLEEP_EXIT);
  delay(120);

  lcd_write_command(COMMAND_FRMCTR1);
  lcd_write_data(0x01);
	lcd_write_data(0x2C);
	lcd_write_data(0x2D);

	lcd_write_command(COMMAND_FRMCTR2);   // 0xB2 in idle mode 8 colors
	lcd_write_data(0x01);
	lcd_write_data(0x2C);
	lcd_write_data(0x2D);

	lcd_write_command(COMMAND_FRMCTR3);   // 0xB3 in partial mode full colors
	lcd_write_data(0x01);
	lcd_write_data(0x2C);
	lcd_write_data(0x2D);
	lcd_write_data(0x01);
	lcd_write_data(0x2C);
	lcd_write_data(0x2D);

	lcd_write_command(COMMAND_INVCTR);   // 0xB4 display Inversion control, Column inversion
	lcd_write_data(0x07);

	//ST7735R Power Sequence
	lcd_write_command(COMMAND_PWCTR1);   // 0xC0 power control setting
	lcd_write_data(0xA2);
	lcd_write_data(0x02);
	lcd_write_data(0x84);

	lcd_write_command(COMMAND_PWCTR2);   // 0xC1 power control setting
	lcd_write_data(0xC5);

	lcd_write_command(COMMAND_PWCTR3);   // 0xC2 in normal mode full colors
	lcd_write_data(0x0A);
	lcd_write_data(0x00);

	lcd_write_command(COMMAND_PWCTR4);   // 0xC3 in idle mode 8 colors
	lcd_write_data(0x8A);
	lcd_write_data(0x2A);

	lcd_write_command(COMMAND_PWCTR5);   // 0xC4 in partial mode full colors
	lcd_write_data(0x8A);
	lcd_write_data(0xEE);

	lcd_write_command(COMMAND_VMCTR1);   // VCOM control 1
	lcd_write_data(0x0E);

	lcd_write_command(COMMAND_MADCTL);   // mempry data access control
							// MX, MY, RGB mode
	lcd_write_data(0xC8);

	//ST7735R Gamma Sequence
	lcd_write_command(COMMAND_GMCTRP1);
	lcd_write_data(0x0f);
	lcd_write_data(0x1a);
	lcd_write_data(0x0f);
	lcd_write_data(0x18);
	lcd_write_data(0x2f);
	lcd_write_data(0x28);
	lcd_write_data(0x20);
	lcd_write_data(0x22);
	lcd_write_data(0x1f);
	lcd_write_data(0x1b);
	lcd_write_data(0x23);
	lcd_write_data(0x37);
	lcd_write_data(0x00);
	lcd_write_data(0x07);
	lcd_write_data(0x02);
	lcd_write_data(0x10);

	lcd_write_command(COMMAND_GMCTRN1);
	lcd_write_data(0x0f);
	lcd_write_data(0x1b);
	lcd_write_data(0x0f);
	lcd_write_data(0x17);
	lcd_write_data(0x33);
	lcd_write_data(0x2c);
	lcd_write_data(0x29);
	lcd_write_data(0x2e);
	lcd_write_data(0x30);
	lcd_write_data(0x30);
	lcd_write_data(0x39);
	lcd_write_data(0x3f);
	lcd_write_data(0x00);
	lcd_write_data(0x07);
	lcd_write_data(0x03);
	lcd_write_data(0x10);

	lcd_write_command(COMMAND_CASET);
	lcd_write_data(0x00);
	lcd_write_data(0x00+2);
	lcd_write_data(0x00);
	lcd_write_data(0x80+2);

	lcd_write_command(COMMAND_RASET);
	lcd_write_data(0x00);
	lcd_write_data(0x00+3);
	lcd_write_data(0x00);
	lcd_write_data(0x80+3);

	lcd_write_command(0xF0); //Enable test command
	lcd_write_data(0x01);
	lcd_write_command(0xF6); //Disable ram power save mode
	lcd_write_data(0x00);

	lcd_write_command(COMMAND_COLMOD); //65k mode
	lcd_write_data(0x05);


	lcd_write_command(COMMAND_DISPON);
}

void lcd_set_region(unsigned int x, unsigned int y, unsigned int width, unsigned int height)
{
	lcd_write_command(COMMAND_CASET);
	lcd_write_data(0x00);
	lcd_write_data(x + 2);
	lcd_write_data(0x00);
	lcd_write_data(x + width +1);

	lcd_write_command(COMMAND_RASET);
	lcd_write_data(0x00);
	lcd_write_data(y + 3);
	lcd_write_data(0x00);
	lcd_write_data(y + height +2);

	lcd_write_command(COMMAND_RAMWR);
}

void lcd_full_screen(unsigned int color)
{
	unsigned char i, j;
	lcd_set_region(0, 0, 128, 128);
	for (i=0; i<128; i++)
	{
    for (j=0; j<128; j++)
		{
      lcd_write_data_16bit(color);
		}
	}
}

void lcd_full_rect(unsigned char x, unsigned char y, unsigned char width, unsigned char height, unsigned int color)
{
	unsigned char i, j;
	lcd_set_region(x, y, width, height);
	for (i=0; i<height; i++)
	{
    for (j=0; j<width; j++)
		{
      lcd_write_data_16bit(color);
		}
	}
}

#endif