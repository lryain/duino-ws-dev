#include <GPRS_Shield_Arduino.h>
#include <SoftwareSerial.h>
#include <Wire.h>
#include <Suli.h>

#define PIN_TX    2
#define PIN_RX    3
#define BAUDRATE  9600
#define PHONE_NUMBER  "10086"

GPRS gprsTest(PIN_TX,PIN_RX,BAUDRATE);//RX,TX,PWR,BaudRate

#define POWER_KEY 7
void setup()
{
  Serial.begin(9600);
  while(0 != gprsTest.init()) { //gprs init
      Serial.print("gprs init error\r\n");
      delay(1000);
  }
  Serial.print("gprs init success\r\n");
  delay(1000);
}

void loop() {
  //nothing to do
}
