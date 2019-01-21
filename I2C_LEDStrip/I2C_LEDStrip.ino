#include <FastLED.h>
#include <Wire.h>

#define LED_PIN     6
#define NUM_LEDS    150

CRGB leds[NUM_LEDS];
volatile int patternCode = 0;

void setup() 
{
  Wire.begin(8);                // join i2c bus with address #8
  Wire.onReceive(receiveEvent); // register event
  Serial.begin(115200);           // start serial for 
  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
}

void loop() 
{
  if (patternCode == 0)
  {
    for (int thisLED = 0; thisLED < NUM_LEDS; thisLED++) 
    {
      leds[thisLED] = CRGB(0 , 0, 0);     
    }
    FastLED.show();      
  }
  
  else if (patternCode == 1){
    // Loop from the lowest pin to the highest:
    for (int thisLED = 0; thisLED < NUM_LEDS; thisLED++) 
    {
      leds[thisLED] = CRGB(0, 0, 255);
    }
    FastLED.show();
  }

  else if (patternCode == 2){
    //Serial.print("Here");
    for (int thisLED = 0; thisLED < NUM_LEDS; thisLED++) 
    {
      leds[thisLED] = CRGB(255, 0, 0);
    }
    FastLED.show();
  }

  //Serial.println(patternCode);
}

  
  

// Function that executes whenever data is received from master
// This function is registered as an event, see setup()
void receiveEvent(int howMany) 
{
  while (1 < Wire.available()) // loop through all but the last
  { 
    char c = Wire.read(); // receive byte as a character
    Serial.print(c);         // print the character
  }
  int x = Wire.read();    // receive byte as an integer
  //Serial.println(x);         // print the integer

  if (patternCode != x){
    patternCode = x;
  }
}
