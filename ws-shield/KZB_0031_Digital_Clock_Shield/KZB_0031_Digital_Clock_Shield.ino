/*
  Blink
  Turns on an LED on for one second, then off for one second, repeatedly.
 
  This example code is in the public domain.
 */
 
// Pin 13 has an LED connected on most Arduino boards.
// give it a name:
int TX = 0;int RX = 1;
int Da = 2;int Db = 3;int Dc = 4;int Dd = 5;int De = 6;int Df = 7;int Dg = 8;
int W1 = 9;int W2 = 10;int W3 = 11;int W4 = 12;int W5 = 13;int W6 = 14;
// the setup routine runs once when you press reset:
void setup() {                
  // initialize the digital pin as an output.
  pinMode(TX, OUTPUT);pinMode(RX, OUTPUT);
  digitalWrite(TX, LOW);digitalWrite(RX, LOW);
  pinMode(Da, OUTPUT);pinMode(Db, OUTPUT);pinMode(Dc, OUTPUT);pinMode(Dd, OUTPUT);pinMode(De, OUTPUT);pinMode(Df, OUTPUT);pinMode(Dg, OUTPUT);//
  pinMode(W1, OUTPUT);pinMode(W2, OUTPUT);pinMode(W3, OUTPUT);pinMode(W4, OUTPUT);pinMode(W5, OUTPUT);pinMode(W6, OUTPUT);
  digitalWrite(Da, HIGH);digitalWrite(Db, HIGH);digitalWrite(Dc, HIGH);digitalWrite(Dd, HIGH);digitalWrite(De, HIGH);digitalWrite(Df, HIGH);digitalWrite(Dg, HIGH);
  digitalWrite(W1, HIGH);digitalWrite(W2, HIGH);digitalWrite(W3, HIGH);digitalWrite(W4, HIGH);digitalWrite(W5, HIGH);digitalWrite(W6, HIGH);
}

// the loop routine runs over and over again forever:
void loop() {
  digitalWrite(W1, LOW);digitalWrite(W2, HIGH);digitalWrite(W3, HIGH);digitalWrite(W4, HIGH);digitalWrite(W5, HIGH);digitalWrite(W6, HIGH);
  digitalWrite(Da, HIGH);digitalWrite(Db, HIGH);digitalWrite(Dc, HIGH);digitalWrite(Dd, HIGH);digitalWrite(De, HIGH);digitalWrite(Df, HIGH);digitalWrite(Dg, LOW);//0
  delay(3);  
  digitalWrite(W1, HIGH);digitalWrite(W2, LOW);digitalWrite(W3, HIGH);digitalWrite(W4, HIGH);digitalWrite(W5, HIGH);digitalWrite(W6, HIGH);
  digitalWrite(Da, LOW);digitalWrite(Db, HIGH);digitalWrite(Dc, HIGH);digitalWrite(Dd, LOW);digitalWrite(De, LOW);digitalWrite(Df, LOW);digitalWrite(Dg, LOW);//1
  delay(3);              
  digitalWrite(W1, HIGH);digitalWrite(W2, HIGH);digitalWrite(W3, LOW);digitalWrite(W4, HIGH);digitalWrite(W5, HIGH);digitalWrite(W6, HIGH);
  digitalWrite(Da, HIGH);digitalWrite(Db, HIGH);digitalWrite(Dc, LOW);digitalWrite(Dd, HIGH);digitalWrite(De, HIGH);digitalWrite(Df, LOW);digitalWrite(Dg, HIGH);//2
  delay(3);             
  digitalWrite(W1, HIGH);digitalWrite(W2, HIGH);digitalWrite(W3, HIGH);digitalWrite(W4, LOW);digitalWrite(W5, HIGH);digitalWrite(W6, HIGH);
  digitalWrite(Da, HIGH);digitalWrite(Db, HIGH);digitalWrite(Dc, HIGH);digitalWrite(Dd, HIGH);digitalWrite(De, LOW);digitalWrite(Df, LOW);digitalWrite(Dg, HIGH);//3
  delay(3);              
  digitalWrite(W1, HIGH);digitalWrite(W2, HIGH);digitalWrite(W3, HIGH);digitalWrite(W4, HIGH);digitalWrite(W5, LOW);digitalWrite(W6, HIGH);
  digitalWrite(Da, LOW);digitalWrite(Db, HIGH);digitalWrite(Dc, HIGH);digitalWrite(Dd, LOW);digitalWrite(De, LOW);digitalWrite(Df, HIGH);digitalWrite(Dg, HIGH);//4
  delay(3);              
  digitalWrite(W1, HIGH);digitalWrite(W2, HIGH);digitalWrite(W3, HIGH);digitalWrite(W4, HIGH);digitalWrite(W5, HIGH);digitalWrite(W6, LOW);
  digitalWrite(Da, HIGH);digitalWrite(Db, LOW);digitalWrite(Dc, HIGH);digitalWrite(Dd, HIGH);digitalWrite(De, LOW);digitalWrite(Df, HIGH);digitalWrite(Dg, HIGH);//5
  delay(3);              

}


