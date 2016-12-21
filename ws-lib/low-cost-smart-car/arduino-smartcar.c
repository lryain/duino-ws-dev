#include <Servo.h>
#include <AFMotor.h>

#define TOPSPEED 200

// ME007 VARIABLES
// variables to take x number of readings and then average them
// to remove the jitter/noise from the DYP-ME007 sonar readings
const int numOfReadings = 10; // number of readings to take/ items in the array
int readings[numOfReadings]; // stores the distance readings in an array
// setup pins and variables for DYP-ME007 sonar device
int trigPin = 24; // DYP-ME007 trigger pin (digital 3)
int echoPin = 25; // DYP-ME007 echo pin (digital 2)

//------------------------------------------------------------------------------------------\
// THE SWITCH FLAG
// whether print the debug messge to Serial Port
boolean isDebugMsgEnable = false;
boolean isUIMsgEnable = true;

// CONSTANTS //
const int SERVO_PIN = 9;
const int MOTOR_SPEED = 100;
const int LEFT_MOTOR_PIN = 3;
const int RIGHT_MOTOR_PIN = 4;

// GLOBAL SERVO SCANNING VARIABLES //
Servo scanServo;  // create servo object to control a servo
int servoPosition = 0;    // variable to store the servo position
long frontReading = 0;
boolean scanIncrement = true;  //increase position?
byte servoIncrementValue = 6;

// MOTOR VARIABLES //
AF_DCMotor rightMotor(RIGHT_MOTOR_PIN, MOTOR12_8KHZ);
AF_DCMotor leftMotor(LEFT_MOTOR_PIN, MOTOR12_8KHZ); 

// TRANSCEIVER VARIABLES //
int notFoundSensitivity = 500;
int west = 0;
int south = 0;
int east = 0;
int north = 0;
int dir = 0;
boolean detected = false;

// TRANSCEIVER DIRECTION MODE VARIABLES //
const int NUM_READINGS = 10;
int directionReadings[NUM_READINGS];
int modeOfDirections = 1;

void setup()
{
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  // create array loop to iterate over every item in the array
  for (int thisReading = 0; thisReading < numOfReadings; thisReading++) {
    readings[thisReading] = 0;
  }
  
  scanServo.attach(SERVO_PIN);  // attaches the servo on pin 9 to the servo object
  scanServo.write(0); // reset servo postion
  rightMotor.setSpeed(MOTOR_SPEED);
  leftMotor.setSpeed(MOTOR_SPEED);
  
  Serial.begin(9600);
  delay(1500);
} 

void loop()
{
  scan();
  move();
} 

// sweep the servo and measure front through a Sharp Analog Distance Sensor
void scan()
{
  scanIncrement ? servoPosition+=servoIncrementValue : servoPosition-=servoIncrementValue; //increment or decrement current position
  if (servoPosition >= 180){
    scanIncrement = false;
    servoPosition = 180;
  } 
  else if (servoPosition <= 1){
    scanIncrement = true;
    servoPosition = 1;
  }
  // get the everage distance via ME007
  frontReading = calcEverageDistance(ping());
  if(isDebugMsgEnable){
    Serial.print("the measure front value is: [");
    Serial.print(frontReading);
    Serial.println("]");
  }

  printUIMsg(servoPosition);
  printUIMsg("|");
  printUIMsg(frontReading);
  printUIMsg(";");

  scanServo.write(servoPosition);
  delay(15);
}

void move()
{
  if(servoPosition >= 0 && servoPosition <= 84 && frontReading > 550){ //Object on the left
    turnLeft();
  }
  else if((servoPosition >= 85 && servoPosition <= 105) && frontReading > 600){ // Object in Front
    turnAround();
  }
  else if((servoPosition >= 106 && servoPosition <= 180) && frontReading > 550){ // Object on the Right
    turnRight();
  }
  else{
    moveTowardBeacon();
  }
}

