/*
  Blink
  Turns on an LED on for one second, then off for one second, repeatedly.

  Most Arduinos have an on-board LED you can control. On the Uno and
  Leonardo, it is attached to digital pin 13. If you're unsure what
  pin the on-board LED is connected to on your Arduino model, check
  the documentation at http://www.arduino.cc

  This example code is in the public domain.

  modified 8 May 2014
  by Scott Fitzgerald
 */
 
void setup() {
  // put your setup code here, to run once:
  for (int i = 0; i < A7; i++) {
    pinMode(i, OUTPUT);
    digitalWrite(i, LOW);
  }
}

void loop() {
  for (int i = 0; i < A7; i++)
  {
    digitalWrite(i, HIGH);
    delay(100);
  }

  for (int i = 0; i < A7; i++)
  {
    digitalWrite(i, LOW);
    delay(100);
  }
}
