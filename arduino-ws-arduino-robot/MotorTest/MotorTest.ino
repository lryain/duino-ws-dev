/*
 Motor Test

 Just see if the robot can move and turn.

 Circuit:
 * Arduino Robot

 created 1 May 2013
 by X. Yang
 modified 12 May 2013
 by D. Cuartielles

 This example is in the public domain
 */

#include <ArduinoRobot.h>
#include <Wire.h>
#include <SPI.h>

void setup() {
  // initialize the robot
  Robot.begin();
    // initialize the screen
  Robot.beginTFT();
}

void loop() {
   // print the value to the TFT screen
  Robot.debugPrint(1);
  Robot.motorsWrite(255, 255);  // move forward
  delay(2000);
  Robot.debugPrint(2);
  Robot.motorsStop();           // fast stop
  delay(1000);
  Robot.debugPrint(3);
  Robot.motorsWrite(-255, -255); // backward
  delay(1000);
  Robot.debugPrint(4);
  Robot.motorsWrite(0, 0);      // slow stop
  delay(1000);
  Robot.debugPrint(5);
  Robot.motorsWrite(-255, 255); // turn left
  delay(2000);
  Robot.debugPrint(6);
  Robot.motorsStop();           // fast stop
  delay(1000);
  Robot.debugPrint(7);
  Robot.motorsWrite(255, -255); // turn right
  delay(2000);
  Robot.debugPrint(8);
  Robot.motorsStop();           // fast stop
  delay(1000);
}
