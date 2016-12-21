// variables to take x number of readings and then average them
// to remove the jitter/noise from the DYP-ME007 sonar readings
const int numOfReadings = 10; // number of readings to take/ items in thearray
int readings[numOfReadings]; // stores the distance readings in an array
int arrayIndex = 0; // arrayIndex of the current item in thearray
int total = 0; // stores the cumlative total
int averageDistance = 0; // stores the average value
// setup pins and variables for DYP-ME007 sonar device
int echoPin = 2; // DYP-ME007 echo pin (digital 2)
int initPin = 3; // DYP-ME007 trigger pin (digital 3)
unsigned long pulseTime = 0; // stores the pulse in Micro Seconds
unsigned long distance = 0; // variable for storing the distance (cm)
// setup pins/values for LED
int redLEDPin = 13; // Red LED, connected to digital PWMpin 9
int redLEDValue = 0; // stores the value of brightness for the LED (0 = fully off, 255 = fully on)
//setup
void setup() {
pinMode(redLEDPin, OUTPUT); // sets pin 9 as output
pinMode(initPin, OUTPUT); // set init pin 3 as output
pinMode(echoPin, INPUT); // set echo pin 2 as input
// create array loop to iterate over every item in the array
for (int thisReading = 0; thisReading < numOfReadings; thisReading++) {
readings[thisReading] = 0;
}
// initialize the serial port, lets you view the
// distances being pinged if connected to computer
Serial.begin(9600);
}
// execute
void loop() {
digitalWrite(initPin, HIGH); // send 10 microsecond pulse
delayMicroseconds(10); // wait 10 microseconds before turning off
digitalWrite(initPin, LOW); // stop sending the pulse
pulseTime = pulseIn(echoPin, HIGH); // Look for a return pulse, it should be high as the pulse goes low-high-low
distance = pulseTime/58; // Distance = pulse time / 58 to convert to cm.
total= total - readings[arrayIndex]; // subtract the last distance
readings[arrayIndex] = distance; // add distance reading to array
total= total + readings[arrayIndex]; // add the reading to the total
arrayIndex = arrayIndex + 1; // go to the next item in the array
// At the end of the array (10 items) then start again
if (arrayIndex >= numOfReadings) {
arrayIndex = 0;
}
averageDistance = total / numOfReadings; // calculate the average distance
// if the distance is less than 255cm then change the brightness of the LED
if (averageDistance < 255) {
redLEDValue = 255 - averageDistance; // this means the smaller the distance the brighterthe LED.
}
analogWrite(redLEDPin, redLEDValue); // Write current value to LED pins
Serial.println(averageDistance, DEC); // print out the average distance to thedebugger
delay(100); // wait 100 milli seconds before looping again
}
