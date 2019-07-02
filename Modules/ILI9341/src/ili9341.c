#include "ili9341.h"

void ili9341_reset(void)
{
  ILI9341_RESET = 1;
	delay_ms(100);
  ILI9341_RESET = 0;
	delay_ms(500);
  ILI9341_RESET = 1;
	delay_ms(200);
}

void ili9341_write_data(uint16_t data)
{
  ILI9341_CS = 0;
  ILI9341_RD = 1;
  ILI9341_DC = 1;
  ILI9341_WR = 0;
  ILI9341_DATA_LOW = (uint8_t)data;
  ILI9341_DATA_HIGH = (uint8_t)(data >> 8);
  ILI9341_WR = 1;
  ILI9341_CS = 1;
}

void ili9341_write_command(uint16_t command)
{
  ILI9341_CS = 0;
  ILI9341_RD = 1;
  ILI9341_DC = 0;
  ILI9341_WR = 0;
  ILI9341_DATA_LOW = (uint8_t)command;
  ILI9341_DATA_HIGH = (uint8_t)(command >> 8);
  ILI9341_WR = 1;
  ILI9341_CS = 1;
}

void ili9341_write_register(uint16_t address, uint16_t data)
{
  ili9341_write_command(address);
  ili9341_write_data(data);
}

void ili9341_set_region(uint16_t x, uint16_t y, uint16_t width, uint16_t height)
{
  ili9341_write_command(0x2A00);
	ili9341_write_data(x>>8);
	ili9341_write_command(0x2A01);
	ili9341_write_data(x);

	ili9341_write_command(0x2A02);
	ili9341_write_data(width>>8);
	ili9341_write_command(0x2A03);
	ili9341_write_data(width);

	ili9341_write_command(0x2B00);
	ili9341_write_data(y>>8);
	ili9341_write_command(0x2B01);
	ili9341_write_data(y);

	ili9341_write_command(0x2B02);
	ili9341_write_data(height>>8);
	ili9341_write_command(0x2B03);
	ili9341_write_data(height);

	ili9341_write_command(0x2C00);
}

void ili9341_full(uint16_t color)
{
	uint16_t i, j;
  uint32_t index=0;
	ili9341_set_region(0, 0, 480 - 1, 800 - 1);
	for(i=0; i<800; i++)
	{
		for(j=0; j<480; j++)
    {
  		ili9341_write_data(color);
    }
	}
}

