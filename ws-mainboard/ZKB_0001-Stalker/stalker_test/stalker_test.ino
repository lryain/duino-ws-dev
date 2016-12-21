/*
  SD card datalogger

 This example shows how to log data from three analog sensors
 to an SD card using the SD library.

 The circuit:
 * analog sensors on analog ins 0, 1, and 2
 * SD card attached to SPI bus as follows:
 ** MOSI - pin 11
 ** MISO - pin 12
 ** CLK - pin 13
 ** CS - pin 10

 created  24 Nov 2010
 modified 9 Apr 2012
 by Tom Igoe

 This example code is in the public domain.

 */

#include <SPI.h>
#include <SD.h>
#include <Wire.h>
#include <Wire.h>
#include "DS3231.h"
#include <Digital_Light_TSL2561.h>

// On the Ethernet Shield, CS is pin 10. Note that even if it's not
// used as the CS pin, the hardware CS pin (10 on most Arduino boards,
// 53 on the Mega) must be left as an output or the SD library
// functions will not work.
const int chipSelect = 10;
DS3231 RTC; //Create the DS3231 object
char weekDay[][4] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat" };
char CH_status_print[][4]=
  {
    "off","on ","ok ","err"
  };
DateTime dt(2016, 05, 27, 12, 00, 0, 0);
File root;

void setup()
{
  // Open serial communications and wait for port to open:
  Serial.begin(57600);
  analogReference(INTERNAL);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }
    Wire.begin();
    TSL2561.init();
    RTC.begin();
    RTC.adjust(dt); //Adjust date-time as defined 'dt' above 

  Serial.print("Initializing SD card...");
  // make sure that the default chip select pin is set to
  // output, even if you don't use it:
  pinMode(10, OUTPUT);

  // see if the card is present and can be initialized:
  if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
    // don't do anything more:
    return;
  }
  Serial.println("card initialized.");
  
  //root = SD.open("/");
  
  //printDirectory(root, 0);
  
  //Serial.println("printDirectory done!");
  
  // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.
  root = SD.open("test.txt", FILE_WRITE);
  
  // if the file opened okay, write to it:
  if (root) {
    Serial.print("Writing to test.txt...");
    root.println("testing 1, 2, 3.");
	// close the file:
    root.close();
    Serial.println("done.");
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening test.txt");
  }
  
  // re-open the file for reading:
  root = SD.open("test.txt");
  if (root) {
    Serial.println("test.txt:");
    
    // read from the file until there's nothing else in it:
    while (root.available()) {
    	Serial.write(root.read());
    }
    // close the file:
    root.close();
  } else {
  	// if the file didn't open, print an error:
    Serial.println("error opening test.txt");
  }
}

void loop()
{

  delay(500);

   unsigned char CHstatus = read_charge_status();//read the charge status
    DateTime now = RTC.now(); //get the current date-time
    Serial.print(now.year(), DEC);
    Serial.print('/');
    Serial.print(now.month(), DEC);
    Serial.print('/');
    Serial.print(now.date(), DEC);
    Serial.print(' ');
    Serial.print(now.hour(), DEC);
    Serial.print(':');
    Serial.print(now.minute(), DEC);
    Serial.print(':');
    Serial.print(now.second(), DEC);
    Serial.print('-');
    Serial.print(weekDay[now.dayOfWeek()]);
   Serial.print('-');
  Serial.print("charge status -->");
  Serial.print(CH_status_print[CHstatus]);
  Serial.print(" charge voltage -->");
  Serial.print(analogRead(7));
  Serial.print('-');
     unsigned long  Lux;
    TSL2561.getLux();
        Serial.print("The Light value is: ");
    Serial.println(TSL2561.calculateLux(0,0,1));
}

void printDirectory(File dir, int numTabs) {
  // Begin at the start of the directory
  dir.rewindDirectory();
  
  while(true) {
     File entry =  dir.openNextFile();
     if (! entry) {
       // no more files
       //Serial.println("**nomorefiles**");
       break;
     }
     for (uint8_t i=0; i<numTabs; i++) {
       Serial.print('\t');   // we'll have a nice indentation
     }
     // Print the 8.3 name
     Serial.print(entry.name());
     // Recurse for directories, otherwise print the file size
     if (entry.isDirectory()) {
       Serial.println("/");
       printDirectory(entry, numTabs+1);
     } else {
       // files have sizes, directories do not
       Serial.print("\t\t");
       Serial.println(entry.size(), DEC);
     }
     entry.close();
   }
}
 
unsigned char read_charge_status(void)
{
  unsigned char CH_Status=0;
  unsigned int ADC6=analogRead(6);
  if(ADC6>900)
  {
    CH_Status = 0;//sleeping
  }
  else if(ADC6>550)
  {
    CH_Status = 1;//charging
  }
  else if(ADC6>350)
  {
    CH_Status = 2;//done
  }
  else
  {
    CH_Status = 3;//error
  }
  return CH_Status;
}
