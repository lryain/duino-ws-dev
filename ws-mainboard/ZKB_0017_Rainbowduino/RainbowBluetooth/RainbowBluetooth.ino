#include <Rainbowduino.h>

char MessageBuff[7];
unsigned char count = 0;
unsigned char flag = 0;
String recvBuf;
String HeadMessage = "Rain";
unsigned char DisplayStatus;
unsigned char MyAddress = 0;

String inputString = "";         // a string to hold incoming data
boolean stringComplete = false;  // whether the string is complete

unsigned char RED[64] = {255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,238,221,204,188,171,154,137,119,102,85,
68,51,34,17,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,17,35,52};

unsigned char GREEN[64] = {0,17,34,51,68,85,102,119,136,153,170,187,204,221,238,255,255,255,255,255,255,255,255,255,255,255,255,
255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,238,221,204,188,170,154,136,120,102,86,68,52,34,18,0,0,0,0};

unsigned char BLUE[64] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,18,34,52,68,86,102,120,136,154,170,188,
204,221,238,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255};

unsigned char plasma[4][4][4];
unsigned char plasma1[4][4][4];
unsigned char plasma2[4][4][4];
unsigned char x,y,z,colorshift=0;

void setup()
{
  Serial.begin(38400);
  //setupBlueToothConnection();
  delay(2000); // This delay is required.
  Serial.println("The slave bluetooth is inquirable!");
  Rb.init();

  for(unsigned char x = 0; x < 4; x++)
  {
    for(unsigned char y = 0; y < 4; y++)
    {
      for(unsigned char z = 0; z < 4; z++)
       {
        int color = int(32.0 + (32.0 * sin(x / 4.0))+ 32.0 + (32.0 * sin(y / 4.0)) + 32.0 + (32.0 * sin(z / 4.0))) / 3;
        plasma[x][y][z] = color; 
        
        int color1 = int(32.0 + (32.0 * sin(x / 1.0))+ 32.0 + (32.0 * sin(y / 1.0)) + 32.0 + (32.0 * sin(z / 1.0))) / 3;
        plasma1[x][y][z] = color1;
        
        int color2 = int(32.0 + (32.0 * sin(x / 8.0))+ 32.0 + (32.0 * sin(y / 8.0)) + 32.0 + (32.0 * sin(z / 8.0))) / 3;
        plasma2[x][y][z] = color2;     
       }   
    }
  }
}

void loop()
{
   // 0 for pattern switch 1 for free RGB value tuning
  // command format: Rain:p1#
  // command format2: Rain:x,1,256,256,256#
  if(Serial.available())
  {
    Receive();
  }
  //Serial.println(MessageBuff[1]);
  //Serial.println(MessageBuff[2]);
 if(MessageBuff[0] == 0)
  {
    Serial.println(MessageBuff[2]);
     switch(MessageBuff[2])
     {
       case 0:pattern5();break;
       case 1:pattern4();break;
       case 2:pattern3();break;
       case 3:pattern2();break;
       case 4:pattern1();break;
       case 5:pattern6();break;
       default:break;
     }
     delay(200);
  }
  else if(MessageBuff[0] == 1)
  {
    if(MessageBuff[1] & 0x01)
    {
      Light(MessageBuff[3],0,MessageBuff[4],MessageBuff[5],MessageBuff[6]);
    }
    else
    {
      Light(MessageBuff[3],0,0,0,0);
    }
    
    if(MessageBuff[1] & 0x02)
    {
      Light(MessageBuff[3],1,MessageBuff[4],MessageBuff[5],MessageBuff[6]);
    }
    else
    {
      Light(MessageBuff[3],1,0,0,0);
    }
    
    if(MessageBuff[1] & 0x04)
    {
      Light(MessageBuff[3],2,MessageBuff[4],MessageBuff[5],MessageBuff[6]);
    }
    else
    {
      Light(MessageBuff[3],2,0,0,0);
    }
    
    if(MessageBuff[1] & 0x08)
    {
      Light(MessageBuff[3],3,MessageBuff[4],MessageBuff[5],MessageBuff[6]);
    }
    else
    {
      Light(MessageBuff[3],3,0,0,0);
    }
  }
  
 
}
/*
XYZ
123
0xFF
Rb.setPixelZXY(0,0,0,0x0000FF); //uses 24bit RGB color Code
Rb.setPixelZXY(0,3,0,0xFF,0,0); //uses R, G and B color bytes
*/
void Light(unsigned char face,char num,unsigned char R,unsigned char G,unsigned char B)
{
  unsigned char a,b;
  if(num >= 0 && num <= 3)
  {
    for(a = 0; a < 4;a++)
    {
       for(b = 0;b < 4;b++)
       {
         switch(face)
         {
           case 'X':Rb.setPixelZXY(a,num,b,R,G,B);break;
           case 'Y':Rb.setPixelZXY(a,b,num,R,G,B);break;
           case 'Z':Rb.setPixelZXY(num,a,b,R,G,B);break;
         }
       }
    }
  }
}

