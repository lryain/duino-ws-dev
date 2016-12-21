/*

Serial LCD Kit Switch Example
written by N.Poole - SparkFun Electronics
Apathyware License 2013 

This is VERY basic example code that allows you to plug the SparkFun Surface Mount Navigation Switch Breakout (COM-08236) 
directly into the D10-13 pins on the Serial LCD Kit and read the position of the switch to the screen.

*/


#include <LiquidCrystal.h>

//Interface pins for the SparkFun Serial LCD Kit
LiquidCrystal lcd(2, 3, 4, 5, 6, 7, 8);


void setup() {

  //This will be ground for the switch
  pinMode(10, OUTPUT);
  digitalWrite(10, LOW); 
  //These are the inputs from the switch
  pinMode(11, INPUT);
  pinMode(12, INPUT);
  pinMode(13, INPUT);
  //Set internal pull-up resistors
  digitalWrite(11, HIGH);
  digitalWrite(12, HIGH);
  digitalWrite(13, HIGH);
  //LCD Backlight
  pinMode(9, OUTPUT);
  digitalWrite(9, HIGH);  

  lcd.begin(16, 2);
  lcd.print("Switch Position");
}

void loop() {

  if(digitalRead(13)==LOW){
  lcd.setCursor(0, 1);
  lcd.print("Left     ");
  }
  if(digitalRead(12)==LOW){
  lcd.setCursor(0, 1);
  lcd.print("Click    ");
  }
  if(digitalRead(11)==LOW){
  lcd.setCursor(0, 1);
  lcd.print("Right    ");
  }
  
}

