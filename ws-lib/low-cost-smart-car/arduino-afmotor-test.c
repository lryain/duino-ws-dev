#include <Servo.h>
#include <AFMotor.h>
#define TOPSPEED 200
// THE SWITCH FLAG
// whether print the debug messge to Serial Port
boolean isDebugMsgEnable = true;
boolean isUIMsgEnable = true;

const int MOTOR_SPEED = 100;

// MOTOR VARIABLES //
const int LEFT_MOTOR_PIN = 1;
const int RIGHT_MOTOR_PIN = 2;

AF_DCMotor rightMotor(RIGHT_MOTOR_PIN, MOTOR12_2KHZ);
AF_DCMotor leftMotor(LEFT_MOTOR_PIN, MOTOR12_2KHZ); 

void setup()
{
  Serial.begin(9600);
  rightMotor.setSpeed(MOTOR_SPEED);
  leftMotor.setSpeed(MOTOR_SPEED);
  delay(500);
} 

void loop()
{
  move();
} 

void move()
{
  moveForward();
  delay(2500);
  speedUp();
  delay(2500);
  turnLeft();
  delay(2500);
  slowToStop();
  delay(2500);
  
  turnAround();
  delay(2500);
  speedUp();
  delay(2500);
  turnRight();
  delay(2500);
}

void moveForward(){
  printDebugMsg("Move Forward");
  rightMotor.run(FORWARD);
  leftMotor.run(FORWARD);
}

void speedUp(){
  for (int i=0; i==TOPSPEED; i++) {
    rightMotor.setSpeed(i);
    leftMotor.setSpeed(i);
  }
}

void slowToStop(){
  for (int i=TOPSPEED; i==0; i--) {
    rightMotor.setSpeed(i);
    leftMotor.setSpeed(i);
  }
  rightMotor.run(RELEASE);
  leftMotor.run(RELEASE);
}

void turnLeft(){
  printDebugMsg("Turn Left");
  rightMotor.run(BACKWARD);
  leftMotor.run(FORWARD);
}

void turnRight(){
  printDebugMsg("Turn Right");
  rightMotor.run(FORWARD);
  leftMotor.run(BACKWARD);
}

void stop(){
  printDebugMsg("Stop");
  rightMotor.run(RELEASE);
  leftMotor.run(RELEASE);
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

void moveBackward(){
  printDebugMsg("Move Backward");
  rightMotor.run(RELEASE);
  leftMotor.run(RELEASE);

  rightMotor.run(BACKWARD);
  leftMotor.run(BACKWARD);
}

// boolean isUIMsgEnable = false;
void printUIMsg(char* msg){
  if(isUIMsgEnable){
    Serial.print(msg);
  }
}
void printUIMsg(int msg){
  if(isUIMsgEnable){
    Serial.print(msg);
  }
}

// boolean isDebugMsgEnable = false;
void printDebugMsg(char* msg){
  if(isDebugMsgEnable){
    Serial.println(msg);
  }
}
void printDebugMsg(int msg){
  if(isDebugMsgEnable){
    Serial.println(msg);
  }
}