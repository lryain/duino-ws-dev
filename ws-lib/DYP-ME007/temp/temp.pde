
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


// sweep the servo and measure front through a ME007 Distance Sensor
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
  //frontReading = calcEverageDistance(ping());
  if(isDebugMsgEnable){
    Serial.print("the measure front value is: [");
    Serial.print(frontReading);
    Serial.println("]");
  }

  //printUIMsg(servoPosition);
  //printUIMsg("|");
  //printUIMsg(frontReading);
  //printUIMsg(";");

  scanServo.write(servoPosition);
  delay(15);
}

void move()
{
  if(servoPosition >= 0 && servoPosition <= 84 && frontReading > 550){ //Object on the left
    _turnLeft();
  }
  else if((servoPosition >= 106 && servoPosition <= 180) && frontReading > 550){ // Object on the Right
    _turnRight();
  }
  else{
    _motorStop();
  }
}

