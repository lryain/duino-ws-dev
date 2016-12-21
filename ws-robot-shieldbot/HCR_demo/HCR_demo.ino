#include "motordriver_4wd.h"
#include <seeed_pwm.h>

#include "BalancingRobotFullSize.h"
#include "Pins.h"
#include "EEPROM.h"
#include "Protocol.h"

double turningValue; // The turning value of the steering rod
uint16_t batteryLevel; // Battery level multiplied by 100 i.e. 24.50V becomes 2450
static uint8_t batteryCounter;
double PIDValue = 0;

void setup()
{
    /* Setup buzzer pin */
  buzzer::SetDirWrite();

  /* Read the PID values, target angle and other saved values in the EEPROM */
  if (!checkEEPROMVersion())
    readEEPROMValues(); // Only read the EEPROM values if they have not been restored
  else { // Indicate that the EEPROM values have been reset by turning on the buzzer
    buzzer::Set();
    delay(1000);
    buzzer::Clear();
    delay(100); // Wait a little after the pin is cleared
  }
    initSerial();

  MOTOR.init();
  /* Beep to indicate that it is now ready */
  buzzer::Set();
  delay(100);
  buzzer::Clear();
}

void loop()
{
  
   // TODO: Turn opposite when going backwards
 int contorlA = analogRead(A0);
  int contorlB = analogRead(A1);

  Serial.print("The X and Y coordinate is:");
  Serial.print(contorlA);
  Serial.print(",");
  Serial.println(contorlB);
  Serial.println(" ");
  
  contorlA *= cfg.leftMotorScaler; // Compensate for difference in some of the motors
  contorlB *= cfg.rightMotorScaler;
int a = 0;
  //Serial.print(PIDLeft); Serial.write('\t'); Serial.println(PIDRight);
      /* Set PWM Values */
  if(contorlA > 450 && contorlA <550 && contorlB > 450 && contorlB <550){
    stopAndReset();
     Serial.println("stopAndReset");
  }else if (contorlA > 550){
       a = map(contorlA, 550,1024, 0,50);
    Serial.println("forward");
    MOTOR.setSpeedDir1(a, DIRF);
    MOTOR.setSpeedDir2(a, DIRF);
  }
  else if (contorlA < 450){
       a = map(contorlA, 0,450, 50,0);
    Serial.println("backward");
    MOTOR.setSpeedDir1(a, DIRR);
    MOTOR.setSpeedDir2(a, DIRR);
  }else if (contorlB > 568){
     a = map(contorlB, 568,1024, 0,50);
    Serial.println("turnleft");
    MOTOR.setSpeedDir1(a, DIRR);
    MOTOR.setSpeedDir2(a, DIRF);
  }else if(contorlB < 468){
     a = map(contorlB, 0,468, 50,0);
    Serial.println("turnright");
    MOTOR.setSpeedDir1(a, DIRF);
    MOTOR.setSpeedDir2(a, DIRR);
  }

  Serial.print("The PWM is:");
  Serial.println(a);
    
    if (++batteryCounter > 100) {
      batteryCounter = 0;
      batteryLevel = (double)analogRead(VBAT_PIN) / 204.6 * 780.0; // It is connected to a 68k-10k voltage divider and then we multiply this by 100, so 12.50V will be equal to 1250 - the voltage divider is connected to an op amp configured as a buffer
      if (batteryLevel < 2160 && batteryLevel > 500) // Equal to 3.6V per cell (21.60V in total) - don't turn on if it's below 5V, this means that no battery is connected
        buzzer::Set();
      else
        buzzer::Clear();
      // TODO: Calibrate this value
    } else{
    //parseSerialData(); // Parse incoming serial data
  }

}
/*********************************************************************************************************
 * END FILE
 *********************************************************************************************************/

void stopAndReset() {
  MOTOR.setStop1();
  MOTOR.setStop2();
}
