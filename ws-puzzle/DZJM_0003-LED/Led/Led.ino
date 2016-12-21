/*************************   2014 duinofun   **************************
* File Name          : led.ino
* Author             : duinofunteam
* Version            : V1.0
* Date               : 10/07/2014
* Description        : Demo code for Puzzle - LED
*************************************************************************/
 
#define LED 2 //connect LED to digital pin2
void setup() {                
  // initialize the digital pin2 as an output.
  pinMode(LED, OUTPUT);     
}
 
void loop() {
  digitalWrite(LED, HIGH);   // set the LED on
  delay(500);               // for 500ms
  digitalWrite(LED, LOW);   // set the LED off
  delay(500);
}

