#define TOPSPEED 200
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
  
  analogWrite(left_motor_pwm, 100);  //set both motors to run at (100/255 = 39)% duty cycle (slow)
  analogWrite(right_motor_pwm, 100); 
}

void loop() {
  controlByRC();
}

void controlByRC(){
  if (Serial.available()) {
    int cmd = Serial.read();
    Serial.print("receved cmd:[");
    Serial.print(cmd, BYTE);
    Serial.println("]");
    switch (cmd) {
      case 'f':
        _motorMoveforward();
        break;
      case 'b':
        _motorMoveBackward();
        break;
      case 'l':
        _turnLeft();
        break;
      case 'r':
        _turnRight();
        break;
      case 's': 
        _motorStop();
        break;
      default: 
        _motorStop();
        break;
      }
      //Serial.println("Please input next RF command!");
  }
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
