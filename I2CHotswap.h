#include <Arduino.h>
#include <Wire.h>

#include <Adafruit_SleepyDog.h>

class Hotswapper {
  public:
    Hotswapper (void);
    void begin (byte address = 0x70, int led = 13);
    int beginTransmission (int ms = 50);
    void endTransmission (void);
    void transmitUntilSuccess (int ms, byte data[], int dataLength, bool flashLED = false);
    void transmitOnce (int ms, byte data[], int dataLength, bool flashLED = false);
  protected:
    int ledPin;
    byte i2cAddress;
};