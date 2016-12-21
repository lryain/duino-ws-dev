

/* Upload this sketch into Seeeduino and press reset*/
/**
* first you need set the AT_MODE jumper to A1
*
**/
#include <SoftwareSerial.h>   //Software Serial Port
#define RxD 6
#define TxD 7
// Analog pin A1 
#define MODE  15
#define DEFAULT_BUAD 9600

SoftwareSerial blueToothSerial(RxD, TxD);

void setup()
{
  pinMode(MODE, OUTPUT);
  // pull the A1(D15) pin to HIGH and sent the reset command to enter the AT MODE.
  digitalWrite(MODE, LOW);
  Serial.begin(DEFAULT_BUAD);
  blueToothSerial.begin(DEFAULT_BUAD);
  pinMode(RxD, INPUT);
  pinMode(TxD, OUTPUT);
}

void loop() {
    char recvChar;
    while(1)
    {
        if(blueToothSerial.available())
        {//check if there's any data sent from the remote bluetooth shield
            Serial.write(blueToothSerial.read());
        }
        if(Serial.available())
        {//check if there's any data sent from the local serial terminal, you can add the other applications here
          
            blueToothSerial.write(Serial.read());
        }
    }
}
