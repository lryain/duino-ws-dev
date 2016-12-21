// Only modify this file to include
// - function definitions (prototypes)
// - include files
// - extern variable definitions
// In the appropriate section

#ifndef _motor_with_encoder_H_
#define _motor_with_encoder_H_
#include "Arduino.h"
//add your includes for the project motor_with_encoder here


//end of add your includes here
#ifdef __cplusplus
extern "C" {
#endif
void loop();
void setup();
#ifdef __cplusplus
} // extern "C"
#endif

//add your function definitions for the project motor_with_encoder here
#define leftEncoder1Pin 15 // Used for attachInterrupt
#define rightEncoder1Pin 16
#define leftEncoder2Pin 30 // Used for pin change interrupt
#define rightEncoder2Pin 31

#define PIN_CHANGE_INTERRUPT_VECTOR_LEFT PCINT0_vect // You should change these to match your pins, if you are in doubt, just comment them out to disable them
#define PIN_CHANGE_INTERRUPT_VECTOR_RIGHT PCINT0_vect

/* Counters used to count the pulses from the encoders */
volatile int32_t leftCounter = 0;
volatile int32_t rightCounter = 0;

uint32_t encoderTimer; // Timer used used to determine when to update the encoder values

//Do not add code below this line
#endif /* _motor_with_encoder_H_ */
