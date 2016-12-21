/*
/* Grove - Temprature Sensor demo v1.0
*  This sensor detects the enviroment temprature,
*  Connect the signal of this sensor to A0, use the 
*  Serial monitor to get the result.
*  By:
*/
#include <math.h>
int a;
float temperature;
int B=3975;                  //B value of the thermistor
float resistance;

void setup()
{
  Serial.begin(9600);  
}

void loop()
{
  a=analogRead(0);
  //a=1023;//-273.15
  //a=1;//-76.97
  //a=512;//25.04
  //a=550;//28.41
  resistance=(float)(1023-a)*10000/a; //get the resistance of the sensor;
  temperature=1/(log(resistance/10000)/B+1/298.15)-273.15;//convert to temperature via datasheet ;
  delay(300);
  Serial.print("Current temperature is ");
  Serial.println(temperature);
  Serial.print("ADC: ");
  Serial.println(a);
 }
