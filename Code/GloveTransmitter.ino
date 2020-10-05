
#include <Adafruit_DotStar.h>
#include <SPI.h>         

Adafruit_DotStar strip(144, 5, 4, DOTSTAR_BGR);
bool startLEDS = false;
void setup() {


  strip.begin(); // Initialize pins for output
  strip.show();  // Turn all LEDs off ASAP
  Serial.begin(9600);
}

void loop() {
  if(Serial.available())
  {
    if(Serial.read() == 's')
    {
      startLEDS = true;
    }
  }
  if(startLEDS)
  {
  for(int i = 1; i< 144; i+=2)
  {
    strip.setPixelColor(i, 0x0000FF);
  }
  for(int i = 0; i< 144; i+=2)
  {
    strip.setPixelColor(i, 0xFF0000);
  }
  strip.show(); 
  delay(50);
  for(int i = 0; i< 144; i+=2)
  {
    strip.setPixelColor(i, 0x000000);
  }
  for(int i = 1; i< 144; i+=2)
  {
    strip.setPixelColor(i, 0x0000FF);
  }
  strip.show(); 
  delay(50);
  }
}
