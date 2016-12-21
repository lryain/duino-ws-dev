// Project Five - Relay Control
//

void setup()
{
  pinMode(1, INPUT);
  pinMode(2, INPUT);
  pinMode(6, OUTPUT);
}

void loop()
{
  for(int i = 10; i>0; i--)
  {
    if(i%2 == 0)
     {
       digitalWrite(6,HIGH);
       delay(2000);
     }
    else
    {
      digitalWrite(6,LOW);
      delay(2000);
    }
  }
  while(1);
 /*if (digitalRead(1)==HIGH)
  {
    digitalWrite(6, HIGH);
    delay(100);
  }
  if (digitalRead(2)==HIGH)
  {
    digitalWrite(6, LOW);
  }*/
}
