NeoPatterns Ring1(32, 0, NEO_GRB + NEO_KHZ800, &Ring1Complete);

// Ring1 Completion Callback
void Ring1Complete()
{
    if (digitalRead(9) == LOW)  // Button #2 pressed
    {
        // Alternate color-wipe patterns with Ring2
        Ring1.Color1 = Ring1.Wheel(random(255));
        // Ring1.Interval = 20000;
        Ring1.Interval = 200;
    }
    else  // Retrn to normal
    {
      Ring1.Reverse();
    }
}

// Initialize everything and prepare to start
void setup()
{
    // Initialize all the pixelStrips
    Ring1.begin();

    // Enable internal pullups on the switch inputs
    pinMode(8, INPUT_PULLUP);
    pinMode(9, INPUT_PULLUP);
    
    // Kick off a pattern
    // Ring1.RainbowCycle(100, FORWARD);
    // Ring1.ColorWipe(Ring1.Color(255,255,0), 100, FORWARD);
    // Ring1.TheaterChase(Ring1.Color(255,255,0), Ring1.Color(0,0,50), 100, REVERSE);
    // Ring1.Scanner(Ring1.Color(255,255,0), 50);
    Ring1.aInfinity(Ring1.Color(255,255,0), 50);
    // Ring1.Fade(Ring1.Color(255,255,0), Ring1.Color(0,0,50), 100, 15, FORWARD);
}

void loop() {
    // put your main code here, to run repeatedly:
    Ring1.Update();
}
