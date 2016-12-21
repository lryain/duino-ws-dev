/**
 * SerialReflector
 */
#include <SoftwareSerial.h>

SoftwareSerial device(6,7); // Rx, Tx

void setup() {
  Serial.begin(19200);   // Serial port for connection to host
  device.begin(19200);  // Serial port for connection to serial device
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
