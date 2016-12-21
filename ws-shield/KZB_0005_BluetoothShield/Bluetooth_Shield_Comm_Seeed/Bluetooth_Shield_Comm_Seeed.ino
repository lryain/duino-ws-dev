#include <SoftwareSerial.h>

// http://www.seeedstudio.com/depot/bluetooth-shield-p-866.html
#define RxD 6
#define TxD 7
#define BUFFER_SIZE 64
 
SoftwareSerial bluetooth(RxD,TxD);
 
void setup() 
{ 
  Serial.begin(9600);
  bluetooth.begin(9600);
} 

unsigned char buf[BUFFER_SIZE] = {0};
unsigned char len = 0;

void loop() {
  
  if (bluetooth.available()) {
    while (bluetooth.available()) {
      Serial.write(bluetooth.read());
    }
  }
  
  while (Serial.available()) {
    unsigned char c = Serial.read();
    if (c == 0xA || c == 0xD) { // \n or \r
      sendData();
    } else {
      bufferData(c);
    }
  }
}

void bufferData(char c) {
  if (len < BUFFER_SIZE) {
    buf[len++] = c;
  } // TODO warn, or send data
}

void sendData() {
  for (int i = 0; i < len; i++) {
    bluetooth.write(buf[i]);
  }
  bluetooth.write(0xA);
  len = 0;
  bluetooth.flush();  
} 
