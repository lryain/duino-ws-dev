// Only modify this file to include
// - function definitions (prototypes)
// - include files
// - extern variable definitions
// In the appropriate section

#ifndef _ShiledbotV1_0_H_
#define _ShiledbotV1_0_H_
#include "Arduino.h"
//add your includes for the project ShiledbotV1_0 here


//#define SHIELDBOTDEBUG 0  //表示用于测试用
// for shieldbot Version 0.9 and 1.0

#define right1 5			//define I1 interface
#define speedPinRight 6  	//enable right motor (bridge A)
#define right2 7      		//define I2 interface
#define left1 8      		//define I3 interface
#define speedPinLeft 9  	//enable motor B
#define left2 10     		//define I4 interface

// for shieldbot Version 1.1, we changed to the driver pins ,
//if you shieldbot is ver1.0 or 0.9, please using the above pin mapping;
/*#define right1 8			//define I1 interface
#define speedPinRight 9 	//enable right motor (bridge A)
#define right2 11      		//define I2 interface
#define left1 12      		//define I3 interface
#define speedPinLeft 10  	//enable motor B
#define left2 13    		//define I4 interface */

#define finder1 A0   		//define line finder S1
#define finder2 A1   		//define line finder S2
#define finder3 A2   		//define line finder S3
#define finder4 A3   		//define line finder S4
#define finder5 4    		//define line finder S5

extern int speedmotorA; //define the speed of motorA
extern int speedmotorB; //define the speed of motorB
extern  int k,n;//用于控制PWM数值
extern  uint8_t flag;//用于标志位



//end of add your includes here
#ifdef __cplusplus
extern "C" {
#endif
void loop();
void setup();
#ifdef __cplusplus
} // extern "C"
#endif

//add your function definitions for the project Shiledbot here
// library interface description

class Shieldbot
{
  // user-accessible "public" interface
  public:
	Shieldbot();
	int readS1();
	int readS2();
	int readS3();
	int readS4();
	int readS5();
	void setMaxSpeed(int);
	void setMaxSpeed(int, int);
	void setMaxLeftSpeed(int);
	void setMaxRightSpeed(int);
	void rightMotor(char);
	void leftMotor(char);
	void drive(char, char);
	void forward();
	void backward();
	void stop();
	void stopRight();
	void stopLeft();
	void fastStopLeft();
	void fastStopRight();
	void fastStop();

};


//Do not add code below this line
#endif /* _Shiledbot_H_ */
