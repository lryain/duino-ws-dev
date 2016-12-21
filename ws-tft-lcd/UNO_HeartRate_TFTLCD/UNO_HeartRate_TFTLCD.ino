/*

 TFT Graph

 This example for an Arduino screen reads
 the value of an analog sensor on A0, and
 graphs the values on the screen.

 This example code is in the public domain.

 Created 15 April 2013 by Scott Fitzgerald

 http://arduino.cc/en/Tutorial/TFTGraph

 */

#include <TFT.h>  // Arduino LCD library
#include <SPI.h>

String inString = "";         // a string to hold incoming data
boolean stringComplete = false;  // whether the string is complete

// pin definition for the Uno
#define cs   10
#define dc   8
#define rst  9
//#define LCD_BLK 7 // the blacklight control of the TFT LCD
#define LO_PLUS 6 // the leads off detection LO +
#define LO_MINUS 7 // the leads off detection LO -

// position of the line on screen
int xPos = 1;
float height = 0.0;
float width = 0.0;
float height_old = 0.0;
float height_new = 0.0;
float inByte = 0.0;

// pin definition for the Leonardo
// #define cs   7
// #define dc   0
// #define rst  1

TFT TFTscreen = TFT(cs, dc, rst);

void setup() {
  pinMode(LO_PLUS, INPUT); // Setup for leads off detection LO +
  pinMode(LO_MINUS, INPUT); // Setup for leads off detection LO -
  //pinMode(LCD_BLK, OUTPUT);
  //digitalWrite(LCD_BLK, HIGH);
  // initialize serial:
  Serial.begin(9600);
    while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }
  // reserve 200 bytes for the inputString:
  inString.reserve(200);
  // initialize the screen
  TFTscreen.begin();
  height = TFTscreen.height();
  width = TFTscreen.width();
  // clear the screen with a nice color
  TFTscreen.background(0, 0, 200);
}

void loop() {
  if((digitalRead(LO_PLUS) == 1)||(digitalRead(LO_MINUS) == 1)){
    Serial.println('!');
    inString += "!\n";
  }else{
    // send the value of analog input 0:
      Serial.println(analogRead(A0));
      inString += analogRead(A0);
      inString += "\n";
  }
delay(1);
   
  if (inString != "") {
    // trim off any whitespace:
    //inString = inString.trim();
    
    // If leads off detection is true notify with blue line
    if (inString.equals("!")) { 
      //stroke(0, 0, 0xff); //Set stroke to blue ( R, G, B)
      TFTscreen.stroke(0, 0, 0xff);
      inByte = 512;  // middle of the ADC range (Flat Line)
    }
    // If the data is good let it through
    else {
      //stroke(0xff, 0, 0); //Set stroke to red ( R, G, B)
      TFTscreen.stroke(0xff, 0, 0);
      //inByte = float(inString); 
      inByte = inString.toFloat();
     }
     //Map and draw the line for new data point
     inByte = map(inByte, 0, 1023, 0, height);
     height_new = height - inByte; 
     TFTscreen.line(xPos - 1, height_old, xPos, height_new);
     height_old = height_new;
    
      // at the edge of the screen, go back to the beginning:
      if (xPos >= width) {
        xPos = 0;
        TFTscreen.background(0xff);
      } 
      else {
        // increment the horizontal position:
        xPos++;
      }
    
  }

  inString = "";

  delay(10);
}

