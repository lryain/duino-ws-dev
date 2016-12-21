#include <Rainbowduino.h>
unsigned char x,y,z,colorshift=0;
unsigned char RED[64] = {255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,238,221,204,188,171,154,137,119,102,85,
68,51,34,17,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,17,35,52};

unsigned char GREEN[64] = {0,17,34,51,68,85,102,119,136,153,170,187,204,221,238,255,255,255,255,255,255,255,255,255,255,255,255,
255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,238,221,204,188,170,154,136,120,102,86,68,52,34,18,0,0,0,0};

unsigned char BLUE[64] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,18,34,52,68,86,102,120,136,154,170,188,
204,221,238,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255};

unsigned char plasma[4][4][4];
unsigned char plasma1[4][4][4];
unsigned char plasma2[4][4][4];
// If you know the size of the String you're expecting, you could use a char[] instead.
String incomingString; // a string to hold incoming data
boolean stringComplete = false;  // whether the string is complete
// example string "a1,b0,c0,d0"
char singleCMDChar = 's';
char fullCMDChar = 'f';
char splitChar = ',';
char toggleChar = '*';
const int swnum = 4;
String singleCmd[swnum];

void setup() {
    Serial.begin(9600);
    Serial.println("Power On");
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
  while (Serial.available()) {
      // get the new byte:
      char inChar = (char)Serial.read(); 
      if (inChar =='#') {
        stringComplete = true;
      } 
      // add it to the inputString:
      if(stringComplete == false) {
        incomingString += inChar;
      }
      // if the incoming character is a newline, set a flag
      // so the main loop can do something about it:
    }
    
  // print the string when a newline arrives:
  if (stringComplete) { // Rain:1,x,256,256,256#
    Serial.print("incomingString: "); 
    Serial.println(incomingString); 
    // handle
    if(incomingString.indexOf(fullCMDChar)==0){//full command
      /*Serial.println("full mode");
      for(int i=0; i<swnum; i++){
        char relayNum = incomingString.substring(i,i+1);
        singleCmd[i] = incomingString.substring(i*3+1,i*3+2);
        char xyz = singleCmd[i].substring(0,1).charAt(0);
        char rgb_1 = singleCmd[i].substring(1,2).charAt(0);
        char rgb_2 = singleCmd[i].substring(2,3).charAt(0);
        if(relayNum=='0')
        {
          Light(xyz,0,MessageBuff[4],MessageBuff[5],MessageBuff[6]);
        }
        else
        {
          Light(MessageBuff[3],0,0,0,0);
        }
        
        if(relayNum=='1')
        {
          Light(MessageBuff[3],1,MessageBuff[4],MessageBuff[5],MessageBuff[6]);
        }
        else
        {
          Light(MessageBuff[3],1,0,0,0);
        }
        
        if(relayNum=='2')
        {
          Light(MessageBuff[3],2,MessageBuff[4],MessageBuff[5],MessageBuff[6]);
        }
        else
        {
          Light(MessageBuff[3],2,0,0,0);
        }
        
        if(relayNum=='3')
        {
          Light(MessageBuff[3],3,MessageBuff[4],MessageBuff[5],MessageBuff[6]);
        }
        else
        {
          Light(MessageBuff[3],3,0,0,0);
        }
      */
    }else{//single command
      if(incomingString.indexOf(singleCMDChar)==0){//single command
        Serial.println("single command"); 
        char patternNum = incomingString.substring(1,2).charAt(0);
        Serial.print("patternNum: "); 
        Serial.println(patternNum);
         switch(patternNum)
         {
           case '0':pattern0();break;
           case '1':pattern1();break;
           case '2':pattern2();break;
           case '3':pattern3();break;
           case '4':pattern4();break;
           case '5':pattern5();break;
           case '6':pattern6();break;
           default:break;
         }
         delay(200);
      }
    }
    // clear the string:
    incomingString = "";
    stringComplete = false;
  }
}

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

void pattern0()
{
  Serial.print("pattern0");
  while(!Serial.available())
  {
    Rb.blankDisplay();
    for(x=0;x<4;x++)
    {
      for(y=0;y<4;y++)
      {
       //Paint layer 0 Green
       Rb.setPixelZXY(0,x,y,0x000000); //uses 24bit RGB color Code
      }
    }  
    delay(1000);
  }
}

void pattern1()
{
  Serial.println("pattern1");
  while(!Serial.available())
  {
    for(z=0; z<64 ;z++)
    {
     for(x=0;x<8;x++)
     {
        for(y=0;y<8;y++)
        {
         //Paint random colors
         //Rb.setPixelZXY(z,x,y,RED[i],GREEN[i],BLUE[i]); //uses R, G and B color bytes
         Rb.setPixelXY(x,y,RED[z],GREEN[z],BLUE[z]); //uses R, G and B color bytes
        }
     }
     delay(100);
    }
    
    for(z=63; z > 0 ;z--)
    {
     for(x=0;x<8;x++)
     {
        for(y=0;y<8;y++)
        {
         //Paint random colors
         //Rb.setPixelZXY(z,x,y,RED[i],GREEN[i],BLUE[i]); //uses R, G and B color bytes
         Rb.setPixelXY(x,y,RED[z],GREEN[z],BLUE[z]); //uses R, G and B color bytes
        }
     }
     delay(100);
    }
  }
}

void pattern2()
{
  Serial.println("pattern2");
  while(!Serial.available())
  {
    Rb.blankDisplay();
    for(x=0;x<4;x++)
    {
      for(y=0;y<4;y++)
      {
       //Paint layer 0 Green
       Rb.setPixelZXY(0,x,y,0x00FF00); //uses 24bit RGB color Code
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
    delay(100);
  }
}

void pattern3()
{  
  Serial.print("pattern3");
  while(!Serial.available())
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
        }
      }
     }
     delay(500);
    }
}

void pattern4()
{
  Serial.print("pattern4");
  while(!Serial.available())
  {
  for(x=0;x<4;x++)  
  {
   for(y=0;y<4;y++)  
   {
    for(z=0;z<4;z++)
      {
       Rb.setPixelZXY(z,x,y,(RED[plasma[x][y][z] + colorshift]) % 256,(GREEN[plasma[x][y][z] + colorshift]) % 256,(BLUE[plasma[x][y][z] + colorshift]) % 256); //uses R, G and B color bytes
      }
   }
  }
  delay(200);
   colorshift=  colorshift + 1;
  }
}

void pattern5()
{
  Serial.print("pattern5");
  while(!Serial.available())
  {
  for(x=0;x<4;x++)  
  {
   for(y=0;y<4;y++)  
   {
    for(z=0;z<4;z++)
      {
       Rb.setPixelZXY(z,x,y,(RED[plasma1[x][y][z] + colorshift]) % 256,(GREEN[plasma1[x][y][z] + colorshift]) % 256,(BLUE[plasma1[x][y][z] + colorshift]) % 256); //uses R, G and B color bytes
      }
   }
  }
   delay(200);
   colorshift=  colorshift + 1;
  }
}

void pattern6()
{
  Serial.print("pattern6");
  while(!Serial.available())
  {
  for(x=0;x<4;x++)  
  {
   for(y=0;y<4;y++)  
   {
    for(z=0;z<4;z++)
      {
       Rb.setPixelZXY(z,x,y,(RED[plasma2[x][y][z] + colorshift]) % 256,(GREEN[plasma2[x][y][z] + colorshift]) % 256,(BLUE[plasma2[x][y][z] + colorshift]) % 256); //uses R, G and B color bytes
      }
   }
  }
   delay(200);
 colorshift=  colorshift + 1;
}
}
