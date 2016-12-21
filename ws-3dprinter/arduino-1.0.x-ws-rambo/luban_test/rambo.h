#ifndef RAMBO_H
#define RAMBO_H

#include <Arduino.h>

namespace rambo{
  void portStep();
  void portDirection(byte dir);
  void portEnable(byte en);
  void portSetMicroSteps(byte ms);
}
#endif
