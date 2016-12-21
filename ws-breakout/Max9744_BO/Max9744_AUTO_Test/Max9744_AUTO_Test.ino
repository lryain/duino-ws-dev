#include <Wire.h>
 
// 0x4B is the default i2c address
#define MAX9744_I2CADDR 0x4B
 
// We'll track the volume level in this variable.
int8_t thevol = 31;
 
void setup() {
  Serial.begin(9600);
  Serial.println("MAX9744 demo");
  Wire.begin();
  Serial.println("setvolume");
  if (! setvolume(thevol)) {
    Serial.println("Failed to set volume, MAX9744 not found!");
    //while (1);
  }
  Serial.println("Setup done");
}
 
 
// Setting the volume is very simple! Just write the 6-bit
// volume to the i2c bus. That's it!
boolean setvolume(int8_t v) {
  // cant be higher than 63 or lower than 0
  if (v > 63) v = 63;
  if (v < 0) v = 0;
  
  Serial.print("Setting volume to ");
  Serial.println(v);
  Wire.beginTransmission(MAX9744_I2CADDR);
  Wire.write(v);
  if (Wire.endTransmission() == 0){ 
    Serial.println("return true");
    return true;
  }else{
    Serial.println("return false");
    return false;
  }
}
 
// Read in + and - characters to set the volume.
void loop() {
 for(int i=30; i<63; i++){
  setvolume(i);
  delay(30);
 }
 for(int i=63; i>30; i--){
  setvolume(i);
  delay(30);
 }
}
