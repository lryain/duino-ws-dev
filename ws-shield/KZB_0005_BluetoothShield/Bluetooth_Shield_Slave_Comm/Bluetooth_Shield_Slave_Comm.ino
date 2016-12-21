

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
// Change bluetooth name here
#define BT_NAME  "DP-BT-Slave"
#define BT_BUAD 9600

SoftwareSerial blueToothSerial(RxD, TxD);

void setup()
{
  pinMode(MODE, OUTPUT);
  // pull the A1(D15) pin to HIGH and sent the reset command to enter the AT MODE.
  digitalWrite(MODE, HIGH);
  Serial.begin(BT_BUAD);
  pinMode(RxD, INPUT);
  pinMode(TxD, OUTPUT);
  
  // Reset to enter the AT MODE.
  enterATMode();
  // Switch to Master Mode
  switch2SlaveMode();
  // Read bluetooth module params
  readParams();
  Serial.println("Done!");
  // Switch to Serial Mode
  enterSerialMode();
}

void loop() {
   Serial.println("Please disconnect your bluetooth shield, and power again!");
   delay(1000);
}

void enterATMode()
{
  blueToothSerial.begin(38400);
  delay(100); // This delay is required.
  blueToothSerial.print("AT\r\n");delay(100);
  blueToothSerial.print("AT+RESET\r\n");
  Serial.print("AT+RESET:"); readBluetooth();
  delay(100); // This delay is required.
}

void enterSerialMode()
{
  Serial.println("------------- Switch to Serial Mode ----------------");
  Serial.print("UART:");Serial.println(BT_BUAD);
  blueToothSerial.begin(BT_BUAD);
  // pull the A1(D15) pin to HIGH and sent the reset command to enter the AT MODE.
  digitalWrite(MODE, LOW);
  delay(100); // This delay is required.
  blueToothSerial.print("AT+RESET\r\n");
  Serial.println("SERIAL MODE");
  delay(100); // This delay is required.
}

void switch2SlaveMode()
{
  Serial.println("------------- Switch to Slave Mode ----------------");
  blueToothSerial.print("AT+ORGL\r\n");//Restore default status
  Serial.print("AT+ORGL:"); 
  readBluetooth();
  blueToothSerial.print("AT+ROLE=0\r\n");//Set/ inquire module role
  Serial.print("AT+ROLE:"); 
  readBluetooth();
  blueToothSerial.print("AT+CMODE=1\r\n");//Set/ Inquire - connection mode
  Serial.print("AT+CMODE:"); 
  readBluetooth();
  blueToothSerial.print("AT+UART=");
  blueToothSerial.print(BT_BUAD);
  blueToothSerial.print(",0,0\r\n");
  Serial.print("AT+UART:"); 
  readBluetooth();
  blueToothSerial.print("AT+NAME=");blueToothSerial.print(BT_NAME);blueToothSerial.print("\r\n");
  Serial.print("AT+NAME:"); 
  readBluetooth();
  blueToothSerial.print("AT+INIT\r\n");//Initialize the SPP profile lib
  Serial.print("AT+INIT:"); 
  readBluetooth();
}
void readParams()
{
  Serial.println("------------- Read Params -------------");
  blueToothSerial.print("AT+ROLE?\r\n");//Set/ inquire module role
  readBluetooth();
  blueToothSerial.print("AT+NAME?\r\n");
  readBluetooth();
  blueToothSerial.print("AT+UART?\r\n");
  readBluetooth();
  delay(100);
}

void readBluetooth() {
  //delay(10);
  char recvChar = 0;
  String recvBuf = "";
  while (blueToothSerial.available()) {
    recvChar = blueToothSerial.read();
    recvBuf += recvChar;
  }
  Serial.print(recvBuf);
  delay(800); // This delay is required.
}