void Receive()
{
  int nameIndex;
    while(Serial.available())
    {
      if(flag == 0)
      {
        char recvChar = (char)Serial.read();
        recvBuf += recvChar;
        Serial.println(recvBuf);
        nameIndex = recvBuf.indexOf(HeadMessage);
        if(nameIndex != -1)
        {
          flag = 1;
          count = 0;
          recvBuf = "";
          Serial.println("Step1");
        }
      }
      else
      {
        MessageBuff[count] = Serial.parseInt();
        Serial.println(count);
        Serial.println(":");
        Serial.println(MessageBuff[count]);
        count++;
        if(count >= 7)
        {
          recvBuf = "";
          flag = 0;
          Serial.println("Step2");
          Serial.flush();
          return;
        }
      }
    }
}

void pattern1()
{
  Serial.println("pattern1");
  Rb.blankDisplay();
    //Set (Z,X,Y):(0,0,0) pixel BLUE
  Rb.setPixelZXY(0,0,0,0x0000FF); //uses 24bit RGB color Code

  //Set (Z,X,Y):(0,3,0) pixel RED
  Rb.setPixelZXY(0,3,0,0xFF,0,0); //uses R, G and B color bytes

  //Set (Z,X,Y):(3,0,3) pixel GREEN
  Rb.setPixelZXY(3,0,3,0x00FF00); //uses 24bit RGB color Code
}

void pattern2()
{
  Rb.blankDisplay();
  for(x=0;x<4;x++)
  {
    for(y=0;y<4;y++)
    {
     //Paint layer 0 Green
     Rb.setPixelZXY(0,x,y,0x00FF00); //uses 24bit RGB color Code
     if(Serial.available())
      {
        Receive();
        return;
      }
    }
  }  

  for(x=0;x<4;x++)
  {
    for(y=0;y<4;y++)
    {
     //Paint layer 3 Blue
     Rb.setPixelZXY(3,x,y,0x0000FF); //uses 24bit RGB color Code
    }
  }
}

void pattern3()
{
  Rb.blankDisplay(); 
 for(z=0;z<4;z++)
 { 
  for(x=0;x<4;x++)
  {
    for(y=0;y<4;y++)
    {
     //Paint random colors
     Rb.setPixelZXY(z,x,y,random(0xFF),random(0xFF),random(0xFF)); //uses R, G and B color bytes
      if(Serial.available())
      {
        Receive();
        return;
      }
    }
  }
 }
}

void pattern4()
{
  for(x=0;x<4;x++)  
  {
   for(y=0;y<4;y++)  
   {
    for(z=0;z<4;z++)
      {
       Rb.setPixelZXY(z,x,y,(RED[plasma[x][y][z] + colorshift]) % 256,(GREEN[plasma[x][y][z] + colorshift]) % 256,(BLUE[plasma[x][y][z] + colorshift]) % 256); //uses R, G and B color bytes
        if(Serial.available())
      {
        Receive();
        return;
      }
      }
   }
  }
 colorshift=  colorshift + 1;
}

void pattern5()
{
  for(x=0;x<4;x++)  
  {
   for(y=0;y<4;y++)  
   {
    for(z=0;z<4;z++)
      {
       Rb.setPixelZXY(z,x,y,(RED[plasma1[x][y][z] + colorshift]) % 256,(GREEN[plasma1[x][y][z] + colorshift]) % 256,(BLUE[plasma1[x][y][z] + colorshift]) % 256); //uses R, G and B color bytes
        if(Serial.available())
        {
          Receive();
          return;
        }
      }
   }
  }
 colorshift=  colorshift + 1;
}

void pattern6()
{
  for(x=0;x<4;x++)  
  {
   for(y=0;y<4;y++)  
   {
    for(z=0;z<4;z++)
      {
       Rb.setPixelZXY(z,x,y,(RED[plasma2[x][y][z] + colorshift]) % 256,(GREEN[plasma2[x][y][z] + colorshift]) % 256,(BLUE[plasma2[x][y][z] + colorshift]) % 256); //uses R, G and B color bytes
        if(Serial.available())
      {
        Receive();
        return;
      }
      }
   }
  }
 colorshift=  colorshift + 1;
}

void setupBlueToothConnection()
{
  Serial.begin(9600); //Set BluetoothBee BaudRate to default baud rate 38400
  Serial.print("\r\n+STWMOD=0\r\n"); //set the bluetooth work in slave mode
  Serial.print("\r\n+STNA=Rainbow\r\n"); //set the bluetooth name as "SeeedBTSlave"
  Serial.print("\r\n+STOAUT=1\r\n"); // Permit Paired device to connect me
  Serial.print("\r\n+STAUTO=0\r\n"); // Auto-connection should be forbidden here
  delay(2000); // This delay is required.
  Serial.print("\r\n+INQ=1\r\n"); //make the slave bluetooth inquirable 
  //Serial.println("The slave bluetooth is inquirable!");
  delay(2000); // This delay is required.
  Serial.flush();
}



