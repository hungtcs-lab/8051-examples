#include "oled.h"
#include "delay.h"
#include "dht22.h"
#include <mcs51/8051.h>

void main()
{
  uint8_t i;
  const char celsius_symbol[] = { 95 + 32, 'C', '\0' };
  DHT22MeasurementResult result;

  oled_init();
  oled_clear();

  while(1)
  {
    dht22_measuring(&result);
    if(result.state == 0)
    {
      oled_clear();

      i = 0;
      oled_put_chars_8x16(0, 0, "Temperature:");
      if(result.temperature < 0)
      {
        oled_put_chars_8x16(i++, 1, "-");
        result.temperature = -result.temperature;
      }
      oled_put_char_8x16(i++, 1, (result.temperature / 10) + 48);
      oled_put_char_8x16(i++, 1, (((int)result.temperature) % 10) + 48);
      oled_put_char_8x16(i++, 1, '.');
      oled_put_char_8x16(i++, 1, ((int)((result.temperature - ((int)result.temperature)) * 10)) + 48);
      oled_put_chars_8x16(i, 1, celsius_symbol);

      i=0;
      oled_put_chars_8x16(0, 2, "Humidity:");
      oled_put_char_8x16(i++, 3, (result.humidity / 10) + 48);
      oled_put_char_8x16(i++, 3, (((int)result.humidity) % 10) + 48);
      oled_put_char_8x16(i++, 3, '.');
      oled_put_char_8x16(i++, 3, ((int)((result.humidity - ((int)result.humidity)) * 10)) + 48);
      oled_put_chars_8x16(i, 3, "%");
    }
    else
    {
      oled_clear();
      oled_put_chars_8x16(0, 0, "Error:");
      if(result.state == 1) {
        oled_put_chars_8x16(0, 1, "No response");
      }
      else if(result.state == 1)
      {
        oled_put_chars_8x16(0, 1, "Checksum error");
      }
      oled_put_chars_8x16(0, 3, "  Retrying...");
    }
    delay_ms(5000);
  }
}
