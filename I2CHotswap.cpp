#include <Arduino.h>
#include <Wire.h>

#include <Adafruit_SleepyDog.h>

#include <I2CHotswap.h>

Hotswapper::Hotswapper (void) {}

void Hotswapper::begin (byte address, int led) {
  Wire.begin();
  pinMode(led, OUTPUT);
  
  ledPin = led;
  i2cAddress = address;
}

int Hotswapper::beginTransmission (int ms) {
  return Watchdog.enable(ms);
}

void Hotswapper::endTransmission (void) {
  Watchdog.disable();
  
  digitalWrite(ledPin, LOW);
}

void Hotswapper::transmitUntilSuccess (int ms, byte data[], int dataLength, bool flashLED) {
  do {
    Wire.beginTransmission(i2cAddress);
    
    for (int i = 0; i < dataLength; i ++)
      Wire.write(data[i]);
    
    if (flashLED)
      digitalWrite(ledPin, HIGH);
  } while (Wire.endTransmission() != 0);
}

void Hotswapper::transmitOnce (int ms, byte data[], int dataLength, bool flashLED) {
  Wire.beginTransmission(i2cAddress);
  
  for (int i = 0; i < dataLength; i ++)
    Wire.write(data[i]);
  
  if (flashLED)
    digitalWrite(ledPin, HIGH);
  
  if (Wire.endTransmission() != 0)
    delay(ms + 10);
}