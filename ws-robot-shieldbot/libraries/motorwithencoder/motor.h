/*
 * motor.h
 *
 *  Created on: 2014年7月19日
 *      Author: caixiaoliang
 */

#ifndef MOTOR_H_
#define MOTOR_H_
#include <stdint.h> // Needed for uint8_t, uint16_t etc.
#include <Arduino.h>
#include "Usb.h"  //this there is very important ,这里有包含了avrpins.h,重新写了一个引脚快速定义拉高拉低的函数
const uint16_t PWM_FREQUENCY = 20000; // The motor driver can handle a PWM frequency up to 20kHz
const uint16_t PWMVALUE = F_CPU / PWM_FREQUENCY / 2; // The frequency is given by F_CPU/(2*N*ICR) - where N is the prescaler, prescaling is used so the frequency is given by F_CPU/(2*ICR) - ICR = F_CPU/PWM_FREQUENCY/2
//const uint16_t PWMVALUE = 250;
/* Used to make commands more readable */
enum Command {
  updatePS3,
  updatePS4,
  updateWii,
  updateXbox,
  updateSpektrum,
  stop,
  forward,
  backward,
  left,
  right,
  imu,
  joystick,
};
//Command lastCommand; // This is used set a new targetPosition

/* Left motor *///小车左轮子，INA,INB,和PWM三个引脚设置
#define M1A P23
#define M1B P24
#define PWM1A P18

/* Right motor *///小车右轮子，INA,INB,和PWM三个引脚设置
#define M2A P25
#define M2B P26
#define PWM1B P17

/* Pins connected to the motor drivers diagnostic pins */
#define M1EN P21 //左电机驱动芯片使能端
#define M2EN P22 //右电机驱动芯片使能端

/* Encoders */
#define EN1A P15 //左编码器使能引脚1
#define EN1B P30 //左编码 器使能引脚2

#define EN2A P16 //右编码器使能引脚1
#define EN2B P31 //右编码器使能引脚2

#define leftEncoder1Pin 15 // Used for attachInterrupt//用于中断
#define rightEncoder1Pin 16
#define leftEncoder2Pin 30 // Used for pin change interrupt
#define rightEncoder2Pin 31

#define LED MAKE_PIN(LED_BUILTIN) // LED_BUILTIN is defined in pins_arduino.h in the hardware add-on

/* Counters used to count the pulses from the encoders */
//编码器根据脉冲计数
//volatile int32_t leftCounter = 0;
//volatile int32_t rightCounter = 0;

class Motor
{
public:
	    //Motor();//构造函数
		void moveMotor(Command motor, Command direction, double speedRaw);
		void stopMotor(Command motor);
		void setPWM(Command motor, uint16_t dutyCycle);
		void stopAndReset();
		void leftEncoder();
		void rightEncoder();
		int32_t readLeftEncoder();
		int32_t readRightEncoder();
		int32_t getWheelsPosition();
};



#endif /* MOTOR_H_ */
