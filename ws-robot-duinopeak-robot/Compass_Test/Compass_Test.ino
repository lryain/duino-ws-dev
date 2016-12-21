/* Robot Compass

 The robot has an on-board compass module, with
 which it can tell the direction the robot is
 facing. This sketch will make sure the robot
 goes towards a certain direction.

 Beware, magnets will interfere with the compass
 readings.

 Circuit:
 * Arduino Robot

 created 1 May 2013
 by X. Yang
 modified 12 May 2013
 by D. Cuartielles

 This example is in the public domain
 */

// include the robot library
#include <ArduinoRobot.h>
#include <Wire.h>
#include <SPI.h>

int speedLeft;
int speedRight;
int compassValue;
int direc = 180;  //Direction the robot is heading

void setup() {
  // initialize the modules
  Robot.begin();
  Robot.beginTFT();
  Robot.beginSD();
  //Robot.displayLogos();
}

void loop() {
  // read the value of the potentiometer
  int val = map(Robot.knobRead(), 0, 1023, 0, 360);
  // read the compass orientation
  compassValue = Robot.compassRead();
  // how many degrees are we off
  int diff = map(compassValue, -480, 250, 0, 360);
  /*
  // modify degress
  if (diff > 180)
    diff = -360 + diff;
  else if (diff < -180)
    diff = 360 + diff;
  */
  // Make the robot turn to its proper orientation
  diff = val-diff;
  Robot.turn(diff);
  // write out to the motors
  Robot.motorsWrite(100, 100);
  // draw the orientation on the screen
  Robot.drawCompass(val);
}
