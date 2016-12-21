/*
  LED Wing Test
  Turns on all LEDs on for 100 millisecond, then off for 100 millisecond, Sequentially and repeatedly.

  More information about your Peakduino UNO, check
  the documentation at http://duinopeak.com/content/getting-know-about-peakduino-uno-geek-plus-editon

  This example code is in the public domain.

  modified 8 May 2016
  by Kevin Liu
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
