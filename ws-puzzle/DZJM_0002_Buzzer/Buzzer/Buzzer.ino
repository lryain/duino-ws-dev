/*************************   2014 duinofun   **************************
* File Name          : buzzer.ino
* Author             : duinofunteam
* Version            : V1.0
* Date               : 10/07/2014
* Description        : Demo code for Puzzle - buzzer
*************************************************************************/
void setup()
{
  pinMode(6, OUTPUT);
}

void loop()
{
  for (int i = 0; i < 10; i++)
  {
    digitalWrite(6, HIGH);
    delay(1);//the return of a0 control the buzzer time 0-1024
    digitalWrite(6, LOW);
    delay(1);
  }
}
