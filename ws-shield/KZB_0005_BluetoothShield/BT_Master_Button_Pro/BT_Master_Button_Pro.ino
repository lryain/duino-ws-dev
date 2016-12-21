

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
#define PINBUTTON   9                               // pin of button
#define LEDON()     digitalWrite(PINLED, HIGH)
#define LEDOFF()    digitalWrite(PINLED, LOW)

SoftwareSerial blueToothSerial(RxD, TxD);

void setup()
{
  pinMode(MODE, OUTPUT);
  pinMode(PINBUTTON, INPUT);
  // pull the A1(D15) pin to HIGH and sent the reset command to enter the AT MODE.
  digitalWrite(MODE, LOW);
  Serial.begin(9600);
  blueToothSerial.begin(9600);
  pinMode(RxD, INPUT);
  pinMode(TxD, OUTPUT);
  //wait 1s and flush the bluetooth connect
  delay(1000);
}

void loop() {
    static unsigned char state = 0;             // led off
    if(digitalRead(PINBUTTON))
    {
        state = 1-state;
        
        Serial.println("button on");
        
        blueToothSerial.write(0x80);
        blueToothSerial.write(0x80);
        blueToothSerial.write(state);
        blueToothSerial.write(0x70);
        blueToothSerial.write(0x60);
        delay(10);
        while(digitalRead(PINBUTTON))       // until button release
        {
            delay(50);
        }
        
        Serial.println("button off");
    }
}
