int led_1 = 3;
int led_2 = 4;
int ldr_1 = 0;
int ldr_2 = 1;
int value_1 = 0;
int value_2 = 0;
int motor_1 = 6;
int motor_2 = 7;
int motor_3 = 8;
int motor_4 = 9;

void setup() {
  //Serial.begin(9600);
  pinMode(led_1,OUTPUT);
  pinMode(led_2,OUTPUT);
  pinMode(motor_1,OUTPUT);
  pinMode(motor_2,OUTPUT);
  pinMode(motor_3,OUTPUT);
  pinMode(motor_4,OUTPUT);
}

void loop() {
  digitalWrite(led_1,HIGH);
  digitalWrite(led_2,HIGH);
  value_1 = analogRead(ldr_1);
  value_2 = analogRead(ldr_2);
  //Serial.println(value_1);
  //Serial.println(value_2);
  if (value_1 <= 925 && value_2 <=930) forward();
  if (value_1 >= 940 && value_2 <= 930) left() ;
  if (value_2 >= 945 && value_1 <= 925) right();
}

void forward() {
  digitalWrite(motor_1,HIGH);
  digitalWrite(motor_2,LOW);
  digitalWrite(motor_3,LOW);
  digitalWrite(motor_4,HIGH);
}
 
void left() {
  digitalWrite(motor_1,LOW);
  digitalWrite(motor_2,LOW);
  digitalWrite(motor_3,LOW);
  digitalWrite(motor_4,HIGH);
 }
void right() {
  digitalWrite(motor_1,HIGH);
  digitalWrite(motor_2,LOW);
  digitalWrite(motor_3,LOW);
  digitalWrite(motor_4,LOW);
}
