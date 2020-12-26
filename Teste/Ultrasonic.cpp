#include "Ultrasonic.h"

HCSR04::HCSR04(const byte echo,const byte trig)
{
  echo_pin=echo;
  trig_pin=trig;
}

uint16_t HCSR04::getMeasure()
{
    int distance;
    long duration;
    digitalWrite(trig_pin,LOW);
    delayMicroseconds(2);
    digitalWrite(trig_pin,HIGH);
    delayMicroseconds(10);
    digitalWrite(trig_pin,LOW);
    duration=pulseIn(echo_pin,HIGH);
    distance=duration*0.034/2;

    return distance;
    
}

uint16_t HCSR04::getDistance()
{
  int s=0;
  for(int i=0;i<10;i++)
      s=s+getMeasure();

  return s/10;
}
