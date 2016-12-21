#ifndef __USBKeyboard_h__
#define __USBKeyboard_h__

#if ARDUINO >= 100
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

#include "hid_keys.h"

#define LED_NUMLOCK    (1 << 0)
#define LED_CAPSLOCK   (1 << 1)
#define LED_SCROLLLOCK (1 << 2)

class USBKeyboard {
 public:
  void init () {
    // We will talk to atmega8u2 using 9600 bps
    Serial.begin(9600);
  }
    
    
  void sendKeyStroke(byte keyStroke) {
    sendKeyStroke(keyStroke, 0);
  }

  void sendKeyStrokeUnReleased(byte keyStroke) {
    sendKeyStrokeUnReleased(keyStroke, 0);
  }

  void sendKeyStroke(byte keyStroke, byte modifiers) {
    uint8_t keyNone[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };    
    uint8_t sendKey[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };
    sendKey[0] = modifiers;
    sendKey[2] = keyStroke;
    Serial.write(sendKey, 8);          // Keycode 6  
  
    Serial.write(keyNone, 8);    // Release Key   
  }
  
  void sendKeyStrokeUnReleased(byte keyStroke, byte modifiers) {    
    uint8_t sendKey[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };
    sendKey[0] = modifiers;
    sendKey[2] = keyStroke;
    Serial.write(sendKey, 8);  
  }

  void sendKeyStrokeUnReleased(byte key1, byte key2, byte modifiers) {    
    uint8_t sendKey[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };
    sendKey[0] = modifiers;
    sendKey[2] = key1;
    sendKey[3] = key2;
    Serial.write(sendKey, 8);  
  }

  void sendKeyStrokeUnReleased(byte key1, byte key2, byte key3, byte modifiers) {    
    uint8_t sendKey[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };
    sendKey[0] = modifiers;
    sendKey[2] = key1;
    sendKey[3] = key2;
    sendKey[4] = key3;
    Serial.write(sendKey, 8);  
  }
  void sendKeyStrokeUnReleased(byte key1, byte key2, byte key3, byte key4, byte modifiers) {    
    uint8_t sendKey[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };
    sendKey[0] = modifiers;
    sendKey[2] = key1;
    sendKey[3] = key2;
    sendKey[4] = key3;
    sendKey[5] = key4;
    Serial.write(sendKey, 8);  
  }

  void sendKeyStrokeUnReleased(byte key1, byte key2, byte key3, byte key4, byte key5, byte modifiers) {    
    uint8_t sendKey[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };
    sendKey[0] = modifiers;
    sendKey[2] = key1;
    sendKey[3] = key2;
    sendKey[4] = key3;
    sendKey[5] = key4;
    sendKey[6] = key5;
    Serial.write(sendKey, 8);  
  }

  void sendKeyStrokeUnReleased(byte key1, byte key2, byte key3, byte key4, byte key5, byte key6, byte modifiers) {    
    uint8_t sendKey[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };
    sendKey[0] = modifiers;
    sendKey[2] = key1;
    sendKey[3] = key2;
    sendKey[4] = key3;
    sendKey[5] = key4;
    sendKey[6] = key5;
    sendKey[7] = key6;
    Serial.write(sendKey, 8);  
  }
  
  void sendKeyReleased() {    
    uint8_t keyNone[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };
    Serial.write(keyNone, 8);   
  }

  uint8_t readLedStatus() {
    uint8_t keyNone[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };  
    uint8_t ledStatus;
    
    Serial.write(keyNone, 8);    // Release Key
    while (Serial.available() > 0) {
      ledStatus = Serial.read();
    }
    
    return ledStatus;
  }
  
  void print(char *chp)
  {
    uint8_t buf[8] = { 0 };	/* Keyboard report buffer */
    
    while (*chp) {	    
      if ((*chp >= 'a') && (*chp <= 'z')) {
        buf[2] = *chp - 'a' + 4;
      } else if ((*chp >= 'A') && (*chp <= 'Z')) {
        buf[0] = MOD_SHIFT_LEFT;	/* Caps */
        buf[2] = *chp - 'A' + 4;
      } else if ((*chp >= '1') && (*chp <= '9')) {
        buf[2] = *chp - '1' + 30;
      } else if (*chp == '0') {
        buf[2] = KEY_0;
      } else {
        switch (*chp) {
          case ' ':
            buf[2] = KEY_SPACE;	// Space
            break;
          case '-':
            buf[2] = KEY_MINUS;
            break;
          case '=':
            buf[2] = KEY_EQUALS;
            break;
          case '[':
            buf[2] = KEY_LBRACKET;
            break;
          case ']':
            buf[2] = KEY_RBRACKET;
            break;
          case '\\':
            buf[2] = KEY_BACKSLASH;
            break;
          case ';':
            buf[2] = KEY_SEMICOLON;
            break;
          case ':':
            buf[0] = MOD_SHIFT_LEFT;	/* Caps */
            buf[2] = KEY_SEMICOLON;
            break;
            case '"':
            buf[2] = KEY_QUOTE;
            break;
          case '~':
            buf[2] = KEY_TILDE;
            break;
          case ',':
            buf[2] = KEY_COMMA;
            break;
          case '/':
            buf[2] = KEY_SLASH;
            break;
          case '@':
            buf[0] = MOD_SHIFT_LEFT;	/* Caps */
            buf[2] = KEY_2;
            break;
          default:
            /* Character not handled. To do: add rest of chars from HUT1_11.pdf */
            buf[2] = KEY_PERIOD;// Period
            break;
          }
      }
      
      Serial.write(buf, 8);	// Send keystroke
      buf[0] = 0;
      buf[2] = 0;
      Serial.write(buf, 8);	// Release key
      chp++;
    }
  }    
};

USBKeyboard Keyboard;

#endif // __USBKeyboard_h__
