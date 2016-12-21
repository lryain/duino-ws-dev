#include <Servo.h>
#define TOPSPEED 200
//------------------------------------------------------------------------------------------\
// THE SWITCH FLAG
// whether print the debug messge to Serial Port
boolean isDebugMsgEnable = false;
boolean isUIMsgEnable = true;

// ME007 VARIABLES
// variables to take x number of readings and then average them
// to remove the jitter/noise from the DYP-ME007 sonar readings
const int numOfReadings = 3; // number of readings to take/ items in the array
int readings[numOfReadings]; // stores the distance readings in an array
int arrayIndex = 0; // arrayIndex of the current item in the array
int total = 0; // stores the cumlative total
int averageDistance = 0; // stores the average value
// setup pins and variables for DYP-ME007 sonar device
int trigPin = 12; // DYP-ME007 trigger pin (digital 3)
int echoPin = 13; // DYP-ME007 echo pin (digital 2)

// CONSTANTS //
const int MOTOR_SPEED = 400;
long frontReading = 0;

int left_motor_pwm = 6;
int right_motor_pwm = 11;

int left_motor_1_a = 2;
int left_motor_1_b = 3;
int left_motor_2_a = 4;
int left_motor_2_b = 5;

int right_motor_1_a = 7;
int right_motor_1_b = 8;
int right_motor_2_a = 9;
int right_motor_2_b = 10;

void setup() {       
  Serial.begin(9600);  //波特率需要和APC220一致  
  // initialize the digital pin as an output.
  // Pin 13 has an LED connected on most Arduino boards:
  pinMode(left_motor_pwm, OUTPUT);  //Set control pins to be outputs
  pinMode(right_motor_pwm, OUTPUT);
  
  pinMode(left_motor_1_a, OUTPUT);
  pinMode(left_motor_1_b, OUTPUT);
  pinMode(left_motor_2_a, OUTPUT);
  pinMode(left_motor_2_b, OUTPUT);
  
  pinMode(right_motor_1_a, OUTPUT);
  pinMode(right_motor_1_b, OUTPUT);
  pinMode(right_motor_2_a, OUTPUT);
  pinMode(right_motor_2_b, OUTPUT);
  
  analogWrite(left_motor_pwm, MOTOR_SPEED);  //set both motors to run at (100/255 = 39)% duty cycle (slow)
  analogWrite(right_motor_pwm, MOTOR_SPEED); 
  
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  // create array loop to iterate over every item in the array
  for (int thisReading = 0; thisReading < numOfReadings; thisReading++) {
    readings[thisReading] = 0;
  }
}

void loop() {
  /*unsigned long distance = ping();
  Serial.print("the measure front value is: [");
  Serial.print(distance, DEC);
  Serial.println("]");*/
  
  measureFront();
  move();
}

void move(){
  if(frontReading <25){ //Object on the front
   _motorStop();
   delay(300);
   _motorMoveBackward();
  delay(300);
  _turnLeft();
  delay(450);
  _motorStop();
   delay(300);
  }
  _motorMoveforward();
}

void measureFront(){
  frontReading = calcEverageDistance(ping());
  Serial.print("the everage distance is: [");
  Serial.print(frontReading, DEC);
  Serial.println("]");
}

void _turnLeft() {
  _leftMotorBackward();
  _rightMotorForward();
}

void _turnRight() {
  _leftMotorForward();
  _rightMotorBackward();
}

void _motorMoveforward() {
  _leftMotorForward();
  _rightMotorForward();
}

void _motorMoveBackward() {
  _leftMotorBackward();
  _rightMotorBackward();
}

void _motorStop() {
  _leftMotorStop();
  _rightMotorStop();
}

void _leftMotorForward() {
  digitalWrite(left_motor_1_a, HIGH);
  digitalWrite(left_motor_1_b, LOW);
  digitalWrite(left_motor_2_a, HIGH);
  digitalWrite(left_motor_2_b, LOW); 
}

void _rightMotorForward() {
  digitalWrite(right_motor_1_a, HIGH);
  digitalWrite(right_motor_1_b, LOW);
  digitalWrite(right_motor_2_a, HIGH);
  digitalWrite(right_motor_2_b, LOW);  
}

void _leftMotorBackward() {
  digitalWrite(left_motor_1_a, LOW);
  digitalWrite(left_motor_1_b, HIGH);
  digitalWrite(left_motor_2_a, LOW);
  digitalWrite(left_motor_2_b, HIGH); 
}

void _rightMotorBackward() {
  digitalWrite(right_motor_1_a, LOW);
  digitalWrite(right_motor_1_b, HIGH);
  digitalWrite(right_motor_2_a, LOW);
  digitalWrite(right_motor_2_b, HIGH);  
}

void _leftMotorStop() {
  digitalWrite(left_motor_1_a, HIGH);
  digitalWrite(left_motor_1_b, HIGH);
  digitalWrite(left_motor_2_a, HIGH);
  digitalWrite(left_motor_2_b, HIGH); 
}

void _rightMotorStop() {
  digitalWrite(right_motor_1_a, HIGH);
  digitalWrite(right_motor_1_b, HIGH);
  digitalWrite(right_motor_2_a, HIGH);
  digitalWrite(right_motor_2_b, HIGH);  
}

void _motorSeedUp(){
  for (int i = 0; i == TOPSPEED; i++) {
    analogWrite(left_motor_pwm, i);
    analogWrite(right_motor_pwm, i); 
    delay(1000);
  }
}

void _motorSlowToStop(){
  for (int i = TOPSPEED; i == 0; i--) {
    analogWrite(left_motor_pwm, i);
    analogWrite(right_motor_pwm, i); 
    delay(1000);
  }
  _motorStop();
}

// ME007-------------------------------------------------------------------------------------------
// attached a me007 Distance Sensor
long ping() {
  digitalWrite(trigPin, HIGH); // send 10 microsecond pulse
  delayMicroseconds(10); // wait 10 microseconds before turning off
  digitalWrite(trigPin, LOW); // stop sending the pulse
  unsigned long pulseTime = pulseIn(echoPin, HIGH); // Look for a return pulse, it should be high as the pulse goes low-high-low
  return (pulseTime/58); // Distance = pulse time / 58 to convert to cm.
}

long calcEverageDistance(unsigned long distance) {
  total= total - readings[arrayIndex]; // subtract the last distance
  readings[arrayIndex] = distance; // add distance reading to array
  total= total + readings[arrayIndex]; // add the reading to the total
  arrayIndex = arrayIndex + 1; // go to the next item in the array
  // At the end of the array (10 items) then start again
  if (arrayIndex >= numOfReadings) {
    arrayIndex = 0;
  }
  averageDistance = total / numOfReadings; // calculate the average distance
  //Serial.println(averageDistance, DEC); // print out the average distance to the debugger
  delay(100); // wait 100 milli seconds before looping again
  return averageDistance;
}
