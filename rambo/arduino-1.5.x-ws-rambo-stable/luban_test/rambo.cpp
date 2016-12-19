#include <Arduino.h>
#include "pins.h"
#include "rambo.h"

void rambo::portStep(){
  PORTC = B11111111;
  delayMicroseconds(1);
  PORTC = B11100000;
  return;
}

void rambo::portDirection(byte dir){
  if(dir)PORTL = B11111111;
  else PORTL = B00111000;
  return;
}

void rambo::portEnable(byte en){
  if(en)PORTA = B00000000;
  else PORTA = B11111000;
  return;
}

void rambo::portSetMicroSteps(byte ms){
  switch(ms) {
  case 1 : 
    {
      digitalWrite(X_MS1_PIN, LOW);
      digitalWrite(X_MS2_PIN, LOW);
      digitalWrite(Y_MS1_PIN, LOW);
      digitalWrite(Y_MS2_PIN, LOW);
      digitalWrite(Z_MS1_PIN, LOW);
      digitalWrite(Z_MS2_PIN, LOW);
      digitalWrite(E0_MS1_PIN, LOW);
      digitalWrite(E0_MS2_PIN, LOW);
      digitalWrite(E1_MS1_PIN, LOW);
      digitalWrite(E1_MS2_PIN, LOW);
      break;
    }
  case 2 : 
    {
      digitalWrite(X_MS1_PIN, HIGH);
      digitalWrite(X_MS2_PIN, LOW);
      digitalWrite(Y_MS1_PIN, HIGH);
      digitalWrite(Y_MS2_PIN, LOW);
      digitalWrite(Z_MS1_PIN, HIGH);
      digitalWrite(Z_MS2_PIN, LOW);
      digitalWrite(E0_MS1_PIN, HIGH);
      digitalWrite(E0_MS2_PIN, LOW);
      digitalWrite(E1_MS1_PIN, HIGH);
      digitalWrite(E1_MS2_PIN, LOW);
      break;   
    }
  case 4 : 
    {
      digitalWrite(X_MS1_PIN, LOW);
      digitalWrite(X_MS2_PIN, HIGH);
      digitalWrite(Y_MS1_PIN, LOW);
      digitalWrite(Y_MS2_PIN, HIGH);
      digitalWrite(Z_MS1_PIN, LOW);
      digitalWrite(Z_MS2_PIN, HIGH);
      digitalWrite(E0_MS1_PIN, LOW);
      digitalWrite(E0_MS2_PIN, HIGH);
      digitalWrite(E1_MS1_PIN, LOW);
      digitalWrite(E1_MS2_PIN, HIGH);
      break;  
    }
  case 16 : 
    {
      digitalWrite(X_MS1_PIN, HIGH);
      digitalWrite(X_MS2_PIN, HIGH);
      digitalWrite(Y_MS1_PIN, HIGH);
      digitalWrite(Y_MS2_PIN, HIGH);
      digitalWrite(Z_MS1_PIN, HIGH);
      digitalWrite(Z_MS2_PIN, HIGH);
      digitalWrite(E0_MS1_PIN, HIGH);
      digitalWrite(E0_MS2_PIN, HIGH);
      digitalWrite(E1_MS1_PIN, HIGH);
      digitalWrite(E1_MS2_PIN, HIGH);
      break;   
    }

  } 
}
