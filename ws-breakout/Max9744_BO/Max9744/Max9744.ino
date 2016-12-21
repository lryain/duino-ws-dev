#include <Wire.h>
 
// 0x4B is the default i2c address
#define MAX9744_I2CADDR 0x4B
 
// We'll track the volume level in this variable.
int sensorValue = 0;        // value read from the pot
int outputValue = 0;        // value output to the PWM (analog out)
int sensorPin = A0;    // select the input pin for the potentiometer
 
void setup() {
  Serial.begin(9600);
  Serial.println("MAX9744 demo");
  Wire.begin();
  
  if (! setvolume(31)) {
    Serial.println("Failed to set volume, MAX9744 not found!");
    while (1);
  }
}
 
 
// Setting the volume is very simple! Just write the 6-bit
// volume to the i2c bus. That's it!
boolean setvolume(int8_t v) {
  // cant be higher than 63 or lower than 0
  if (v > 63) v = 63;
  if (v < 0) v = 0;
  
  Serial.print("Setting volume to ");
  Serial.println(v);
  Wire.beginTransmission(MAX9744_I2CADDR);
  Wire.write(v);
  if (Wire.endTransmission() == 0) 
    return true;
  else
    return false;
}
 
// Read in + and - characters to set the volume.
void loop() {
  // read the value from the sensor:
  sensorValue = analogRead(sensorPin);
  // map it to the range of the analog out:
  outputValue = map(sensorValue, 0, 63, 0, 255);
 
  setvolume(outputValue);
}
