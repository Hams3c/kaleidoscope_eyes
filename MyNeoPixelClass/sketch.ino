MyNeoPixelClass Rings(32, 0);

// the setup routine runs once when you press reset:
void setup()
{
    Rings.begin();
    Rings.setBrightness(60);
    Rings.Index = 0;
}

uint32_t customColor = 0xFF0000;
uint8_t i = 0;
void loop()
{
    Rings.Color1 = Rings.Wheel(random(255));
    Rings.Color2 = Rings.Wheel(random(255));


    if (i < 25)
    {
        Rings.ferrisWheel(Rings.Color1);
    }
    else if (i < 50)
    {
        Rings.RainbowCycle();
    }
    else if (i < 75)
    {
        Rings.TheaterChase(Rings.Color(255,0,0), Rings.Color(0,0,50));
    }
    else if (i < 100)
    {
        Rings.FadeAndBlink(Rings.Color(255,255,0));
    }
    else if (i < 125)
    {
        Rings.Fade(Rings.Color(255,255,0));
    }
    else if (i < 150)
    {
        Rings.Scanner(Rings.Color(0,200,0));
    }
    else if (i < 175)
    {
        Rings.aInfinity(Rings.Color1);
    }
    else if (i < 200)
    {
        Rings.Strobe(Rings.Color(255,255,0));
    }
    else if (i < 225)
    {
        Rings.Heartbeat(Rings.Color(255,0,0));
        delay(2000);
    }
    else
    {
        i = 0;
    }
    i++;
}