void moveTowardBeacon()
{
  readTransceiverandSetDirection();
  if(modeOfDirections == 3 || modeOfDirections == 4){ //South or West
    turnRight();
  } 
  else if(modeOfDirections == 2) { // East
    turnLeft();
  } 
  else if(modeOfDirections == 1){ //North
    moveForward();
  }
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

//  BEACON LOGIC  //
// read the four IR sensor value of four direction first 
// then calculate the direction
// finally set the mode of direction
void readTransceiverandSetDirection(){
  west = analogRead(2);
  south = analogRead(3);
  east = analogRead(4);
  north = analogRead(5);
  getDirection();
  setModeOfDirections();
}

// calculate the direction
void getDirection(){   
  int minValue = 1200;   
  if(minValue > west){
    minValue = west;
    dir = 4;
  }

  if(minValue > south){
    minValue = south;
    dir = 3;
  }

  if(minValue > east){
    minValue = east;
    dir = 2;
  }

  if(minValue > north){
    minValue = north;
    dir = 1;
  }

  addDirectionToReadings();

  if(dir == 1){
    printDebugMsg("North");
    printUIMsg("N");
  }else if(dir == 2){
    printDebugMsg("East");
    printUIMsg("E");
  }else if(dir == 3){
    printDebugMsg("South");
    printUIMsg("S");
  }else if(dir == 4){
    printDebugMsg("West");
    printUIMsg("W");
  }
}

// put the direction data into reading array
void addDirectionToReadings(){
  int index = 0;
  directionReadings[index] = dir;

  index = (index + 1);
  if (index >= NUM_READINGS)             // if we're at the end of the array...
    index = 0;
}

// =========================================
// In order to smooth out the directions readings from the
// IR transceiver, You have to take the mode (most prevalent number in a collection)
// of the directionReadings Array.  This allows the program to determine which
// direction is being read the most from the device.
// Otherwise, the readings make the robot squirrelly.
// ========================================
void setModeOfDirections(){
  int currentValue = directionReadings[0];
  int counter = 1;
  int maxCounter = 1;
  int modeValue = modeOfDirections;
  int directionCounts[4] = { 0,0,0,0 }; //{North(1), East(2), South(3), West(4)}

  for (int i = 1; i < NUM_READINGS; ++i){
    //printDebugMsg(directionReadings[i]);
    //printDebugMsg("|");
    ++directionCounts[directionReadings[i]-1];
  }

  //Determine mode of directions from count array
  printDebugMsg("");
  int modeCount[2] = { 1,directionCounts[0] }; //This array holds the current maximum count and the direction it points to.
  for(int i = 0; i < 4; ++i){
    //printDebugMsg(directionCounts[i]);
    //printDebugMsg("|");
    if(modeCount[1] >= directionCounts[i]){
      modeCount[0] = i + 1; // set direction
      modeCount[1] = directionCounts[i]; //set count
    }
  }

  modeOfDirections = modeCount[0];
  //printDebugMsg("");
  //printDebugMsg("Direction Mode: ");
  printDebugMsg(modeOfDirections);
}

boolean foundBeacon(){
  if(west < notFoundSensitivity and east < notFoundSensitivity and south < notFoundSensitivity and north < notFoundSensitivity){     
    return false;   
  }
  else{     
    return true;   
  } 
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
  int averageDistance = 0; // stores the average value
  int arrayIndex = 0; // arrayIndex of the current item in the array
  int total = total - readings[arrayIndex]; // subtract the last distance
  readings[arrayIndex] = distance; // add distance reading to array
  total= total + readings[arrayIndex]; // add the reading to the total
  arrayIndex = arrayIndex + 1; // go to the next item in the array
  // At the end of the array (10 items) then start again
  if (arrayIndex >= numOfReadings) {
    arrayIndex = 0;
  }
  averageDistance = total / numOfReadings; // calculate the average distance
  Serial.println(averageDistance, DEC); // print out the average distance to the debugger
  delay(100); // wait 100 milli seconds before looping again
  return averageDistance;
}