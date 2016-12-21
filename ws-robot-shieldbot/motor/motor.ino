/*
 * motor.ino
 *
 *  Created on: 2014年7月19日
 *      Author: caixiaoliang
*/

#include <Arduino.h>
#include "motor.h"
#include "Usb.h"  //this there is very important ,这里有包含了avrpins.h,重新写了一个引脚快速定义拉高拉低的函数

Motor motor1;//进行一个类说明

void setup()
{
  Serial.begin(9600);

  /* Set the motordriver diagnostic pins to inputs */
  M1EN::SetDirRead();
  M2EN::SetDirRead();

  /* Setup motor pins to output */
  PWM1A::SetDirWrite();
  M1A::SetDirWrite();
  M1B::SetDirWrite();
  PWM1B::SetDirWrite();
  M2A::SetDirWrite();
  M2B::SetDirWrite();
  /* Set PWM frequency to 20kHz - see the datasheet http://www.atmel.com/Images/Atmel-8272-8-bit-AVR-microcontroller-ATmega164A_PA-324A_PA-644A_PA-1284_P_datasheet.pdf page 129-139 */
  // Set up PWM, Phase and Frequency Correct on pin 18 (OC1A) & pin 17 (OC1B) with ICR1 as TOP using Timer1
  TCCR1B = (1 << WGM13) | (1 << CS10); // Set PWM Phase and Frequency Correct with ICR1 as TOP and no prescaling
  ICR1 = PWMVALUE; // ICR1 is the TOP value - this is set so the frequency is equal to 20kHz

  /* Enable PWM on pin 18 (OC1A) & pin 17 (OC1B) */
  // Clear OC1A/OC1B on compare match when up-counting
  // Set OC1A/OC1B on compare match when down-counting
  TCCR1A = (1 << COM1A1) | (1 << COM1B1);

  Serial.print("please");
  // M1EN::Set();
  //M2EN::Set();
}

void loop() {

  if (!M1EN::IsSet() || !M2EN::IsSet()) { // Motor driver will pull these low on error
    motor1.stopMotor(left);
    motor1.stopMotor(right);
    while (1);
  }
  /*if (!M1EN::IsSet() || !M2EN::IsSet()) { // Motor driver will pull these low on error
     //buzzer::Set();
  	motor1.moveMotor(right,forward,100);
  		motor1.moveMotor(left,forward,100);
      //while (1);
    }
    */
  //checkSerialData();
  Serial.print("resive");
  motor1.moveMotor(right, forward, 100);
  motor1.moveMotor(left, forward, 100);
  delay(3000);
  motor1.moveMotor(right, backward, 100);
  motor1.moveMotor(left, backward, 100);
  delay(3000);


  Serial.print('\n');
}


