#include "Ultrasonic.h"

const byte echoPin= 6; 
const byte trigPin= 12;

HCSR04 sensor(echoPin,trigPin);

int distance=0;
bool cnt;
void setup()
{
  pinMode(trigPin,OUTPUT);
  pinMode(echoPin,INPUT);
  Serial.begin(9600);
  Serial.println("HC-SR04 with classes test by Mishu");
}

void loop()
{
    cnt=false;

    for(int i=0;i<10;i++){
      distance=sensor.getDistance();
      if(distance<100){
        cnt=true;
        break;
      }
      
    }
    if(cnt==true)
      Serial.println("Miscare detectata...");
    else
      Serial.println("Nu este miscare...");

     delay(1000);
}
 
