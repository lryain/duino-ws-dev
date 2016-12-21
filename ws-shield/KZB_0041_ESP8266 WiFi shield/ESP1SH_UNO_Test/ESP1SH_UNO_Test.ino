/**
 * SerialReflector
 */
#include <SoftwareSerial.h>

SoftwareSerial device(2,3); // Rx, Tx

void setup() {
  Serial.begin(9600);   // Serial port for connection to host
  device.begin(9600);  // Serial port for connection to serial device
}

void loop() {
  if(device.available())
  {
    Serial.write(device.read());
  }
  if(Serial.available())
  {
    device.write(Serial.read());
  }
}
