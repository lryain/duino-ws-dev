/*
  Blink
  Turns on an LED on for one second, then off for one second, repeatedly.
 
  This example code is in the public domain.
 */
 
// Pin 13 has an LED connected on most Arduino boards.
// give it a name:
int ledPins[] = {0, 1, 2, 3};

// the setup routine runs once when you press reset:
void setup() {                
  // initialize the digital pin as an output.   
  for(int i=0; i<4; i++)  // This for loop will run 5 times
  {  // blink the white LEDs (first 5 LEDs in ledPins array)
    pinMode(ledPins[i], OUTPUT);  // set pin as output
  }  
}

// the loop routine runs over and over again forever:
void loop() {
for(int i=0; i<4; i++)  // This for loop will run 5 times
  {  // blink the white LEDs
    digitalWrite(ledPins[i], HIGH);  // turn LED on
    delay(150);  // wait for a quarter second
    digitalWrite(ledPins[i], LOW); // turn LED off
  }
}
