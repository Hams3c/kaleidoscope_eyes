#include <Adafruit_NeoPixel.h>
#ifdef __AVR_ATtiny85__ // Trinket, Gemma, etc.
  #include <avr/power.h>
#endif

#define PIN 0

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(32, PIN);

void setup()
{
  #ifdef __AVR_ATtiny85__ // Trinket, Gemma, etc.
    if(F_CPU == 16000000) clock_prescale_set(clock_div_1);
  #endif

  pixels.begin();
  pixels.setBrightness(60);
}

void ferrisWheel(uint32_t color)
{
  for (uint8_t i=0; i < 16; i++)
  {
    pixels.setPixelColor(i,color);
    pixels.setPixelColor(31-i, color); // Second eye (flipped)
    pixels.show();
    // if( (offset + i) < 0) c = color; // 2 pixels on...
    delay(30);
  }

  return true;
}

// uint32_t colorArr[] = {0xFF0000, 0x00FF00};//, 0x0000FF};//, 0xFFFF00, 0x00FFFF};
uint32_t customColor = 0xFF0000;
int arrIndex = 0;

void loop()
{
  ferrisWheel(customColor);
  arrIndex++;

  customColor >>= 8;
  if(!customColor) customColor = 0xFF0000; // Reset to red
}
