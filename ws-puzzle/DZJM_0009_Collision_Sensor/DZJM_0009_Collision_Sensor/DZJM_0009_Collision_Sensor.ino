
#define LED 13 //the onboard LED of Arduino 
#define COLLISION_SENSOR 2//collision sensor is connected with D2 of Arduino
void setup()
{
  pins_init();
}

void loop()
{
  if (isTriggered())
  {
    turnOnLED();
    delay(100);
  }
  else turnOffLED();
}
void pins_init()
{
  pinMode(LED, OUTPUT);
  turnOffLED();
  pinMode(COLLISION_SENSOR, INPUT);
}
boolean isTriggered()
{
  if (digitalRead(COLLISION_SENSOR))
  {
    delay(50);//Debounce 50 milliseconds
    if (digitalRead(COLLISION_SENSOR))
      return true;//the collision sensor triggers
  }
  return false;
}
void turnOnLED()
{
  digitalWrite(LED, HIGH); //the LED is on
}
void turnOffLED()
{
  digitalWrite(LED, LOW); //the LED is off
}
