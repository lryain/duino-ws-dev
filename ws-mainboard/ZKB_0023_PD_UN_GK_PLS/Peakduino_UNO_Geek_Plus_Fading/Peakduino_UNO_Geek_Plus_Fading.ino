#define delayTime 100
#define fadingDelayTime 30
#define fadingCount 3
#define blinkCount 3

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
    delay(delayTime);
  }
  delay(300);
  for (int i = 0; i < A7; i++)
  {
    digitalWrite(i, LOW);
    delay(delayTime);
  }
  delay(300);

  for(int i=0; i<blinkCount; i++){
    for (int i = 0; i < A7; i++)
      {
        digitalWrite(i, HIGH);
        delay(50);
        digitalWrite(i, LOW);
        delay(80);
      }
    delay(300);
  }
  for(int i=0; i<fadingCount; i++){
    // fade in from min to max in increments of 5 points:
    for (int fadeValue = 0 ; fadeValue <= 255; fadeValue += 5) {
      // sets the value (range from 0 to 255):
      analogWrite(3, fadeValue);
      analogWrite(5, fadeValue);
      analogWrite(6, fadeValue);
      analogWrite(9, fadeValue);
      analogWrite(10, fadeValue);
      analogWrite(11, fadeValue);
      // wait for 30 milliseconds to see the dimming effect
      delay(fadingDelayTime);
    }
  
    // fade out from max to min in increments of 5 points:
    for (int fadeValue = 255 ; fadeValue >= 0; fadeValue -= 5) {
      // sets the value (range from 0 to 255):
      analogWrite(3, fadeValue);
      analogWrite(5, fadeValue);
      analogWrite(6, fadeValue);
      analogWrite(9, fadeValue);
      analogWrite(10, fadeValue);
      analogWrite(11, fadeValue);
      // wait for 30 milliseconds to see the dimming effect
      delay(fadingDelayTime);
    }
  }
  delay(1000);

  for(int i=0; i<blinkCount; i++){
    for (int i = 0; i < A7; i++)
    {
      digitalWrite(i, HIGH);
    }
    delay(300);
    for (int i = 0; i < A7; i++)
    {
      digitalWrite(i, LOW);
    }
    delay(300);
  }
}


