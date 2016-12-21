#define delayTime 500
#define fadingDelayTime 100
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
}


