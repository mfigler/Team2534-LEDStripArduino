#include <FastLED.h>
#include <Wire.h>
#define LED_PIN     6
#define NUM_LEDS    150

CRGB leds[NUM_LEDS];
volatile int patternCode = 9;
int d_lay = 300;

void setup() 
{
  Wire.begin(8);                // join i2c bus with address #8
//  Wire.onReceive(receiveEvent); // register event
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
      //BLUE
      leds[thisLED] = CRGB(0, 0, 255);
    }
    FastLED.show();
  }

  else if (patternCode == 2){
    //Serial.print("Here");
    for (int thisLED = 0; thisLED < NUM_LEDS; thisLED++) 
    {
      //RED
      leds[thisLED] = CRGB(255, 0, 0);
    }
    FastLED.show();
  }

  else if (patternCode == 3){
    //Serial.print("Here");
    for (int thisLED = 0; thisLED < NUM_LEDS; thisLED++) 
    {
      //GREEN
      leds[thisLED] = CRGB(0, 255, 0);
    }
    FastLED.show();
  }

  else if (patternCode == 4){
    for(int thisLED = 0; thisLED < NUM_LEDS; thisLED++)
    {
      //PINK
      leds[thisLED] = CRGB(255, 0, 191);
    }
    FastLED.show();
  }

  else if (patternCode == 5){
    for(int thisLED = 0; thisLED < NUM_LEDS; thisLED++)
    {
      //PURPLE
      leds[thisLED] = CRGB(128, 0, 255);
    }
    FastLED.show();
  }

  else if (patternCode == 6){
    for(int thisLED = 0; thisLED < NUM_LEDS; thisLED++)
    {
      //SKY BLUE
      leds[thisLED] = CRGB(0, 255, 255);
    }
    FastLED.show();
  }

  else if (patternCode == 7){
    for(int thisLED = 0; thisLED < NUM_LEDS; thisLED++)
    {
      //YELLOW
      leds[thisLED] = CRGB(255, 255, 0);
    }
    FastLED.show();
  }

  else if (patternCode == 8){
    for(int thisLED = 0; thisLED < NUM_LEDS; thisLED++)
    {
      //ORANGE
      leds[thisLED] = CRGB(255, 128, 0);
    }
    FastLED.show();
  }

  else if(patternCode == 9){
    //Activate Rainbow
    rainbowCycle(20);   
  }

  else if(patternCode == 10){
    //Green-Red Flash
    for (int thisLED = 0; thisLED < NUM_LEDS; thisLED++) 
    {
      leds[thisLED] = CRGB(0, 255, 0);
    }
    FastLED.show();
    delay(d_lay);
    for (int thisLED = 0; thisLED < NUM_LEDS; thisLED++) 
    {

      leds[thisLED] = CRGB(255, 0, 0);
    }
    FastLED.show();
    delay(d_lay);
  }

  else if(patternCode == 11){
    //Police 
    for (int thisLED = 0; thisLED < NUM_LEDS; thisLED++) 
    {
      leds[thisLED] = CRGB(255, 0, 0);
    }
    FastLED.show();
    delay(d_lay);
    for (int thisLED = 0; thisLED < NUM_LEDS; thisLED++) 
    {
      //GREEN
      leds[thisLED] = CRGB(0, 0, 255);
    }
    FastLED.show();
    delay(d_lay);
  }

  Serial.println(patternCode);
}
void rainbowCycle(int SpeedDelay) {
  byte *c;
  uint16_t i, j;

  for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
    for(i=0; i< NUM_LEDS; i++) {
      c=Wheel(((i * 256 / NUM_LEDS) + j) & 255);
      setPixel(i, *c, *(c+1), *(c+2));
    }
    showStrip();
    delay(SpeedDelay);
  }
}

byte * Wheel(byte WheelPos) {
  static byte c[3];
  
  if(WheelPos < 85) {
   c[0]=WheelPos * 3;
   c[1]=255 - WheelPos * 3;
   c[2]=0;
  } else if(WheelPos < 170) {
   WheelPos -= 85;
   c[0]=255 - WheelPos * 3;
   c[1]=0;
   c[2]=WheelPos * 3;
  } else {
   WheelPos -= 170;
   c[0]=0;
   c[1]=WheelPos * 3;
   c[2]=255 - WheelPos * 3;
  }

  return c;
}

void showStrip() {
 #ifndef ADAFRUIT_NEOPIXEL_H
   // FastLED
   FastLED.show();
 #endif
}

void setPixel(int Pixel, byte red, byte green, byte blue) {
 #ifndef ADAFRUIT_NEOPIXEL_H 
   // FastLED
   leds[Pixel].r = red;
   leds[Pixel].g = green;
   leds[Pixel].b = blue;
 #endif
}

  void setAll(byte red, byte green, byte blue) {
  for(int i = 0; i < NUM_LEDS; i++ ) {
    setPixel(i, red, green, blue); 
  }
    showStrip();
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
