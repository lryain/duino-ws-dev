#include <USBKeyboard.h>

void setup() 
{
  Keyboard.init();
}

void loop() 
{
  delay(5000);
  Keyboard.print("hello world");
}
