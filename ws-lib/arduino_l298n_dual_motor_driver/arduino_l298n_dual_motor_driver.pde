#include <Servo.h>
#define TOPSPEED 1000
// THE SWITCH FLAG
// whether print the debug messge to Serial Port
boolean isDebugMsgEnable = false;
boolean isUIMsgEnable = true;

// SERVO SCANNING VARIABLES //
Servo myservo;  // create servo object to control a servo
int servoPosition = 0;    // variable to store the servo position
const int SERVO_PIN = 12;
int floorState = 0;
long frontReading = 0;
boolean scanIncrement = true;  //increase position?
byte servoIncrementValue = 6;
byte servoDecrementValue = 6;

// TRANSCEIVER VARIABLES //
int notFoundSensitivity = 80;
// TRANSCEIVER VARIABLES //
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
int index = 0;


// CONSTANTS //
const int MOTOR_SPEED = 600;

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

  myservo.attach(SERVO_PIN);  // attaches the servo on pin 9 to the servo object
  myservo.write(0);
  delay(1500);
}

void loop() {
  scan();
  move();
}

void move()
{
  if(servoPosition >= 0 && servoPosition <= 84 && frontReading > 550){ //Object on the right
    //Serial.println("Object on the right, ----------> turnLeft");
    _turnLeft();
  }
  else if((servoPosition >= 85 && servoPosition <= 105) && frontReading > 600){ // Object in front
    //Serial.println("Object in front, ----------> turnAround");
    turnAround();
  }
  else if((servoPosition >= 106 && servoPosition <= 180) && frontReading > 550){ // Object on the left
    //Serial.println("Object on the left, ----------> turnRight");
    _turnRight();
  }
  else{
    //Serial.println("Clear, ----------> moveTowardBeacon");
    moveTowardBeacon();
  }
}

void scan()
{
  scanIncrement ? servoPosition+=servoIncrementValue : servoPosition-=servoDecrementValue; //increment or decrement current position
  if (servoPosition >= 180){
    scanIncrement = false;
    servoPosition = 180;
  } 
  else if (servoPosition <= 1){
    scanIncrement = true;
    servoPosition = 1;
  }
  frontReading = measureFront();
  Serial.print(servoPosition);
  Serial.print("|");
  Serial.print(frontReading);
  Serial.print(";");
  myservo.write(servoPosition);
  delay(10);
}

long measureFront()
{
  return analogRead(0);
}


void moveTowardBeacon()
{
  readTransceiverandSetDirection();
  
  if(modeOfDirections == 4){ // or West
    Serial.println("turnLeft");
    _turnLeft();
  } else if(modeOfDirections == 3) { // South
    Serial.println("motorMoveBackward");
    _motorMoveBackward();
  } else if(modeOfDirections == 2) { // East
    Serial.println("turnRight");
    _turnRight();
  } else if(modeOfDirections == 1){ //North
    Serial.println("motorMoveForward");
    _motorMoveForward();
  }
}


//  BEACON LOGIC  //
void readTransceiverandSetDirection(){
  west = analogRead(2); //left
  south = analogRead(3); //back
  east = analogRead(4); //right
  north = analogRead(5); //front
 
  Serial.println("");  
  Serial.print("The 4 IR value is[front:");
  Serial.print(north);
  Serial.print("-");
  Serial.print("back:");
  Serial.print(south);
  Serial.print("-");
  Serial.print("left:");
  Serial.print(west);
  Serial.print("-");
  Serial.print("right:");
  Serial.print(east);
  Serial.println("]");
  
  getDirection();
  setModeOfDirections();
}

void getDirection(){   
  int minValue = 30;   
  if(minValue >= west){
    minValue = west;
    dir = 4;
  }
  if(minValue >= south){
    minValue = south;
    dir = 3;
  }
  if(minValue >= east){
    minValue = east;
    dir = 2;
  }
  if(minValue >= north){
    minValue = north;
    dir = 1;
  }

  /*
  Serial.print("dir is:[");
  Serial.print(dir);
  Serial.println("]");
  */
  addDirectionToReadings();

  if(dir == 1){
    Serial.println("N");
  }else if(dir == 2){
    Serial.println("E");
  }else if(dir == 3){
    Serial.println("S");
  }else if(dir == 4){
    Serial.println("W");
  }
}

void addDirectionToReadings(){
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
  int directionCounts[4] = { 0,0,0,0 }; //{North(1), East(2), South(3), West(4)}

  for (int i = 1; i < NUM_READINGS; ++i){
    //Serial.print(directionReadings[i]);
    //Serial.print("[");
    ++directionCounts[directionReadings[i]-1];
    //Serial.print(directionCounts[directionReadings[i]-1]);
    //Serial.print("]");
  }

  //Determine mode of directions from count array
  //Serial.println("");
  int modeCount[2] = { 1,directionCounts[0]  }; //This array holds the current maximum count and the direction it points to.
  for(int i = 0; i < 4; ++i){
    //Serial.print(directionCounts[i]);
    //Serial.print("|");
    if(directionCounts[i] >= modeCount[1]){
      modeCount[0] = i + 1; // set direction
      modeCount[1] = directionCounts[i]; //set count
    }
  }

  modeOfDirections = modeCount[0];
  //Serial.println("");
  //Serial.print("Direction Mode: ");
  //Serial.println(modeOfDirections);
}

void turnAround(){
  _motorStop();
  delay(500);
  _motorMoveForward();
  delay(300);
  _turnLeft();
  delay(300);
  _motorStop();
  //runAway = true;
}

void _turnLeft() {
  if(isDebugMsgEnable){
    Serial.println("turnLeft");
  }
  _leftMotorBackward();
  _rightMotorForward();
}

void _turnRight() {
  if(isDebugMsgEnable){
    Serial.println("turnRight");
  }
  _leftMotorForward();
  _rightMotorBackward();
}

void _motorMoveForward() {
  if(isDebugMsgEnable){
    Serial.println("motorMoveForward");
  }
  _leftMotorForward();
  _rightMotorForward();
}

void _motorMoveBackward() {
  if(isDebugMsgEnable){
    Serial.println("motorMoveBackward");
  }
  _leftMotorStop();
  _rightMotorStop();
  _leftMotorBackward();
  _rightMotorBackward();
}

void _motorSeedUp(){
  if(isDebugMsgEnable){
    Serial.println("motorSeedUp");
  }
  for (int i = 0; i == TOPSPEED; i++) {
    analogWrite(left_motor_pwm, i);
    analogWrite(right_motor_pwm, i); 
  }
}

void _motorSlowToStop(){
  if(isDebugMsgEnable){
    Serial.println("motorSlowToStop");
  }
  for (int i = TOPSPEED; i == 0; i--) {
    analogWrite(left_motor_pwm, i);
    analogWrite(right_motor_pwm, i); 
  }
  _motorStop();
}

void _motorStop() {
  if(isDebugMsgEnable){
    Serial.println("motorStop");
  }
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
