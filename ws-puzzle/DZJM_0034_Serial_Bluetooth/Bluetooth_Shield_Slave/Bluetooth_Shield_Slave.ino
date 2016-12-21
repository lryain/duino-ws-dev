

/* Upload this sketch into Seeeduino and press reset*/

#include <SoftwareSerial.h>   //Software Serial Port
#define RxD 6
#define TxD 7

#define MODE  15

SoftwareSerial blueToothSerial(RxD,TxD);

void setup()
{
    pinMode(MODE, OUTPUT);
    digitalWrite(MODE, HIGH);
    
    Serial.begin(9600);
    Bluetooth_Reset();
    Slave();

}

void loop()
{
    char recvChar;
    while(1)
    {
        if(blueToothSerial.available())
        {//check if there's any data sent from the remote bluetooth shield
            recvChar = blueToothSerial.read();
            Serial.print(recvChar);
        }
        if(Serial.available())
        {//check if there's any data sent from the local serial terminal, you can add the other applications here
            recvChar  = Serial.read();
            blueToothSerial.print(recvChar);
        }
    }
}

void readBluetooth(){
delay(10);  
  char recvChar=0;String recvBuf=0;//
      while(blueToothSerial.available()){
        recvChar = blueToothSerial.read();
         //Serial.print("recvChar: ");
        //Serial.println(recvChar);
 	recvBuf += recvChar;
      }

Serial.println(recvBuf);
}

void Bluetooth_Reset() 
{ 
  digitalWrite(MODE, HIGH);
  Serial.println("RESET");
 
  
  delay(100); // This delay is required.
} 

void Master() 
{  
  Serial.println("38400");
  blueToothSerial.begin(38400);
  Serial.println("Master");
  blueToothSerial.print("AT+ORGL\r\n");//Restore default status
  Serial.print("AT+ORGL:");readBluetooth();
  delay(100); // This delay is required.
  blueToothSerial.print("AT+ROLE=1\r\n");//Set/ inquire module role
  Serial.print("AT+ROLE=1:");readBluetooth();
  delay(100); // This delay is required.
  blueToothSerial.print("AT+CMODE=1\r\n");//Set/ Inquire - connection mode
  Serial.print("AT+CMODE=1:");readBluetooth();
  delay(100); // This delay is required.
 
  blueToothSerial.print("AT+INIT\r\n");//Initialize the SPP profile lib
  Serial.print("AT+INIT:");readBluetooth();
  delay(100); // This delay is required.
  digitalWrite(MODE, LOW);
  delay(100); // This delay is required.
  Serial.println("connect the module to anyaddress=OK!");
  delay(1000); // This delay is required.
  blueToothSerial.print("AT+ROLE?\r\n");//Set/ inquire module role
  Serial.print("AT+ROLE?:");readBluetooth();
} 

void Slave() 
{ 
  Serial.println("38400");
  blueToothSerial.begin(38400);
  Serial.println("Slave");
  blueToothSerial.print("AT+ORGL\r\n");//Restore default status
  Serial.print("AT+ORGL:");readBluetooth();
  delay(100); // This delay is required.
  blueToothSerial.print("AT+ROLE=0\r\n");//Set/ inquire module role
  Serial.print("AT+ROLE=0:");readBluetooth();
  delay(500); // This delay is required.
  blueToothSerial.print("AT+CMODE=0\r\n");//Set/ Inquire - connection mode
  Serial.print("AT+CMODE=0:");readBluetooth();
  delay(100); // This delay is required.
  blueToothSerial.print("AT+UART=38400,0,0\r\n");
  delay(500); // This delay is required.
   Serial.print("AT+UART=38400");readBluetooth();
    blueToothSerial.print("AT+UART?");delay(3000); 
  readBluetooth();delay(100); 
   //Serial.print("AT+UART?:");delay(100); // This delay is required.readBluetooth();
  delay(100); // This delay is required.
  blueToothSerial.print("AT+INIT\r\n");//Initialize the SPP profile lib
  Serial.print("AT+INIT:");readBluetooth();
  delay(100); // This delay is required.
  digitalWrite(MODE, LOW);
  delay(100); // This delay is required.
  Serial.println("connect the module to thespecified Bluetooth address.=OK!");
  delay(1000); // This delay is required.
  blueToothSerial.print("AT+ROLE?\r\n");//Set/ inquire module role
  Serial.print("AT+ROLE?:");readBluetooth();

} 
