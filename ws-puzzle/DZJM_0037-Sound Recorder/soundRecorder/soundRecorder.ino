/****************************************************************************/

#include "APR9600.h"

/*macro definition of the Grove interface on the Sounder Recorder*/
#define SEL1 2
#define SEL2 3
ARP9600 recorder(SEL1, SEL2);
/*Store the command from the serial monitor you type.*/
char index;//can be '2','3','4',that is the index of section 2,section 3,section 4
char control;//control byte, can be 'r' for record, 's' for stop recording,
//'p' for play

void setup()
{
  Serial.begin(9600);
  recorder.begin();
}
void loop()
{
  getCommand();
  delay(50);
}
void getCommand()
{
  if (Serial.available() > 0)
  {
    /*Get the command from the serial monitor*/
    index = Serial.read();
    control = Serial.read();
  }
  while (Serial.available() > 0)Serial.read(); //clear the receive buffer
  if ((index > '1') && (index < '5')) // index should be 2~4
  {
    if (control == 'r') //if it is record comand?
    {
      recorder.record(index - 0x30);
      Serial.print("get the ");
      Serial.write(index);
      Serial.write(control);
      Serial.print(" command, ");
      Serial.print("begin to record section_");
      Serial.println(index - 0x30);
    }
    else if (control == 'p') //if it is play command
    {
      recorder.play(index - 0x30);
      Serial.print("get the ");
      Serial.write(index);
      Serial.write(control);
      Serial.print(" command, ");
      Serial.print("begin to play section_");
      Serial.println(index - 0x30);
    }
    else if (control == 's') //if it is stop command
    {
      recorder.stop();//stop recording
      Serial.print("get the ");
      Serial.write(index);
      Serial.write(control);
      Serial.print(" command, ");
      Serial.print("stop recording");
    }
    /*Clear the comand*/
    index = 0;
    control = 0;
  }
}
