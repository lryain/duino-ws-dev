#include <Servo.h>
#include <AFMotor.h>
#define TOPSPEED 200

// THE SWITCH FLAG
// whether print the debug messge to Serial Port
boolean isDebugMsgEnable = false;
boolean isUIMsgEnable = true;

// SERVO SCANNING VARIABLES //
const int SERVO_PIN = 9;
const int MOTOR_SPEED = 100;

Servo scanServo;  // create servo object to control a servo
int servoPosition = 0;    // variable to store the servo position

int floorState = 0;
long frontReading = 0;

boolean scanIncrement = true;  //increase position?
byte servoIncrementValue = 6;
byte servoDecrementValue = 6;

// MOTOR VARIABLES //
const int LEFT_MOTOR_PIN = 3;
const int RIGHT_MOTOR_PIN = 4;

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
int index = 0;

void setup()
{
  Serial.begin(38400);
  scanServo.attach(SERVO_PIN);  // attaches the servo on pin 9 to the servo object
  scanServo.write(0); // reset servo postion
  rightMotor.setSpeed(MOTOR_SPEED);
  leftMotor.setSpeed(MOTOR_SPEED);
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

// attached a Sharp GP2Y0A02YK0F Analog Distance Sensor 20-150cm
long measureFront()
{
  return analogRead(0);
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

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
import processing.serial.*;

 // Serial Variables
 Serial serialPort;    // The serial port: 
 int baudRate = 38400; //make sure this matches the baud rate in the arduino program.
 int lf = 10;
 
 // Font Settings
 PFont font;
 float radianMultiplier;
 int[] angles; 
 
 // Sensor Variables
 String direction = "N";
 int sensorReading;
 int angle;
 int degreeIncrement = 6;
 
 int startAngle = 0;
 int endAngle = 180;
 
 int totalReadings = 0;
 
 void setup(){
   smooth();
   size(600, 400);
 
   //270 is Helvetica-Neue (my current favorite) to get a list use println(PFont.list());
   font = createFont(PFont.list()[200], 24); 
   textFont(font); 
   
   radianMultiplier = PI / 180;
 
   totalReadings = (endAngle - startAngle)/degreeIncrement;
   angles = new int[totalReadings];
   for (int i = 0; i < totalReadings; i++){
     angles[i] = 0;
   }
 
   serialPort = new Serial(this, Serial.list()[1], baudRate);
   serialPort.bufferUntil(lf);
 
   noLoop();
 }
 
void draw()
{
  background(#266014);
  renderClear();
  renderScan();
  renderDirection();
}
 
void serialEvent(Serial p) {
  String inString;
  int pipeIndex = -1;
  int semicolonIndex = -1; 
 
  String angleString;
  String sensorString;
  String dirString;
 
  String newString;
  String stepString;
 
  try {
    // the string is shaped like so: [angle]|[sensorReading];[direction] -- 6|450;N
    inString = (serialPort.readString());
    pipeIndex = inString.indexOf('|');               //find the pipe
    semicolonIndex = inString.indexOf(';');               //find the semicolon
 
    if (pipeIndex != -1) {                           //if we found the pipe
      angleString = inString.substring(0, pipeIndex);  //parse angle reading
      sensorString = inString.substring(pipeIndex+1, semicolonIndex); 
      //dirString = inString.substring(semicolonIndex + 1, inString.length()-2); //length()-2 <- strips off the linefeed
      dirString = inString.substring(semicolonIndex + 1, semicolonIndex + 2);
      angle = int(angleString);
      sensorReading = int(sensorString);
      direction = dirString;
      // prevent the array out of bound exception.
      int index = (angle/degreeIncrement) - 1;
      if(index>=0&&!(index>(angles.length-1))){
        angles[(angle/degreeIncrement) - 1] = sensorReading;
      }   
    }
  }
  catch(Exception e) {
    println(e);
  }
  redraw();
}

// Render Functions
void renderReadings(int angle, int sensor){
  noStroke();
 
  mediumFont();
  text("Angle: " + angle, 139, 50);
  text("Sensor: " + sensor, 123, 90);
}
 
void renderScan(){
  noStroke();
  fill(#424242);
  rect(0,0,400,600);
 
  stroke(#000000);
  for (int x=0; x<totalReadings; x++) {
    boolean objectDetected = angles[x] >= 450;
    if(objectDetected == true){
      fill(#980f0f, 400);
    }else{
      fill(#ffffff, 100);
    }
 
    int angle = (x * degreeIncrement) - 180;
    noStroke();
    arc(200, 325, angles[x], angles[x], radians(angle), radians(angle + 6));
    if(objectDetected == true){renderAlert();}
    renderReadings(x, angles[x]);
  }
 
  fill(#ffffff);
  rect(175,325,50,65);
}
 
void renderDirection(){
  fill(#e38a20);
  rect(400,0,200,200);
  smallFont();
  noStroke();
  renderNorth(direction.equals("N"));
  renderSouth(direction.equals("S"));
  renderWest(direction.equals("W"));
  renderEast(direction.equals("E")); 
}
 
void renderNorth(boolean isCurrent){
  if(isCurrent == true){
    fill(#2b2b2b);
    arc(500, 100, 175, 175, radians(225), radians(315)); 
  }else{
    fill(#696969, 475);
    arc(500, 100, 150, 150, radians(225), radians(315));
  } 
  fill(#ffffff);
  text("N", 492, 50);
}
 
void renderSouth(boolean isCurrent){
  if(isCurrent==true){
    fill(#2b2b2b);
    arc(500, 100, 175, 175, radians(45), radians(135));
  }else{
    fill(#696969, 475);
    arc(500, 100, 150, 150, radians(45), radians(135));
  }  
  fill(#ffffff);
  text("S", 492, 165);
}
 
void renderWest(boolean isCurrent){
  if(isCurrent==true){
    fill(#2b2b2b);
    arc(500, 100, 175, 175, radians(135), radians(225));
  }else{
    fill(#464646, 475);
    arc(500, 100, 150, 150, radians(135), radians(225));
  }  
  fill(#ffffff);
  text("W", 435, 110);
}
 
void renderEast(boolean isCurrent){
  // the 405 angle here is weird, you'd think that because you're starting at 315
  // it would be 45 (the beginning of the South arc), but
  // you have to continue around the circle adding angles
  // in when you pass the 360/0 degrees mark
  if(isCurrent==true){
    fill(#2b2b2b);
    arc(500, 100, 175, 175, radians(315), radians(405));
  }else{
    fill(#464646, 475);
    arc(500, 100, 150, 150, radians(315), radians(405));
  }  
  fill(#ffffff);
  text("E", 553, 110);
}
 
void renderAlert(){
  largeFont();
  fill(#980f0f);
  rect(400,200,200,200);
  fill(#ffffff);
  text("ALERT", 440, 305);
}
 
void renderClear(){
  mediumFont();
  fill(#ffffff);
  text("CLEAR", 450, 305);
}
 
void smallFont(){  textFont(font, 24); }
void mediumFont(){ textFont(font, 30); }
void largeFont(){  textFont(font, 40); }