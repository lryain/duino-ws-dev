#include <SoftwareSerial.h>   //Software Serial Port
#define RxD 2
#define TxD 3
 
#define DEBUG_ENABLED  1
 
SoftwareSerial BLE(RxD,TxD);
 
void setup() 
{ 
  Serial.begin(9600);
  pinMode(RxD, INPUT);
  pinMode(TxD, OUTPUT);
  setupBleConnection();
  Serial.println("Setup done, entering into serial mode.");
} 
 
void loop() 
{ 
  char recvChar;
  while(1){
    if(BLE.available()){//check if there's any data sent from the remote BLE shield
      recvChar = BLE.read();
      Serial.print(recvChar);
    }
    if(Serial.available()){//check if there's any data sent from the local serial terminal, you can add the other applications here
      recvChar  = Serial.read();
      BLE.print(recvChar);
    }
  }
} 
 
void setupBleConnection()
{
  BLE.begin(9600); //Set BLE BaudRate to default baud rate 9600
  delay(3000);
  BLE.print("AT+CLEAR"); //clear all previous setting
  delay(1000);
  readBluetooth();
  BLE.print("AT+NAMEBLE Slave"); //clear all previous setting
  readBluetooth();
  
  BLE.print("AT+ROLE0"); //set the bluetooth name as a slaver
  readBluetooth();
  BLE.print("AT+ROLE?"); //set the bluetooth name as a slaver
  readBluetooth();
  BLE.print("AT+SAVE1");  //don't save the connect information
  readBluetooth();
  BLE.print("AT+SAVE?");  //don't save the connect information
  readBluetooth();
  BLE.print("AT+BAUD?");  //don't save the connect information
  readBluetooth();
  
}

void readBluetooth(){
  delay(1000);  
  char recvChar=0;
  String recvBuf="";
    while(BLE.available()){
      recvChar = BLE.read();
 	recvBuf += recvChar;
    }
  Serial.println(recvBuf);
  //BLE.flush();
}
