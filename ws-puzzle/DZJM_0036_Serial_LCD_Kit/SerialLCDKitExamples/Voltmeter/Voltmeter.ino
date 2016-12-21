/*

Arduino Voltmeter
written by N.Poole - SparkFun Electronics
LCD Code Adapted from Jim Lindblom
Apathyware License 2013 

This code turn your Serial LCD Kit into a voltmeter that can measure a DC voltage up to 20V. 
This is accomplished by implimenting a voltage divider before reading the voltage using the ATMega's internal ADC. 

Pressing the pushbutton will put the meter into continuity mode.

--------|                                           |---------
Positive|            330k            110k           |Negative
Probe   |----o------/\/\/\-----o----/\/\/\----o----|Probe
--------|    |                 |              |     |---------
             |                 |              |
             |                 |              |
          Arduino           Arduino          GND
             A1                A0


        GND ____/ ____ D10        GND -----O----- D11
            pushbutton                    LED


WARNING: This is not intended to be an acurate instrument for measuring voltage. I DO NOT RECOMMEND measuring high 
current supplies using this example. Measuring voltages above 20VDC will damage your ATMega. There is no reverse
polarity protection, take care not to test batteries backwards!

*/

#include <LiquidCrystal.h>
#include <EEPROM.h>

// --- EEPROM ADDRESS DEFINITIONS
#define LCD_BACKLIGHT_ADDRESS 1  // EEPROM address for backlight setting
#define BAUD_ADDRESS 2  // EEPROM address for Baud rate setting
#define SPLASH_SCREEN_ADDRESS 3 // EEPROM address for splash screen on/off
#define ROWS_ADDRESS 4  // EEPROM address for number of rows
#define COLUMNS_ADDRESS 5  // EEPROM address for number of columns

// --- SPECIAL COMMAND DEFINITIONS
#define BACKLIGHT_COMMAND 128  // 0x80
#define SPECIAL_COMMAND 254 // 0xFE
#define BAUD_COMMAND 129  // 0x81

// --- ARDUINO PIN DEFINITIONS
uint8_t RSPin = 2;
uint8_t RWPin = 3;
uint8_t ENPin = 4;
uint8_t D4Pin = 5;
uint8_t D5Pin = 6;
uint8_t D6Pin = 7;
uint8_t D7Pin = 8;
uint8_t BLPin = 9;

char inKey;  // Character received from serial input
uint8_t Cursor = 0;  // Position of cursor, 0 is top left, (rows*columns)-1 is bottom right
uint8_t LCDOnOff = 1;  // 0 if LCD is off
uint8_t blinky = 0;  // Is 1 if blinky cursor is on
uint8_t underline = 0; // Is 1 if underline cursor is on
uint8_t splashScreenEnable = 1;  // 1 means splash screen is enabled
uint8_t rows = 2;  // Number rows, will be either 2 or 4
uint8_t columns = 16; // Number of columns, will be 16 or 20
uint8_t characters; // rows * columns

// initialize the LCD at pins defined above
LiquidCrystal lcd(RSPin, RWPin, ENPin, D4Pin, D5Pin, D6Pin, D7Pin);


/* ----------------------------------------------------------
  In the setup() function, we'll read the previous baud,
  screen size, backlight brightness, and splash screen state
  from EEPROM. Serial will be started at the proper baud, the
  LCD will be initialized, backlight turned on, and splash
  screen displayed (or not) according to the EEPROM states.
  ----------------------------------------------------------*/
  int reading = 0;
  float readingfinal = 0;
  boolean state = 0;
 
void setup(){
 
  pinMode(10, INPUT);
  digitalWrite(10, HIGH); //Button Input, Set internal pull-up resistors 
  pinMode(11, OUTPUT); //LED output for continuity tester
  // initialize the serial communications:
  setBaudRate(EEPROM.read(BAUD_ADDRESS));
 
  // Read rows and columns from EEPROM
  // Will default to 2x16, if not previously set
  rows = EEPROM.read(ROWS_ADDRESS);
  if (rows != 4)
    rows = 2;
  columns = EEPROM.read(COLUMNS_ADDRESS);
  if (columns != 20)
    columns = 16;
 
  // set up the LCD's number of rows and columns:
  lcd.begin(columns, rows);
 
  // Set up the backlight
  pinMode(BLPin, OUTPUT);
  setBacklight(EEPROM.read(LCD_BACKLIGHT_ADDRESS));
 
  // Do splashscreen if set
  splashScreenEnable = EEPROM.read(SPLASH_SCREEN_ADDRESS);
  if (splashScreenEnable!=0)
  {
    if (columns == 16)
    {

    }
    else
    {
      lcd.setCursor(0, 1);
      lcd.print("  www.SparkFun.com  ");
      lcd.setCursor(0, 2);
      lcd.print("   Serial LCD Kit   ");
      delay(2000);
      lcd.clear();
    }
  }
}

