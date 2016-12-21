#define J1  4
#define J2  5
#define J3  6
#define J4  7
#define delay_time 500

void setup()
{
  pinMode(J1, OUTPUT);
  pinMode(J2, OUTPUT);
  pinMode(J3, OUTPUT);
  pinMode(J4, OUTPUT);
}

void loop()
{
  digitalWrite(J1, HIGH);
  delay(delay_time);
  digitalWrite(J1, LOW);
  delay(delay_time);

  digitalWrite(J2, HIGH);
  delay(delay_time);
  digitalWrite(J2, LOW);
  delay(delay_time);

  digitalWrite(J3, HIGH);
  delay(delay_time);
  digitalWrite(J3, LOW);
  delay(delay_time);

  digitalWrite(J4, HIGH);
  delay(delay_time);
  digitalWrite(J4, LOW);
  delay(delay_time);
}




