// variables to take x number of readings and then average them
// to remove the jitter/noise from the DYP-ME007 sonar readings
const int numOfReadings = 10; // number of readings to take/ items in the array
int readings[numOfReadings]; // stores the distance readings in an array
int arrayIndex = 0; // arrayIndex of the current item in the array
int total = 0; // stores the cumlative total
int averageDistance = 0; // stores the average value
// setup pins and variables for DYP-ME007 sonar device
int trigPin = 24; // DYP-ME007 trigger pin (digital 3)
int echoPin = 25; // DYP-ME007 echo pin (digital 2)

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  // create array loop to iterate over every item in the array
  for (int thisReading = 0; thisReading < numOfReadings; thisReading++) {
    readings[thisReading] = 0;
  }
  // initialize the serial port, lets you view the
  // distances being pinged if connected to computer
  Serial.begin(9600);
}

void loop() {
  unsigned long distance = ping();
  //Serial.println(result, DEC);
  calcEverageDistance(distance);
}

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
  Serial.println(averageDistance, DEC); // print out the average distance to the debugger
  delay(100); // wait 100 milli seconds before looping again
  return averageDistance;
}