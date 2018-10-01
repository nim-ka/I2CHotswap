#include <Adafruit_LEDBackpack.h>
#include <I2CHotswap.h>

Adafruit_8x16minimatrix matrix = Adafruit_8x16minimatrix();
Hotswapper hotswapper = Hotswapper();

void setup () {
  hotswapper.begin();

  int tx = hotswapper.beginTransmission();

  // Repeatedly sends the data to initialize the matrix until the I2C device is found
  hotswapper.transmitUntilSuccess(tx, new byte[3] { 0x21, 0x81, 0xEF }, 3, true);
  matrix.begin(MATRIX_ADDRESS);

  hotswapper.endTransmission();
}

// LED Matrix code goes here! Make sure to call `writeDisplay` instead of `matrix.writeDisplay`
int state = LED_OFF;

void loop () {
  for (int i = -1; i <= 8; i ++) {
    matrix.drawRect(-1, -1, 8 - i, 15 - i * 2,
      state == LED_OFF ? LED_ON : LED_OFF);
    matrix.drawRect(-1, -1, 8 - i, 16 - i * 2,
      state == LED_OFF ? LED_ON : LED_OFF);
    
    writeDisplay();

    delay(50);
  }

  state = state == LED_OFF ? LED_ON : LED_OFF;
}

// For other matrix functions you can write your own very easily by just going into the LED Backpack repository,
// finding the code for said function, and putting all the `Wire.write` calls into a byte array like I did with
// `matrix.begin` at the start
void writeDisplay () {
  // Data to send to the matrix
  byte data[17] = {0x00};

  for (int i = 0; i < 8; i ++) {
    data[i * 2 + 1] = matrix.displaybuffer[i] & 0xFF;
    data[i * 2 + 2] = matrix.displaybuffer[i] >> 8;
  }

  // Start transmitting
  int tx = hotswapper.beginTransmission();

  // `transmitOnce` will try to transmit the data once, and resets the system if it failed
  hotswapper.transmitOnce(tx, data, 17, true);

  hotswapper.endTransmission();
}
