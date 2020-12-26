#ifndef Ultrasonic_h
#define Ultrasonic_h

#include <Arduino.h>

class HCSR04{
  private:
      byte echo_pin;
      byte trig_pin;
  public:
      HCSR04(const byte,const byte);
      uint16_t getMeasure();
      uint16_t getDistance();
      
};

#endif
