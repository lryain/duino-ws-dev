

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
#define PINLED      13

#define LEDON()     digitalWrite(PINLED, HIGH)
#define LEDOFF()    digitalWrite(PINLED, LOW)

SoftwareSerial blueToothSerial(RxD, TxD);

void setup()
{
  pinMode(MODE, OUTPUT);
  // pull the A1(D15) pin to HIGH and sent the reset command to enter the AT MODE.
  digitalWrite(MODE, LOW);
  Serial.begin(9600);
  blueToothSerial.begin(9600);
  pinMode(RxD, INPUT);
  pinMode(TxD, OUTPUT);
  pinMode(PINLED, OUTPUT);
  LEDOFF();
  //wait 1s and flush the bluetooth connect
  delay(1000);
}

void loop() {
 char recvChar;
    
    while(1)
    {
        if(blueToothSerial.available())
        {//check if there's any data sent from the remote bluetooth shield
            recvChar = (char)blueToothSerial.read();
            Serial.print(recvChar);
            
            if(recvChar == '1')
            {
                LEDON();
            }
            else if(recvChar == '0')
            {
                LEDOFF();
            }
        }
    }
}
