#include "balanbot.h"

#if defined(ENABLE_SPP) || defined(ENABLE_PS3) || defined(ENABLE_PS4) || defined(ENABLE_WII) || defined(ENABLE_XBOX) || defined(ENABLE_ADK)
#define ENABLE_USB
USB Usb; // This will take care of all USB communication
#else
#define _usb_h_ // Workaround include trap in the USB Host library
#include <avrpins.h> // Include this from the USB Host library
#endif

#if defined(ENABLE_SPP) || defined(ENABLE_PS3) || defined(ENABLE_PS4) || defined(ENABLE_WII)
#define ENABLE_BTD
#include <usbhub.h> // Some dongles can have a hub inside
USBHub Hub(&Usb); // Some dongles have a hub inside
BTD Btd(&Usb); // This is the main Bluetooth library, it will take care of all the USB and HCI communication with the Bluetooth dongle
#endif

void setup()
{
	Serial.begin(115200);
	buzzer::SetDirWrite();//set up the buzzer pin 拉高蜂鸣器
}

void loop()
{
    	
  buzzer::Set();
        delay(100);
        buzzer::Clear();
        delay(1000);
}







