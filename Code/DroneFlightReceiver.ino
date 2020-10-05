#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include "PPMEncoder.h"


RF24 radio(7, 8);
const byte address[6] = "00001";

long prevMillis;

int r = 0;
int g = 0;
int b = 0;
int times = 0;
double throttle;
struct PACKAGE
{
  int rollV;
  int pitchV;
  int throttleV;
  bool armedV;
};

PACKAGE data;


bool takenOff = false;


void setup() {
  ppmEncoder.begin(10);

  tone(6, 2100, 120);
  delay(120);
  tone(6, 2400, 120);
  delay(120);
  tone(6, 2700, 120);
  delay(120);
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MAX);
  radio.setDataRate(RF24_250KBPS);
  radio.startListening();
  ppmEncoder.setChannel(0, 1497);
  ppmEncoder.setChannel(1, 1497);
  ppmEncoder.setChannel(2, 997);
  ppmEncoder.setChannel(3, 1497);
  ppmEncoder.setChannel(4, 1900);
  long prevMillis = millis();

  while (!radio.available())
  {
    lookingForTransmitterPattern();
  }

  ledsOff();
  startupSequence();

}
void loop() {
  if (radio.available()) {
    startupSequence();
    radio.read(&data, sizeof(PACKAGE));
    throttle = data.throttleV;
    if (throttle >= 1400 && data.armedV)
    {
      takenOff = true;
    }
    else
    {
      takenOff = false;
    }
    ppmEncoder.setChannel(0, data.pitchV);
    ppmEncoder.setChannel(1, data.rollV);
    ppmEncoder.setChannel(2, data.throttleV);
    ppmEncoder.setChannel(3, 1497);
    if (data.armedV)
    {
      ppmEncoder.setChannel(4, 1100);
    }
    else
    {
      ppmEncoder.setChannel(4, 1900);
    }

    prevMillis = millis();
  }
  else if (millis() - prevMillis > 500)
  {
    ppmEncoder.setChannel(0, 1497);
    ppmEncoder.setChannel(1, 1497);
    ledsOff();
    if (takenOff)
    {
      r = 255;
      g = 0;
      setColor();
      if (throttle > 1400)
      {
        throttle = 1400;
      }
      else
      {
        throttle -= .01;
        ppmEncoder.setChannel(2, throttle);
        if (throttle <= 1150)
        {
          takenOff = false;
        }
      }
    }
    else
    {
      
      ppmEncoder.setChannel(0, 1497);
      ppmEncoder.setChannel(1, 1497);
      ppmEncoder.setChannel(2, 1000);
      ppmEncoder.setChannel(4, 1900);
      while (!radio.available())
      {
        lookingForTransmitterPattern();
      }

      ledsOff();
      startupSequence();
    }
  }
}


void lookingForTransmitterPattern()
{
  if (millis() - prevMillis > 200)
  {
    if (r == 255)
    {
      times ++;
      if(times == 7)
      {
        tone(6,2600,130);
        times = 0;
      }
      r = 0;
      setColor();
    }
    else
    {
      r = 255;
      setColor();
    }
    prevMillis = millis();
  }


}


void ledsOff()
{
  r = 0;
  g = 0;
  b = 0;
  setColor();
}

void startupSequence()
{
  r = 0;
  g = 255;
  setColor();
}

void lostConnection()
{

}

void setColor()
{
  analogWrite(A0, 255 - r);
  analogWrite(A1, 255 - g);
  analogWrite(A2, 255 - b);
}