/*----------------------------------------------------------
  In loop(), we wait for a serial character to be
  received. Once received, the character is checked against
  all the special commands if it's not a special command the
  character (or tab, line feed, etc.) is displayed. If it is
  a special command another loop will be entered and we'll
  again wait for any further characters that are needed to
  finish the command.
  ----------------------------------------------------------*/
void loop()
{
  
  // This is how the meter switched between continuity and voltage testing modes
  for(int ldl = 0; ldl<500; ldl++){delay(1);
  if(digitalRead(10)==LOW){state = !state; lcd.clear();}
 
 
}
 
  if(state==0){ //Voltage Mode
  
  //In Voltage mode, the meter reads the center tap from the voltage divider on ADC 0 and scales the result in relation to 20V
   
    pinMode(A1, INPUT); //Set both ADC as INPUT
    pinMode(A0, INPUT);
           
  reading = analogRead(A0); //Read the ADC at the center of the voltage divider
  readingfinal = map(reading, 0, 1023, 0, 2000); //Stretch the ADC's 5V range to a number easily divisable by 20
  readingfinal = readingfinal/100; //Scale down
 
 
 //Report Voltage
      lcd.setCursor(0, 0);
      lcd.print("Volts DC: ");
      lcd.setCursor(0, 1);
      lcd.print("            ");lcd.setCursor(0, 1);
      lcd.print(readingfinal);
 

  } else { //Continuity Mode
  
  //In Continuity Mode the center of the voltage tap is set HIGH, one leg of the voltage divider prevents a short to 
  //ground. The positive tap is read into ADC 1. If there's no continuity between the probes, the V-out from ADC 0 
  //is sinked partially to ground and partially to ADC 1. When there is continuity, ADC 1 reads no voltage as ADC 0 
  //is sinked to ground through the negative probe.

    pinMode(A1, INPUT); //We'll read the positive tap
    pinMode(A0, OUTPUT); //Set voltage divider center tap HIGH
    digitalWrite(A0, HIGH);
   
   
  reading = analogRead(A1);   
      lcd.setCursor(0, 0);
      lcd.print("Continuity Test");
      lcd.setCursor(0, 1);
      lcd.print("            ");lcd.setCursor(0, 1);
      lcd.print(reading);
      //Turn on the LED 
      if(reading<500){digitalWrite(11, HIGH);}else{digitalWrite(11, LOW);}
   
  }   

}

void setBacklight(uint8_t backlightSetting)
{
  analogWrite(BLPin, backlightSetting);
  EEPROM.write(LCD_BACKLIGHT_ADDRESS, backlightSetting);
}

/* ----------------------------------------------------------
  setBaudRate() is called from SpecialCommands(). It receives
  a baud rate setting balue that should be between 0 and 10.
  The baud rate is then set accordingly, and the new value is
  written to EEPROM. If the EEPROM value hasn't been written
  before (255), this function will default to 9600. If the value
  is out of bounds 10<baud<255, no action is taken.
  ----------------------------------------------------------*/
void setBaudRate(uint8_t baudSetting)
{
  // If EEPROM is unwritten (0xFF), set it to 9600 by default
  if (baudSetting==255)
    baudSetting = 4;
   
  switch(baudSetting)
  {
    case 0:
      Serial.begin(300);
      break;
    case 1:
      Serial.begin(1200);
      break;
    case 2:
      Serial.begin(2400);
      break;
    case 3:
      Serial.begin(4800);
      break;
    case 4:
      Serial.begin(9600);
      break;
    case 5:
      Serial.begin(14400);
      break;
    case 6:
      Serial.begin(19200);
      break;
    case 7:
      Serial.begin(28800);
      break;
    case 8:
      Serial.begin(38400);
      break;
    case 9:
      Serial.begin(57600);
      break;
    case 10:
      Serial.begin(115200);
      break;
  }
  if ((baudSetting>=0)&&(baudSetting<=10))
    EEPROM.write(BAUD_ADDRESS, baudSetting);
}
