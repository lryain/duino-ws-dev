#include <math.h>
#include <stdlib.h>
#include "Wire.h"
#include "WiiChuck.h"


WiiChuck wii = WiiChuck();

void setup()
{
 wii.initWithPower(); 
 Serial.begin(115200);
}

void loop() 
{
  static int count = 0;

  if (true == wii.read()) {
    Serial.print(count, DEC);
    Serial.print("\t");

    Serial.print("joystick:");
    Serial.print(wii.getJoyAxisX(), DEC);
    Serial.print(",");
    Serial.print(wii.getJoyAxisY(), DEC);
    Serial.print(" \t");

    Serial.print("accel:");
    Serial.print(wii.getAccelAxisX(), DEC);
    Serial.print(",");
    Serial.print(wii.getAccelAxisY(), DEC);
    Serial.print(",");
    Serial.print(wii.getAccelAxisZ(), DEC);
    Serial.print(" \t");

    Serial.print("button:");
    Serial.print(wii.getButtonZ(), DEC);
    Serial.print(",");
    Serial.print(wii.getButtonC(), DEC);

    Serial.println(" ");
    count ++;
  }  
  delay(100);

}