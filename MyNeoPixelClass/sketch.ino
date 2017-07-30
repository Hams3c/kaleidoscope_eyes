MyNeoPixelClass Rings(32, 0);

unsigned long previousMillis = 0;

// the setup routine runs once when you press reset:
void setup()
{
    Rings.begin();
    Rings.Index = 0;
}


uint32_t customColor = 0xFF0000;
void loop()
{
    unsigned long currentMillis = millis();

    Rings.Color1 = Rings.Wheel(random(255));
    Rings.Color2 = Rings.Wheel(random(255));

    if (currentMillis - previousMillis > 50000L)
    {
        previousMillis = currentMillis;
    }

    if (currentMillis - previousMillis > 45000L)
    {
        Rings.ferrisWheel(Rings.Color1);
    }
    else if (currentMillis - previousMillis > 40000L)
    {
        Rings.RainbowCycle();
    }
    else if (currentMillis - previousMillis > 35000L)
    {
        Rings.TheaterChase(Rings.Color(255,0,0), Rings.Color(0,0,50));
    }
    // sketch too big, had to disable something
    // else if (currentMillis - previousMillis > 30000L)
    // {
    //     Rings.FadeAndBlink(Rings.Color(255,255,0));
    // }
    else if (currentMillis - previousMillis > 25000L)
    {
        Rings.Fade(Rings.Color(255,255,0));
    }
    else if (currentMillis - previousMillis > 20000L)
    {
        Rings.Scanner(Rings.Color(144,0,255));
    }
    else if (currentMillis - previousMillis > 15000L)
    {
        Rings.aInfinity(Rings.Color1);
    }
    else if (currentMillis - previousMillis > 5000L)
    {
        Rings.Heartbeat(Rings.Color(255,0,0));
        delay(2000);
    }
    else
    {
        Rings.Index = 0;
        Rings.Strobe(Rings.Color(255,255,0));
    }
}