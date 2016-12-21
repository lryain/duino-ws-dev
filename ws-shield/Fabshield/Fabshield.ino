// FabScan - http://hci.rwth-aachen.de/fabscan
//
//  Created by Francis Engelmann on 7/1/11.
//  Copyright 2011 Media Computing Group, RWTH Aachen University. All rights reserved.
//  Last Modifcation: R. Bohne 29.01.2013: changed pin mapping to Watterott FabScan Arduino Shield

#include <Servo.h> 
 
#define LIGHT_PIN 17
#define LASER_PIN 18
#define MS_PIN    19

//Stepper 1 as labeled on Shield, Turntable
#define ENABLE_PIN_0  2
#define STEP_PIN_0    3
#define DIR_PIN_0     4

//Stepper 2, Laser Stepper
#define ENABLE_PIN_1  5
#define STEP_PIN_1    6
#define DIR_PIN_1     7
#define SERVO_PIN     6 
#define SERVO_MAX     140
#define SERVO_MIN     0
#define LASER_DIR_CW  1
#define LASER_DIR_CCW 2

//Stepper 3, currently unused
#define ENABLE_PIN_2  11
#define STEP_PIN_2    12
#define DIR_PIN_2     13
  
#define TURN_LASER_OFF      200
#define TURN_LASER_ON       201
#define PERFORM_STEP        202
#define SET_DIRECTION_CW    203
#define SET_DIRECTION_CCW   204
#define TURN_STEPPER_ON     205
#define TURN_STEPPER_OFF    206
#define TURN_LIGHT_ON       207
#define TURN_LIGHT_OFF      208
#define ROTATE_LASER        209
#define FABSCAN_PING        210
#define FABSCAN_PONG        211
#define SELECT_STEPPER      212
#define LASER_STEPPER       11
#define TURNTABLE_STEPPER   10
//the protocol: we send one byte to define the action what to do.
//If the action is unary (like turnung off the light) we only need one byte so we are fine.
//If we want to tell the stepper to turn, a second byte is used to specify the number of steps.
//These second bytes are defined here below.

#define ACTION_BYTE         1    //normal byte, first of new action
#define LIGHT_INTENSITY     2
#define TURN_TABLE_STEPS    3
#define LASER1_STEPS        4
#define LASER2_STEPS        5
#define LASER_ROTATION      6
#define STEPPER_ID          7

int incomingByte = 0;
int byteType = 1;
int currStepper;
int currLaserDir = 0;
int angleIN=90;

Servo laserServo;               // Servo to adjust Laser

void step()
{
 if(currStepper == TURNTABLE_STEPPER){
   digitalWrite(STEP_PIN_0, 0);
 }

 delay(3);
 if(currStepper == TURNTABLE_STEPPER){
   digitalWrite(STEP_PIN_0, 1);
 }
 delay(3);
}

void step(int count)
{
  if(currStepper == LASER_STEPPER){
   laserrotate();
 }
  for(int i=0; i<count; i++){
    step();
  }
}

void setup() 
{ 
  // initialize the serial port
   Serial.begin(9600);
   pinMode(LASER_PIN, OUTPUT);
   pinMode(LIGHT_PIN, OUTPUT);
 
   pinMode(MS_PIN, OUTPUT);
   digitalWrite(MS_PIN, HIGH);  //HIGH for 16microstepping, LOW for no microstepping

  pinMode(ENABLE_PIN_0, OUTPUT);
  pinMode(DIR_PIN_0, OUTPUT);
  pinMode(STEP_PIN_0, OUTPUT);

  pinMode(ENABLE_PIN_1, OUTPUT);
  pinMode(DIR_PIN_1, OUTPUT);
  pinMode(STEP_PIN_1, OUTPUT);
 
  pinMode(ENABLE_PIN_2, OUTPUT);
  pinMode(DIR_PIN_2, OUTPUT);
  pinMode(STEP_PIN_2, OUTPUT);
 
 //enable turntable and laser steppers
 digitalWrite(ENABLE_PIN_0, HIGH);  //LOW to turn
 digitalWrite(ENABLE_PIN_1, HIGH);  //LOW to turn
 digitalWrite(ENABLE_PIN_2, LOW);  //LOW to turn off
 
 digitalWrite(LIGHT_PIN, 0); //turn light off
 
  laserServo.attach(STEP_PIN_0);   //
 int angle;                      // Current servo angle
 
 digitalWrite(LASER_PIN, 1); //turn laser on
 Serial.write(FABSCAN_PONG); //send a pong back to the computer so we know setup is done and that we are actually dealing with a FabScan
 
 currStepper = TURNTABLE_STEPPER;  //turntable is default stepper
} 
void laserrotate()
{
  if (currLaserDir == LASER_DIR_CCW) {angleIN++;}
  else{ angleIN--;}
  
  if (angleIN < 0) angleIN=0;
  if (angleIN > 180) angleIN=180;
  
  double angleOUT = map(angleIN,0,180,1000,2000);
  laserServo.writeMicroseconds(angleOUT);
}

void loop() 
{
    digitalWrite(ENABLE_PIN_0, 0);
            delay(3000);
} 
