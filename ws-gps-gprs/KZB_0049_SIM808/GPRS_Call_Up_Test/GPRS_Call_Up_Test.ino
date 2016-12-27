/*
  GPRS Call Up Test

  This sketch is used to test seeeduino GPRS_Shield's callUp function.
  to make it work, you should insert SIM card to Duinopeak GPRS
  and replace the phoneNumber,enjoy it!

  create on 2015/12/5, version: 0.1
  by kevin liu(lryain.master@gmail.com)
*/

#include "SIM900.h"
#include <SoftwareSerial.h>
//We don't need the http functions. So we can disable the next line.
//#include "inetGSM.h"
#include "sms.h"
#include "call.h"

//To change pins for Software Serial, use the two lines in GSM.cpp.

//GSM Shield for Arduino
//www.duinopeak.com
//this code is based on the example of Arduino Labs.

//Simple sketch to call up

//We have to create the classes for SMSs and calls.
CallGSM call;
SMSGSM sms;

char number[20];
char phoneNumber[20] = "10086";
byte stat = 0;
int value = 0;
int pin = 1;
char value_str[5];
#define BAUDRATE  9600

void setup()
{
  //Serial connection.
  Serial.begin(BAUDRATE);
  Serial.println("SIM808 Shield Call up testing.");
  //Start configuration of shield with baudrate.
  //For http uses is raccomanded to use 4800 or slower.
  if (gsm.begin(BAUDRATE))
    Serial.println("\nstatus=READY");
  else Serial.println("\nstatus=IDLE");
  delay(3000);
  Serial.println("start to call ...");
  call.Call(phoneNumber);
  delay(30000);
  Serial.println("end up the call ...");

}

void loop() {
  //nothing to do
}
