/*
  Button
  1.86 76 68 61 C5 66
  2.86 76 68 62 C6 66
  3.86 76 68 63 C6 66
  created 2010
  by Kalvin.Liu@Make Shields 
 */
 
const int buttonPin1 = 2;     // the number of the pushbutton1 pin
const int buttonPin2 = 3;     // the number of the pushbutton2 pin
const int buttonPin3 = 4;     // the number of the pushbutton3 pin
const int ledPin =  13;      // the number of the LED pin

void setup()
{
  // start serial port at 9600 bps:
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);    
  pinMode(buttonPin1, INPUT);   
  pinMode(buttonPin2, INPUT);   
  pinMode(buttonPin3, INPUT);    
}

void loop()
{
  // check if the pushbutton is pressed.
  // if it is, the buttonState is HIGH:
  if (digitalRead(buttonPin1) == HIGH) {     
    // turn LED on:    
    digitalWrite(ledPin, HIGH);  
    Serial.print(0x61, HEX);               
  }
  else if (digitalRead(buttonPin2) == HIGH) {     
    // turn LED on:    
    digitalWrite(ledPin, HIGH);  
    Serial.print(0x62, HEX);               
  }
  else if (digitalRead(buttonPin3) == HIGH) {     
    // turn LED on:    
    digitalWrite(ledPin, HIGH);  
    Serial.print(0x63, HEX);               
  }
}
