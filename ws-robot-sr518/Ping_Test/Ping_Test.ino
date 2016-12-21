/*
J.Teda 21/04/2013

This is a smiple ping test to see if your Half to full duplex circuit is working using the LED on pin 13
LED ON = Dynamixel PING successful
LED OFF = Dynamixel PING fail

You well need to make a half duplex to full duplex circuit to run this sketch. ( http://support.robotis.com/en/product/dynamixel/dxl_mx_main.htm )
Robotis e-Manual ( http://support.robotis.com )

*/

#include <Dynamixel_Serial.h>       // Library needed to control Dynamixal servo
#include <SoftwareSerial.h>

const int rxpin = 2;
const int txpin = 3;
SoftwareSerial Serial_AX(rxpin, txpin);

#define SERVO_ID 0x01               // ID of Dynamixel (0x01 is default)
#define SERVO_ControlPin 0x02       // Control pin of buffer chip ( 74LS241N )
#define SERVO_SET_Baudrate 500000    // Baud rate speed which the Dynamixel will be set too (57600 is default)
#define LED13 0x0D                  // Pin for Visual indication when ping test is successful - pin 13 normal has a built in LED on Arduino UNO


void setup(){

  pinMode(LED13, OUTPUT);
  digitalWrite(LED13, LOW);

  delay(1000);                                               // Give time for Dynamixel to start on power-up
  Serial_AX.begin(57600);
  Dynamixel.begin(SERVO_SET_Baudrate);                       // Set up Arduino to communicate to Dynamixel
  Dynamixel.setDirectionPin(SERVO_ControlPin);               // Optional. Set direction control pin
}


void loop(){
  //Serial_AX.print("Servo ID: ");Serial_AX.print(SERVO_ID);
  Serial_AX.println(Dynamixel.ping(SERVO_ID));
  if (Dynamixel.ping(SERVO_ID) == SERVO_ID){  // Ping SUCCESSFUL, Status packet has been recived with no error - the value returned from ping is the servo ID
    digitalWrite(LED13, HIGH);
      }else{                                  // Ping NOT successful
        digitalWrite(LED13, LOW);
      }

//  delay(500);  // Delay 0.5 Sec
}



