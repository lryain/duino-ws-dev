/*
GPRS Loop Handle

This sketch is used to test seeeduino GPRS_Shield's call answering and 
reading SMS function.To make it work, you should insert SIM card
to Seeeduino GPRS Shield,enjoy it!

create on 2013/12/5, version: 0.1
by lawliet.zou(lawliet.zou@gmail.com)
*/
#include <GPRS_Shield_Arduino.h>
#include <SoftwareSerial.h>
#include <Wire.h>
#include <Suli.h>

#define PIN_TX    7
#define PIN_RX    8
#define BAUDRATE  9600
//#define BAUDRATE  19200
#define PHONE_NUMBER  "18603063105"
char gprsBuffer[64];
int i = 0;
char *s = NULL;
int inComing = 0;

GPRS gprsTest(PIN_TX,PIN_RX,BAUDRATE);//RX,TX,PWR,BaudRate
 
void setup() {
  Serial.begin(9600);
  // Disconnect Existing Connection
  sim900_send_cmd("ATH\r\n");
  delay(300);
  // Reset to default config
  sim900_send_cmd("ATZ\r\n");
  delay(300);
  while(0 != gprsTest.init()) {
      delay(1000);
      Serial.print("init error\r\n");
  }
  delay(1000);  
  Serial.println("gprs init success, please call to me!");
}

void loop() {
   if(gprsTest.readable()) {
       inComing = 1;
   }else{ delay(10);}
   
   if(inComing){
      sim900_read_buffer(gprsBuffer,32,DEFAULT_TIMEOUT);
      //Serial.print(gprsBuffer);
      
      if(NULL != strstr(gprsBuffer,"RING")) {
          //gprsTest.answer();
          Serial.print(gprsBuffer);
          delay(3000);
          // Disconnect Existing Connection
          sim900_send_cmd("ATH\r\n");
          Serial.println("start to call ...");
          gprsTest.callUp(PHONE_NUMBER);
          delay(3000);  
      }else{
       Serial.print(gprsBuffer);
          delay(3000);
          // Disconnect Existing Connection
          sim900_send_cmd("ATH\r\n");
          Serial.println("start to call ...");
          gprsTest.callUp(PHONE_NUMBER);
          delay(3000);  
      }/*else if(NULL != (s = strstr(gprsBuffer,"+CMTI: \"SM\""))) { //SMS: $$+CMTI: "SM",24$$
          char message[MESSAGE_LENGTH];
          int messageIndex = atoi(s+12);
          gprsTest.readSMS(messageIndex, message,MESSAGE_LENGTH);
          Serial.print("Recv Message: ");
          Serial.println(message);
     }*/
     sim900_clean_buffer(gprsBuffer,32);  
     inComing = 0;
   }
}
