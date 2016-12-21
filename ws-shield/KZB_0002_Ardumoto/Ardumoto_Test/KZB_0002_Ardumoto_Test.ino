/*
 5/22/2012
  Timothy Holmberg
  SparkFun Electronics
  
  This code includes the ddition of fade in and out PWM. Also a stop feature. And the addition of individual functions for motor control 
  
  This was a revision of the example sketch that originated from Pete Dokter's code for Arduino that shows very basically how to control an Ardumoto 
  motor driver shield with a 5V Arduino controller board. http://www.sparkfun.com/datasheets/DevTools/Arduino/Ardumoto_test_3.pde
  
  This also includes parts of the Fading Example,  Created 1 Nov 2008 By David A. Mellis, modified 30 Aug 2011 By Tom Igoe http://arduino.cc/en/Tutorial/Fading
 
*/

int pwm_a = 3;   //PWM control for motor outputs 1 and 2 is on digital pin 3
int pwm_b = 11;  //PWM control for motor outputs 3 and 4 is on digital pin 11
int dir_a = 12;  //direction control for motor outputs 1 and 2 is on digital pin 12
int dir_b = 13;  //direction control for motor outputs 3 and 4 is on digital pin 13

void setup()
{
  pinMode(pwm_a, OUTPUT);  //Set control pins to be outputs
  pinMode(pwm_b, OUTPUT);
  pinMode(dir_a, OUTPUT);
  pinMode(dir_b, OUTPUT);
  
  analogWrite(pwm_a, 100);  //set both motors to run at (100/255 = 39)% duty cycle (slow)
  analogWrite(pwm_b, 100);
  
} 

void loop()
{ 
  right();
  delay(2000);
   left();
  delay(2000);
  forward();      //continue full speed forward
  delay(2000);    
  backward();     //full speed backward
  delay(2000);
}

void right() //full speed forward
{ 
  digitalWrite(dir_a, LOW);  //Reverse motor direction, 1 high, 2 low
  digitalWrite(dir_b, HIGH);  //Reverse motor direction, 3 low, 4 high  
  analogWrite(pwm_a, 255);    //set both motors to run at (100/255 = 39)% duty cycle
  analogWrite(pwm_b, 255);
}

void left() //full speed forward
{ 
  digitalWrite(dir_a, HIGH);  //Reverse motor direction, 1 high, 2 low
  digitalWrite(dir_b, LOW);  //Reverse motor direction, 3 low, 4 high  
  analogWrite(pwm_a, 255);    //set both motors to run at (100/255 = 39)% duty cycle
  analogWrite(pwm_b, 255);
}

void forward() //full speed forward
{ 
  digitalWrite(dir_a, HIGH);  //Reverse motor direction, 1 high, 2 low
  digitalWrite(dir_b, HIGH);  //Reverse motor direction, 3 low, 4 high  
  analogWrite(pwm_a, 255);    //set both motors to run at (100/255 = 39)% duty cycle
  analogWrite(pwm_b, 255);
}

void backward() //full speed backward
{
  digitalWrite(dir_a, LOW);  //Set motor direction, 1 low, 2 high
  digitalWrite(dir_b, LOW);  //Set motor direction, 3 high, 4 low
  analogWrite(pwm_a, 255);   //set both motors to run at 100% duty cycle (fast)
  analogWrite(pwm_b, 255);
}