void ili9341_init(void)
{
  ili9341_reset();

	ili9341_write_command(0xff00);   ili9341_write_data(0x80);		//enable access command2
  ili9341_write_command(0xff01);   ili9341_write_data(0x09);		//enable access command2
  ili9341_write_command(0xff02);   ili9341_write_data(0x01);		//enable access command2
  ili9341_write_command(0xff80);   ili9341_write_data(0x80);		//enable access command2
  ili9341_write_command(0xff81);   ili9341_write_data(0x09);		//enable access command2
  ili9341_write_command(0xff03);   ili9341_write_data(0x01);		//
  ili9341_write_command(0xc5b1);   ili9341_write_data(0xA9);		//power control

  ili9341_write_command(0xc591);   ili9341_write_data(0x0F);               //power control
  ili9341_write_command(0xc0B4);   ili9341_write_data(0x50);

  //panel driving mode : column inversion

  //////	gamma
  ili9341_write_command(0xE100);   ili9341_write_data(0x00);
  ili9341_write_command(0xE101);   ili9341_write_data(0x09);
  ili9341_write_command(0xE102);   ili9341_write_data(0x0F);
  ili9341_write_command(0xE103);   ili9341_write_data(0x0E);
  ili9341_write_command(0xE104);   ili9341_write_data(0x07);
  ili9341_write_command(0xE105);   ili9341_write_data(0x10);
  ili9341_write_command(0xE106);   ili9341_write_data(0x0B);
  ili9341_write_command(0xE107);   ili9341_write_data(0x0A);
  ili9341_write_command(0xE108);   ili9341_write_data(0x04);
  ili9341_write_command(0xE109);   ili9341_write_data(0x07);
  ili9341_write_command(0xE10A);   ili9341_write_data(0x0B);
  ili9341_write_command(0xE10B);   ili9341_write_data(0x08);
  ili9341_write_command(0xE10C);   ili9341_write_data(0x0F);
  ili9341_write_command(0xE10D);   ili9341_write_data(0x10);
  ili9341_write_command(0xE10E);   ili9341_write_data(0x0A);
  ili9341_write_command(0xE10F);   ili9341_write_data(0x01);
  ili9341_write_command(0xE200);   ili9341_write_data(0x00);
  ili9341_write_command(0xE201);   ili9341_write_data(0x09);
  ili9341_write_command(0xE202);   ili9341_write_data(0x0F);
  ili9341_write_command(0xE203);   ili9341_write_data(0x0E);
  ili9341_write_command(0xE204);   ili9341_write_data(0x07);
  ili9341_write_command(0xE205);   ili9341_write_data(0x10);
  ili9341_write_command(0xE206);   ili9341_write_data(0x0B);
  ili9341_write_command(0xE207);   ili9341_write_data(0x0A);
  ili9341_write_command(0xE208);   ili9341_write_data(0x04);
  ili9341_write_command(0xE209);   ili9341_write_data(0x07);
  ili9341_write_command(0xE20A);   ili9341_write_data(0x0B);
  ili9341_write_command(0xE20B);   ili9341_write_data(0x08);
  ili9341_write_command(0xE20C);   ili9341_write_data(0x0F);
  ili9341_write_command(0xE20D);   ili9341_write_data(0x10);
  ili9341_write_command(0xE20E);   ili9341_write_data(0x0A);
  ili9341_write_command(0xE20F);   ili9341_write_data(0x01);
  ili9341_write_command(0xD900);   ili9341_write_data(0x4E);		//vcom setting

  ili9341_write_command(0xc181);   ili9341_write_data(0x66);		//osc=65HZ

  ili9341_write_command(0xc1a1);   ili9341_write_data(0x08);
  ili9341_write_command(0xc592);   ili9341_write_data(0x01);		//power control

  ili9341_write_command(0xc595);   ili9341_write_data(0x34);		//power control

  ili9341_write_command(0xd800);   ili9341_write_data(0x79);		//GVDD / NGVDD setting

  ili9341_write_command(0xd801);   ili9341_write_data(0x79);		//GVDD / NGVDD setting

  ili9341_write_command(0xc594);   ili9341_write_data(0x33);		//power control

  ili9341_write_command(0xc0a3);   ili9341_write_data(0x1B);       //panel timing setting
  ili9341_write_command(0xc582);   ili9341_write_data(0x83);		//power control

  ili9341_write_command(0xc481);   ili9341_write_data(0x83);		//source driver setting

  ili9341_write_command(0xc1a1);   ili9341_write_data(0x0E);
  ili9341_write_command(0xb3a6);   ili9341_write_data(0x20);
  ili9341_write_command(0xb3a7);   ili9341_write_data(0x01);
  ili9341_write_command(0xce80);   ili9341_write_data(0x85);		// GOA VST

  ili9341_write_command(0xce81);   ili9341_write_data(0x01); 	// GOA VST

  ili9341_write_command(0xce82);   ili9341_write_data(0x00);		// GOA VST

  ili9341_write_command(0xce83);   ili9341_write_data(0x84);		// GOA VST
  ili9341_write_command(0xce84);   ili9341_write_data(0x01);		// GOA VST
  ili9341_write_command(0xce85);   ili9341_write_data(0x00);		// GOA VST

  ili9341_write_command(0xcea0);   ili9341_write_data(0x18);		// GOA CLK
  ili9341_write_command(0xcea1);   ili9341_write_data(0x04);		// GOA CLK
  ili9341_write_command(0xcea2);   ili9341_write_data(0x03);		// GOA CLK
  ili9341_write_command(0xcea3);   ili9341_write_data(0x39);		// GOA CLK
  ili9341_write_command(0xcea4);   ili9341_write_data(0x00);		// GOA CLK
  ili9341_write_command(0xcea5);   ili9341_write_data(0x00);		// GOA CLK
  ili9341_write_command(0xcea6);   ili9341_write_data(0x00);		// GOA CLK
  ili9341_write_command(0xcea7);   ili9341_write_data(0x18);		// GOA CLK
  ili9341_write_command(0xcea8);   ili9341_write_data(0x03);		// GOA CLK
  ili9341_write_command(0xcea9);   ili9341_write_data(0x03);		// GOA CLK
  ili9341_write_command(0xceaa);   ili9341_write_data(0x3a);		// GOA CLK
  ili9341_write_command(0xceab);   ili9341_write_data(0x00);		// GOA CLK
  ili9341_write_command(0xceac);   ili9341_write_data(0x00);		// GOA CLK
  ili9341_write_command(0xcead);   ili9341_write_data(0x00);		// GOA CLK
  ili9341_write_command(0xceb0);   ili9341_write_data(0x18);		// GOA CLK
  ili9341_write_command(0xceb1);   ili9341_write_data(0x02);		// GOA CLK
  ili9341_write_command(0xceb2);   ili9341_write_data(0x03); 		// GOA CLK
  ili9341_write_command(0xceb3);   ili9341_write_data(0x3b);		// GOA CLK
  ili9341_write_command(0xceb4);   ili9341_write_data(0x00);		// GOA CLK
  ili9341_write_command(0xceb5);   ili9341_write_data(0x00);		// GOA CLK
  ili9341_write_command(0xceb6);   ili9341_write_data(0x00);		// GOA CLK
  ili9341_write_command(0xceb7);   ili9341_write_data(0x18);		// GOA CLK
  ili9341_write_command(0xceb8);   ili9341_write_data(0x01);		// GOA CLK
  ili9341_write_command(0xceb9);   ili9341_write_data(0x03);		// GOA CLK
  ili9341_write_command(0xceba);   ili9341_write_data(0x3c);		// GOA CLK
  ili9341_write_command(0xcebb);   ili9341_write_data(0x00);		// GOA CLK
  ili9341_write_command(0xcebc);   ili9341_write_data(0x00);		// GOA CLK
  ili9341_write_command(0xcebd);   ili9341_write_data(0x00);		// GOA CLK
  ili9341_write_command(0xcfc0);   ili9341_write_data(0x01);		// GOA ECLK
  ili9341_write_command(0xcfc1);   ili9341_write_data(0x01);		// GOA ECLK
  ili9341_write_command(0xcfc2);   ili9341_write_data(0x20); 		// GOA ECLK

  ili9341_write_command(0xcfc3);   ili9341_write_data(0x20); 		// GOA ECLK

  ili9341_write_command(0xcfc4);   ili9341_write_data(0x00); 		// GOA ECLK

  ili9341_write_command(0xcfc5);   ili9341_write_data(0x00); 		// GOA ECLK

  ili9341_write_command(0xcfc6);   ili9341_write_data(0x01); 		// GOA other options

  ili9341_write_command(0xcfc7);   ili9341_write_data(0x00);

  // GOA signal toggle option setting

  ili9341_write_command(0xcfc8);   ili9341_write_data(0x00); 		//GOA signal toggle option setting
  ili9341_write_command(0xcfc9);   ili9341_write_data(0x00);

  //GOA signal toggle option setting

  ili9341_write_command(0xcfd0);   ili9341_write_data(0x00);
  ili9341_write_command(0xcb80);   ili9341_write_data(0x00);
  ili9341_write_command(0xcb81);   ili9341_write_data(0x00);
  ili9341_write_command(0xcb82);   ili9341_write_data(0x00);
  ili9341_write_command(0xcb83);   ili9341_write_data(0x00);
  ili9341_write_command(0xcb84);   ili9341_write_data(0x00);
  ili9341_write_command(0xcb85);   ili9341_write_data(0x00);
  ili9341_write_command(0xcb86);   ili9341_write_data(0x00);
  ili9341_write_command(0xcb87);   ili9341_write_data(0x00);
  ili9341_write_command(0xcb88);   ili9341_write_data(0x00);
  ili9341_write_command(0xcb89);   ili9341_write_data(0x00);
  ili9341_write_command(0xcb90);   ili9341_write_data(0x00);
  ili9341_write_command(0xcb91);   ili9341_write_data(0x00);
  ili9341_write_command(0xcb92);   ili9341_write_data(0x00);
  ili9341_write_command(0xcb93);   ili9341_write_data(0x00);
  ili9341_write_command(0xcb94);   ili9341_write_data(0x00);
  ili9341_write_command(0xcb95);   ili9341_write_data(0x00);
  ili9341_write_command(0xcb96);   ili9341_write_data(0x00);
  ili9341_write_command(0xcb97);   ili9341_write_data(0x00);
  ili9341_write_command(0xcb98);   ili9341_write_data(0x00);
  ili9341_write_command(0xcb99);   ili9341_write_data(0x00);
  ili9341_write_command(0xcb9a);   ili9341_write_data(0x00);
  ili9341_write_command(0xcb9b);   ili9341_write_data(0x00);
  ili9341_write_command(0xcb9c);   ili9341_write_data(0x00);
  ili9341_write_command(0xcb9d);   ili9341_write_data(0x00);
  ili9341_write_command(0xcb9e);   ili9341_write_data(0x00);
  ili9341_write_command(0xcba0);   ili9341_write_data(0x00);
  ili9341_write_command(0xcba1);   ili9341_write_data(0x00);
  ili9341_write_command(0xcba2);   ili9341_write_data(0x00);
  ili9341_write_command(0xcba3);   ili9341_write_data(0x00);
  ili9341_write_command(0xcba4);   ili9341_write_data(0x00);
  ili9341_write_command(0xcba5);   ili9341_write_data(0x00);
  ili9341_write_command(0xcba6);   ili9341_write_data(0x00);
  ili9341_write_command(0xcba7);   ili9341_write_data(0x00);
  ili9341_write_command(0xcba8);   ili9341_write_data(0x00);
  ili9341_write_command(0xcba9);   ili9341_write_data(0x00);
  ili9341_write_command(0xcbaa);   ili9341_write_data(0x00);
  ili9341_write_command(0xcbab);   ili9341_write_data(0x00);
  ili9341_write_command(0xcbac);   ili9341_write_data(0x00);
  ili9341_write_command(0xcbad);   ili9341_write_data(0x00);
  ili9341_write_command(0xcbae);   ili9341_write_data(0x00);
  ili9341_write_command(0xcbb0);   ili9341_write_data(0x00);
  ili9341_write_command(0xcbb1);   ili9341_write_data(0x00);
  ili9341_write_command(0xcbb2);   ili9341_write_data(0x00);
  ili9341_write_command(0xcbb3);   ili9341_write_data(0x00);
  ili9341_write_command(0xcbb4);   ili9341_write_data(0x00);
  ili9341_write_command(0xcbb5);   ili9341_write_data(0x00);
  ili9341_write_command(0xcbb6);   ili9341_write_data(0x00);
  ili9341_write_command(0xcbb7);   ili9341_write_data(0x00);
  ili9341_write_command(0xcbb8);   ili9341_write_data(0x00);
  ili9341_write_command(0xcbb9);   ili9341_write_data(0x00);
  ili9341_write_command(0xcbc0);   ili9341_write_data(0x00);
  ili9341_write_command(0xcbc1);   ili9341_write_data(0x04);
  ili9341_write_command(0xcbc2);   ili9341_write_data(0x04);
  ili9341_write_command(0xcbc3);   ili9341_write_data(0x04);
  ili9341_write_command(0xcbc4);   ili9341_write_data(0x04);
  ili9341_write_command(0xcbc5);   ili9341_write_data(0x04);
  ili9341_write_command(0xcbc6);   ili9341_write_data(0x00);
  ili9341_write_command(0xcbc7);   ili9341_write_data(0x00);
  ili9341_write_command(0xcbc8);   ili9341_write_data(0x00);
  ili9341_write_command(0xcbc9);   ili9341_write_data(0x00);
  ili9341_write_command(0xcbca);   ili9341_write_data(0x00);
  ili9341_write_command(0xcbcb);   ili9341_write_data(0x00);
  ili9341_write_command(0xcbcc);   ili9341_write_data(0x00);
  ili9341_write_command(0xcbcd);   ili9341_write_data(0x00);
  ili9341_write_command(0xcbce);   ili9341_write_data(0x00);
  ili9341_write_command(0xcbd0);   ili9341_write_data(0x00);
  ili9341_write_command(0xcbd1);   ili9341_write_data(0x00);
  ili9341_write_command(0xcbd2);   ili9341_write_data(0x00);
  ili9341_write_command(0xcbd3);   ili9341_write_data(0x00);
  ili9341_write_command(0xcbd4);   ili9341_write_data(0x00);
  ili9341_write_command(0xcbd5);   ili9341_write_data(0x00);
  ili9341_write_command(0xcbd6);   ili9341_write_data(0x04);
  ili9341_write_command(0xcbd7);   ili9341_write_data(0x04);
  ili9341_write_command(0xcbd8);   ili9341_write_data(0x04);
  ili9341_write_command(0xcbd9);   ili9341_write_data(0x04);
  ili9341_write_command(0xcbda);   ili9341_write_data(0x04);
  ili9341_write_command(0xcbdb);   ili9341_write_data(0x00);
  ili9341_write_command(0xcbdc);   ili9341_write_data(0x00);
  ili9341_write_command(0xcbdd);   ili9341_write_data(0x00);
  ili9341_write_command(0xcbde);   ili9341_write_data(0x00);
  ili9341_write_command(0xcbe0);   ili9341_write_data(0x00);
  ili9341_write_command(0xcbe1);   ili9341_write_data(0x00);
  ili9341_write_command(0xcbe2);   ili9341_write_data(0x00);
  ili9341_write_command(0xcbe3);   ili9341_write_data(0x00);
  ili9341_write_command(0xcbe4);   ili9341_write_data(0x00);
  ili9341_write_command(0xcbe5);   ili9341_write_data(0x00);
  ili9341_write_command(0xcbe6);   ili9341_write_data(0x00);
  ili9341_write_command(0xcbe7);   ili9341_write_data(0x00);
  ili9341_write_command(0xcbe8);   ili9341_write_data(0x00);
  ili9341_write_command(0xcbe9);   ili9341_write_data(0x00);
  ili9341_write_command(0xcbf0);   ili9341_write_data(0xFF);
  ili9341_write_command(0xcbf1);   ili9341_write_data(0xFF);
  ili9341_write_command(0xcbf2);   ili9341_write_data(0xFF);
  ili9341_write_command(0xcbf3);   ili9341_write_data(0xFF);
  ili9341_write_command(0xcbf4);   ili9341_write_data(0xFF);
  ili9341_write_command(0xcbf5);   ili9341_write_data(0xFF);
  ili9341_write_command(0xcbf6);   ili9341_write_data(0xFF);
  ili9341_write_command(0xcbf7);   ili9341_write_data(0xFF);
  ili9341_write_command(0xcbf8);   ili9341_write_data(0xFF);
  ili9341_write_command(0xcbf9);   ili9341_write_data(0xFF);
  ili9341_write_command(0xcc80);   ili9341_write_data(0x00);
  ili9341_write_command(0xcc81);   ili9341_write_data(0x26);
  ili9341_write_command(0xcc82);   ili9341_write_data(0x09);
  ili9341_write_command(0xcc83);   ili9341_write_data(0x0B);
  ili9341_write_command(0xcc84);   ili9341_write_data(0x01);
  ili9341_write_command(0xcc85);   ili9341_write_data(0x25);
  ili9341_write_command(0xcc86);   ili9341_write_data(0x00);
  ili9341_write_command(0xcc87);   ili9341_write_data(0x00);
  ili9341_write_command(0xcc88);   ili9341_write_data(0x00);
  ili9341_write_command(0xcc89);   ili9341_write_data(0x00);
  ili9341_write_command(0xcc90);   ili9341_write_data(0x00);
  ili9341_write_command(0xcc91);   ili9341_write_data(0x00);
  ili9341_write_command(0xcc92);   ili9341_write_data(0x00);
  ili9341_write_command(0xcc93);   ili9341_write_data(0x00);
  ili9341_write_command(0xcc94);   ili9341_write_data(0x00);
  ili9341_write_command(0xcc95);   ili9341_write_data(0x00);
  ili9341_write_command(0xcc96);   ili9341_write_data(0x00);
  ili9341_write_command(0xcc97);   ili9341_write_data(0x00);
  ili9341_write_command(0xcc98);   ili9341_write_data(0x00);
  ili9341_write_command(0xcc99);   ili9341_write_data(0x00);
  ili9341_write_command(0xcc9a);   ili9341_write_data(0x00);
  ili9341_write_command(0xcc9b);   ili9341_write_data(0x26);
  ili9341_write_command(0xcc9c);   ili9341_write_data(0x0A);
  ili9341_write_command(0xcc9d);   ili9341_write_data(0x0C);
  ili9341_write_command(0xcc9e);   ili9341_write_data(0x02);
  ili9341_write_command(0xcca0);   ili9341_write_data(0x25);
  ili9341_write_command(0xcca1);   ili9341_write_data(0x00);
  ili9341_write_command(0xcca2);   ili9341_write_data(0x00);
  ili9341_write_command(0xcca3);   ili9341_write_data(0x00);
  ili9341_write_command(0xcca4);   ili9341_write_data(0x00);
  ili9341_write_command(0xcca5);   ili9341_write_data(0x00);
  ili9341_write_command(0xcca6);   ili9341_write_data(0x00);
  ili9341_write_command(0xcca7);   ili9341_write_data(0x00);
  ili9341_write_command(0xcca8);   ili9341_write_data(0x00);
  ili9341_write_command(0xcca9);   ili9341_write_data(0x00);
  ili9341_write_command(0xccaa);   ili9341_write_data(0x00);
  ili9341_write_command(0xccab);   ili9341_write_data(0x00);
  ili9341_write_command(0xccac);   ili9341_write_data(0x00);
  ili9341_write_command(0xccad);   ili9341_write_data(0x00);
  ili9341_write_command(0xccae);   ili9341_write_data(0x00);
  ili9341_write_command(0xccb0);   ili9341_write_data(0x00);
  ili9341_write_command(0xccb1);   ili9341_write_data(0x25);
  ili9341_write_command(0xccb2);   ili9341_write_data(0x0C);
  ili9341_write_command(0xccb3);   ili9341_write_data(0x0A);
  ili9341_write_command(0xccb4);   ili9341_write_data(0x02);
  ili9341_write_command(0xccb5);   ili9341_write_data(0x26);
  ili9341_write_command(0xccb6);   ili9341_write_data(0x00);
  ili9341_write_command(0xccb7);   ili9341_write_data(0x00);
  ili9341_write_command(0xccb8);   ili9341_write_data(0x00);
  ili9341_write_command(0xccb9);   ili9341_write_data(0x00);
  ili9341_write_command(0xccc0);   ili9341_write_data(0x00);
  ili9341_write_command(0xccc1);   ili9341_write_data(0x00);
  ili9341_write_command(0xccc2);   ili9341_write_data(0x00);
  ili9341_write_command(0xccc3);   ili9341_write_data(0x00);
  ili9341_write_command(0xccc4);   ili9341_write_data(0x00);
  ili9341_write_command(0xccc5);   ili9341_write_data(0x00);
  ili9341_write_command(0xccc6);   ili9341_write_data(0x00);
  ili9341_write_command(0xccc7);   ili9341_write_data(0x00);
  ili9341_write_command(0xccc8);   ili9341_write_data(0x00);
  ili9341_write_command(0xccc9);   ili9341_write_data(0x00);
  ili9341_write_command(0xccca);   ili9341_write_data(0x00);
  ili9341_write_command(0xcccb);   ili9341_write_data(0x25);
  ili9341_write_command(0xcccc);   ili9341_write_data(0x0B);
  ili9341_write_command(0xcccd);   ili9341_write_data(0x09);
  ili9341_write_command(0xccce);   ili9341_write_data(0x01);
  ili9341_write_command(0xccd0);   ili9341_write_data(0x26);
  ili9341_write_command(0xccd1);   ili9341_write_data(0x00);
  ili9341_write_command(0xccd2);   ili9341_write_data(0x00);
  ili9341_write_command(0xccd3);   ili9341_write_data(0x00);
  ili9341_write_command(0xccd4);   ili9341_write_data(0x00);
  ili9341_write_command(0xccd5);   ili9341_write_data(0x00);
  ili9341_write_command(0xccd6);   ili9341_write_data(0x00);
  ili9341_write_command(0xccd7);   ili9341_write_data(0x00);
  ili9341_write_command(0xccd8);   ili9341_write_data(0x00);
  ili9341_write_command(0xccd9);   ili9341_write_data(0x00);
  ili9341_write_command(0xccda);   ili9341_write_data(0x00);
  ili9341_write_command(0xccdb);   ili9341_write_data(0x00);
  ili9341_write_command(0xccdc);   ili9341_write_data(0x00);
  ili9341_write_command(0xccdd);   ili9341_write_data(0x00);
  ili9341_write_command(0xccde);   ili9341_write_data(0x00);
  ili9341_write_command(0x3A00);   ili9341_write_data(0x55);

  ili9341_write_command(0x1100);
  delay_ms(100);
  ili9341_write_command(0x2900);
  delay_ms(50);
  ili9341_write_command(0x2C00);
  ili9341_write_command(0x2A00);  ili9341_write_data(0x00);
  ili9341_write_command(0x2A01);  ili9341_write_data(0x00);
  ili9341_write_command(0x2A02);  ili9341_write_data(0x01);
  ili9341_write_command(0x2A03);  ili9341_write_data(0xe0);
  ili9341_write_command(0x2B00);  ili9341_write_data(0x00);
  ili9341_write_command(0x2B01);  ili9341_write_data(0x00);
  ili9341_write_command(0x2B02);  ili9341_write_data(0x03);
  ili9341_write_command(0x2B03);  ili9341_write_data(0x20);

  ili9341_full(0xFFFF);
}
