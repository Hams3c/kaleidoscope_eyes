#include <Adafruit_NeoPixel.h>
#ifdef __AVR_ATtiny85__ // Trinket, Gemma, etc.
    #include <avr/power.h>
#endif

// #ifdef __AVR_ATtiny85__ // Trinket, Gemma, etc.
//   if(F_CPU == 16000000) clock_prescale_set(clock_div_1);
// #endif

class MyNeoPixelClass : public Adafruit_NeoPixel
{
    public:

    uint32_t Color1, Color2;  // What colors are in use
    uint16_t Index;  // current step within the pattern

    // Constructor - calls base-class constructor to initialize discs
    MyNeoPixelClass(uint16_t pixels, uint8_t pin)
    :Adafruit_NeoPixel(pixels, pin) {};

    // Input a value 0 to 255 to get a color value.
    // The colours are a transition r - g - b - back to r.
    uint32_t Wheel(byte WheelPos)
    {
        WheelPos = 255 - WheelPos;
        if(WheelPos < 85)
        {
            return Color(255 - WheelPos * 3, 0, WheelPos * 3);
        }
        else if(WheelPos < 170)
        {
            WheelPos -= 85;
            return Color(0, WheelPos * 3, 255 - WheelPos * 3);
        }
        else
        {
            WheelPos -= 170;
            return Color(WheelPos * 3, 255 - WheelPos * 3, 0);
        }
    }

    // Return color, dimmed by 75% (used by scanner)
    uint32_t DimColor(uint32_t color)
    {
        uint32_t dimColor = Color(Red(color) >> 1, Green(color) >> 1, Blue(color) >> 1);
        return dimColor;
    }

    // Returns the Red component of a 32-bit color
    uint8_t Red(uint32_t color)
    {
        return (color >> 16) & 0xFF;
    }

    // Returns the Green component of a 32-bit color
    uint8_t Green(uint32_t color)
    {
        return (color >> 8) & 0xFF;
    }

    // Returns the Blue component of a 32-bit color
    uint8_t Blue(uint32_t color)
    {
        return color & 0xFF;
    }

    void ferrisWheel(uint32_t color)
    {
        for (uint8_t i=0; i < 16; i++)
        {
            setPixelColor(i, color);
            setPixelColor(31-i, color); // Second eye (flipped)
            show();
            // if( (offset + i) < 0) c = color; // 2 pixels on...
            delay(30);
        }
    }

    // Initialize for a INFINITY
    void aInfinity(uint32_t color)
    {
        setBrightness(100);
        for (int i = 4; i < 16; i++)
        {
            setPixelColor(i, color);
            delay(30);
            show();
        }

        for (int i = 0; i < 4; i++)
        {
            setPixelColor(i, color);
            delay(30);
            show();
        }

        for (int i = 28; i > 21; i--)
        {
            setPixelColor(i, color);
            delay(30);
            show();
        }

        for (int i = 21; i > 15; i--)
        {
            setPixelColor(i, color);
            delay(30);
            show();
        }

        for (int i = 31; i > 28; i--)
        {
            setPixelColor(i, color);
            delay(30);
            show();
        }
    }

    void RainbowCycle()
    {
        for(int i=0; i < numPixels(); i++)
        {
            uint32_t color = Wheel(((i * 256 / numPixels())) & 255);
            setPixelColor(i, color);
            setPixelColor(31-i, color); // Second eye (flipped)
            show();
            // if( (offset + i) < 0) c = color; // 2 pixels on...
            delay(30);
        }
    }

    void TheaterChase(uint32_t color1, uint32_t color2)
    {
        for(int i=0; i < numPixels(); i++)
        {
            if ((i+Index) % 3 == 0)
            {
                setPixelColor(i, color1);
                setPixelColor((numPixels()-i), color1);
            }
            else
            {
                setPixelColor(i, color2);
                setPixelColor(numPixels()-i, color2);
            }
        }
        show();
        delay(50);
        Index++;
    }

    void FadeAndBlink(uint32_t color)
    {
        for (int i=0; i < numPixels(); i++)
        {
            setPixelColor(i, Color1);
        }
        show();
        delay(1000);

        // i'm being lazy and just adding another loop around this
        for (int i=0; i < 5; i++)
        {
            for (int j=0; j < numPixels(); j++)
            {
                setPixelColor(j, DimColor(getPixelColor(j)));
                show();
            }
        }
    }

    void Scanner(uint32_t color1)
    {
        uint16_t TotalSteps = (numPixels() - 1) * 2;

        for (int i = 0; i < numPixels(); i++)
        {
            if (i == Index) // first half of the scan
            {
                setPixelColor(i, color1);
            }
            else if (i == TotalSteps - Index) // The return trip.
            {
                setPixelColor(i, color1);
            }
            else  // fade to black
            {
                setPixelColor(i, DimColor(getPixelColor(i)));
            }
        }
        show();
        Index++;

        if (Index == numPixels())
        {
            Index = 0;
        }
    }

    void Strobe(uint32_t color)
    {
        for (int i=0; i < numPixels(); i++)
        {
            setPixelColor(i, Color1);
        }
        show();
        delay(30);
    }

    void Fade(uint32_t color)
    {
        uint8_t brightness = 0;

        while (brightness != 100)
        {
            for (int i=0; i < numPixels(); i++)
            {
                setBrightness(brightness);
                setPixelColor(i, Color1);
            }
            show();
            brightness += 1;
        }

        while (brightness != 0)
        {
            for (int i=0; i < numPixels(); i++)
            {
                setBrightness(brightness);
                setPixelColor(i, Color1);
            }
            show();
            brightness -= 1;
        }
    }

    void Heartbeat(uint32_t color)
    {
        uint8_t brightness = 100;
        setBrightness(brightness);

        for (int i=0; i < numPixels(); i++)
        {
            // setBrightness(brightness);
            setPixelColor(i, color);
        }
        show();

        while (brightness > 0)
        {
            for (int i=0; i < numPixels(); i++)
            {
                setBrightness(brightness);
            }
            show();
            delay(10);
            brightness -= 10;
        }

        delay(100);
        brightness = 100;
        setBrightness(brightness);
        for (int i=0; i < numPixels(); i++)
        {
            // setBrightness(brightness);
            setPixelColor(i, color);
        }
        show();

        while (brightness > 0)
        {
            for (int i=0; i < numPixels(); i++)
            {
                setBrightness(brightness);
            }
            show();
            delay(30);
            brightness -= 10;
        }

        brightness = 0;
        for (int i=0; i < numPixels(); i++)
        {
            setBrightness(brightness);
        }
        show();
        delay(400);
    }
};