/*

 Esplora TFT Graph

 This example for the Esplora with an Arduino TFT reads
 the value of the light sensor, and graphs the values on
 the screen.

 This example code is in the public domain.

 Created 15 April 2013 by Scott Fitzgerald

 http://arduino.cc/en/Tutorial/EsploraTFTGraph

 */

#include <Esplora.h>
#include <TFT.h>  // Arduino LCD library
#include <SPI.h>

String inString = "";         // a string to hold incoming data
boolean stringComplete = false;  // whether the string is complete

// position of the line on screen
int xPos = 1;
float height = 0.0;
float width = 0.0;
float height_old = 0.0;
float height_new = 0.0;
float inByte = 0.0;

void setup() {
  // initialize serial:
  Serial.begin(9600);
    while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }
  // reserve 200 bytes for the inputString:
  inString.reserve(200);
  // initialize the screen
  EsploraTFT.begin();
  height = EsploraTFT.height();
  width = EsploraTFT.width();
  // clear the screen with a nice color
  EsploraTFT.background(0, 0, 200);
}

void loop() {
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read();
    // add it to the inputString:
    inString += inChar;
    // if the incoming character is a newline, set a flag
    // so the main loop can do something about it:
    if (inChar == '\n') {
      stringComplete = true;
    }
  }

   
  if (inString != ""&&stringComplete) {
    // trim off any whitespace:
    //inString = inString.trim();
    
    // If leads off detection is true notify with blue line
    if (inString.equals("!")) { 
      //stroke(0, 0, 0xff); //Set stroke to blue ( R, G, B)
      EsploraTFT.stroke(0, 0, 0xff);
      inByte = 512;  // middle of the ADC range (Flat Line)
    }
    // If the data is good let it through
    else {
      //stroke(0xff, 0, 0); //Set stroke to red ( R, G, B)
      EsploraTFT.stroke(0xff, 0, 0);
      //inByte = float(inString); 
      inByte = inString.toFloat();
     }
     Serial.println(inByte);
     //Map and draw the line for new data point
     inByte = map(inByte, 0, 1023, 0, height);
     height_new = height - inByte; 
     EsploraTFT.line(xPos - 1, height_old, xPos, height_new);
     height_old = height_new;
    
      // at the edge of the screen, go back to the beginning:
      if (xPos >= width) {
        xPos = 0;
        EsploraTFT.background(0xff);
      } 
      else {
        // increment the horizontal position:
        xPos++;
      }
    
  }
  if (stringComplete) {
    // clear the string:
    inString = "";
    //Serial.print("--");
    //Serial.println(inString);
    stringComplete = false;
  }else{
    //Serial.println("false");
  } 
  delay(16);
}

void serialEvent() {
  // get the ASCII string:
  //String inString = myPort.readStringUntil('\n');
  

}

