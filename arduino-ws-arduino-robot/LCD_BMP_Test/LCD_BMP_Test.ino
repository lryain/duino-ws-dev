/* Robot Logo

 This sketch demonstrates basic movement of the Robot.
 When the sketch starts, press the on-board buttons to tell
 the robot how to move. Pressing the middle button will
 save the pattern, and the robot will follow accordingly.
 You can record up to 20 commands. The robot will move for
 one second per command.

 This example uses images on an SD card. It looks for
 files named "lg0.bmp" and "lg1.bmp" and draws them on the
 screen.

 Circuit:
 * Arduino Robot

 created 1 May 2013
 by X. Yang
 modified 12 May 2013
 by D. Cuartielles

 This example is in the public domain
 */

#include <ArduinoRobot.h> // include the robot library

int commands[20];  //  array for storing commands

void setup() {
  // initialize the Robot, SD card, and display
  Serial.begin(9600);
  Robot.begin();
  Robot.beginTFT();
  Robot.beginSD();
  Robot.stroke(0, 0, 0);
  Robot.displayLogos();
  //Robot.sdTest();
}

void loop() {

  Robot.drawBMP("intro.bmp", 0, 0);  //display background image
  Robot.stroke(0, 0, 0);
  Robot.text("Done!", 5, 103); // write some text to the display
  delay(1500); // wait for a moment
}
