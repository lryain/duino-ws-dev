/***************************************************
  This is a library for the Adafruit 1.8" SPI display.

This library works with the Adafruit 1.8" TFT Breakout w/SD card
  ----> http://www.adafruit.com/products/358
The 1.8" TFT shield
  ----> https://www.adafruit.com/product/802
The 1.44" TFT breakout
  ----> https://www.adafruit.com/product/2088
as well as Adafruit raw 1.8" TFT display
  ----> http://www.adafruit.com/products/618

  Check out the links above for our tutorials and wiring diagrams
  These displays use SPI to communicate, 4 or 5 pins are required to
  interface (RST is optional)
  Adafruit invests time and resources providing this open source code,
  please support Adafruit and open-source hardware by purchasing
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.
  MIT license, all text above must be included in any redistribution
 ****************************************************/

#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library
#include <SPI.h>
#define POST_TO_SERIAL 1

// For the breakout, you can use any 2 or 3 pins
// These pins will also work for the 1.8" TFT shield
#define TFT_CS     10
#define TFT_RST    9  // you can also connect this to the Arduino reset
                      // in which case, set this #define pin to 0!
#define TFT_DC     8

// Option 1 (recommended): must use the hardware SPI pins
// (for UNO thats sclk = 13 and sid = 11) and pin 10 must be
// an output. This is much faster - also required if you want
// to use the microSD card (see the image drawing example)
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS,  TFT_DC, TFT_RST);

String inString = "";         // a string to hold incoming data

#define LO_PLUS 6 // the leads off detection LO +
#define LO_MINUS 7 // the leads off detection LO -

// position of the line on screen
int xPos = 1;
float height = 0.0;
float width = 0.0;
float height_old = 0.0;
float height_new = 0.0;
float inByte = 0.0;

void setup(void) {
  pinMode(LO_PLUS, INPUT); // Setup for leads off detection LO +
  pinMode(LO_MINUS, INPUT); // Setup for leads off detection LO -
  Serial.begin(9600);
    while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }

  tft.initR(INITR_18GREENTAB);   // initialize a ST7735S chip, black tab
  inString.reserve(200);
  Serial.println("Initialized");
  tft.setRotation(tft.getRotation()+3);
  uint16_t time = millis();
  tft.fillScreen(ST7735_BLACK);
  time = millis() - time;

  Serial.println(time, DEC);
  delay(500);

  // large block of text
  //tft.setTextWrap(false);
  tft.fillScreen(ST7735_BLACK);
  tft.setCursor(0, 30);
  tft.setTextSize(2);
  tft.setTextColor(ST7735_YELLOW);
  tft.println("Duinopeak Heart Rate Test");
  delay(1000);
}

void loop() {
 if((digitalRead(LO_PLUS) == 1)||(digitalRead(LO_MINUS) == 1)){
    Serial.println('!');
    inString += "!\n";
  }else{
    //if(POST_TO_SERIAL){
      int a0 = analogRead(A0);
      Serial.println(a0);
    //}
      inString += a0;
      inString += "\n";
  }
  delay(1);
   if (inString != "") {
    // If leads off detection is true notify with blue line
    if (inString.equals("!")) { 
      tft.fillScreen(ST7735_BLACK);
      //mediabuttons();
      inByte = 512;  // middle of the ADC range (Flat Line)
    }
    // If the data is good let it through
    else {
        // large block of text
      //tft.fillScreen(ST7735_BLACK);
      //inByte = float(inString); 
      inByte = inString.toFloat();
     }
     
     //Map and draw the line for new data point
     inByte = map(inByte, 0, 1023, 0, tft.height());
     height_new = tft.height() - inByte; 
     tft.drawLine(xPos - 1, height_old, xPos, height_new, ST7735_RED);
     //tft.drawFastHLine(xPos - 1, height_old, height_new, ST7735_RED);
     height_old = height_new;
    
      // at the edge of the screen, go back to the beginning:
      if (xPos >= width) {
        xPos = 0;
        //tft.fillScreen(ST7735_BLACK);
      } 
      else {
        // increment the horizontal position:
        xPos++;
      }
    
  }
    inString = "";
    delay(10);
}

void testdrawtext(char *text, uint16_t color) {
  tft.setCursor(0, 0);
  tft.setTextColor(color);
  tft.setTextWrap(true);
  tft.print(text);
}

void testfastlines(uint16_t color1, uint16_t color2) {
  tft.fillScreen(ST7735_BLACK);
  for (int16_t y=0; y < tft.height(); y+=5) {
    tft.drawFastHLine(0, y, tft.width(), color1);
  }
  for (int16_t x=0; x < tft.width(); x+=5) {
    tft.drawFastVLine(x, 0, tft.height(), color2);
  }
}

void mediabuttons() {
  // play
  tft.fillScreen(ST7735_BLACK);
  tft.fillRoundRect(25, 10, 78, 60, 8, ST7735_WHITE);
  tft.fillTriangle(42, 20, 42, 60, 90, 40, ST7735_RED);
  delay(500);
  // pause
  tft.fillRoundRect(25, 90, 78, 60, 8, ST7735_WHITE);
  tft.fillRoundRect(39, 98, 20, 45, 5, ST7735_GREEN);
  tft.fillRoundRect(69, 98, 20, 45, 5, ST7735_GREEN);
  delay(500);
  // play color
  tft.fillTriangle(42, 20, 42, 60, 90, 40, ST7735_BLUE);
  delay(50);
  // pause color
  tft.fillRoundRect(39, 98, 20, 45, 5, ST7735_RED);
  tft.fillRoundRect(69, 98, 20, 45, 5, ST7735_RED);
  // play color
  tft.fillTriangle(42, 20, 42, 60, 90, 40, ST7735_GREEN);
}
