#include <Servo.h>
#include <AFMotor.h>
#define TOPSPEED 200
// THE SWITCH FLAG
// whether print the debug messge to Serial Port
boolean isDebugMsgEnable = true;
boolean isUIMsgEnable = true;

const int MOTOR_SPEED = 150;

// MOTOR VARIABLES //
const int LEFT_MOTOR_1 = 1;
const int LEFT_MOTOR_2 = 2;
const int RIGHT_MOTOR_1 = 3;
const int RIGHT_MOTOR_2 = 4;

AF_DCMotor leftMotor1(LEFT_MOTOR_1, MOTOR12_2KHZ);
AF_DCMotor leftMotor2(LEFT_MOTOR_2, MOTOR12_2KHZ);
AF_DCMotor rightMotor1(RIGHT_MOTOR_1, MOTOR12_2KHZ);
AF_DCMotor rightMotor2(RIGHT_MOTOR_2, MOTOR12_2KHZ); 

void setup()
{
  Serial.begin(9600);
  leftMotor1.setSpeed(MOTOR_SPEED);
  leftMotor2.setSpeed(MOTOR_SPEED);
  rightMotor1.setSpeed(MOTOR_SPEED);
  rightMotor2.setSpeed(MOTOR_SPEED);
  delay(500);
} 

void loop()
{
  move();
} 

void move()
{
  moveForward();
  delay(300);
  moveBackward();
  delay(300);
}

void moveForward(){
  rightMotor1.run(FORWARD);
  leftMotor1.run(FORWARD);
  rightMotor2.run(FORWARD);
  leftMotor2.run(FORWARD);
}

void turnLeft(){
  rightMotor1.run(BACKWARD);
  leftMotor1.run(FORWARD);
  rightMotor2.run(BACKWARD);
  leftMotor2.run(FORWARD);
}

void moveBackward(){
  rightMotor1.run(RELEASE);
  leftMotor1.run(RELEASE);
  rightMotor2.run(RELEASE);
  leftMotor2.run(RELEASE);
  
  rightMotor1.run(BACKWARD);
  leftMotor1.run(BACKWARD);
  rightMotor2.run(BACKWARD);
  leftMotor2.run(BACKWARD);
}

void turnRight(){
  rightMotor1.run(FORWARD);
  leftMotor1.run(BACKWARD);
  rightMotor2.run(FORWARD);
  leftMotor2.run(BACKWARD);
}

void speedUp(){
  for (int i=0; i==TOPSPEED; i++) {
    rightMotor1.setSpeed(i);
    leftMotor1.setSpeed(i);
    rightMotor2.setSpeed(i);
    leftMotor2.setSpeed(i);
  }
}

void slowToStop(){
  for (int i=TOPSPEED; i==0; i--) {
    rightMotor1.setSpeed(i);
    leftMotor1.setSpeed(i);
    rightMotor2.setSpeed(i);
    leftMotor2.setSpeed(i);
  }
  rightMotor1.run(RELEASE);
  leftMotor1.run(RELEASE);
  rightMotor2.run(RELEASE);
  leftMotor2.run(RELEASE);
}

void stop(){
  rightMotor1.run(RELEASE);
  leftMotor1.run(RELEASE);
  rightMotor2.run(RELEASE);
  leftMotor2.run(RELEASE);
  delay(500);
}

void turnAround(){
  stop();
  delay(500);
  moveBackward();
  delay(300);
  turnLeft();
  delay(300);
  stop();
  //runAway = true;
}
