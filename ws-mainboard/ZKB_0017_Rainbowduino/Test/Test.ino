/*
 Rainbowduino v1.0 Library examples:
 
 test the Red Green Blue three colors
 
 write:yewenwu 2014/09/05
 email:1423119894@qq.com
 */

#include <Rainbowduino.h>

void setup()
{
  Rb.init(); //initialize Rainbowduino driver
}
int x,y,z;
void loop()
{
  for(int m=0;m<256;m++){
    //the Blue color
    for(x=0;x<4;x++)  
    {
      for(y=0;y<4;y++)  
      {
        for(z=0;z<4;z++){
          //Set (Z,X,Y):(0,0,0) pixel BLUE
          Rb.setPixelZXY(z,x,y,m,0,0); //uses 24bit RGB color Code
        }
      }
    }
    delay(2);
  }
  delay(1000);
  for(int m=0;m<256;m++){
    //the RED
    for(x=0;x<4;x++)  
    {
      for(y=0;y<4;y++)  
      {
        for(z=0;z<4;z++){

          //Set (Z,X,Y):(0,3,0) pixel RED
          Rb.setPixelZXY(z,x,y,0,m,0); //uses R, G and B color bytes

        }
      }
    }
    delay(2);
  }
  delay(1000);
  for(int m=0;m<256;m++){
    //the Green
    for(x=0;x<4;x++)  
    {
      for(y=0;y<4;y++)  
      {
        for(z=0;z<4;z++){
          //Set (Z,X,Y):(3,0,3) pixel GREEN
          Rb.setPixelZXY(z,x,y,0,0,m); //uses 24bit RGB color Code
        }
      }
    }
    delay(2);
  }
  delay(1000);
  for(int m=0;m<256;m++){
    //the Green
    for(x=0;x<4;x++)  
    {
      for(y=0;y<4;y++)  
      {
        for(z=0;z<4;z++){
          //Set (Z,X,Y):(3,0,3) pixel GREEN
          Rb.setPixelZXY(z,x,y,m,m,m); //uses 24bit RGB color Code
        }
      }
    }
    delay(2);
  }
  delay(1000);
}







