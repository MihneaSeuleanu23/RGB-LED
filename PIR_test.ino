const int PIR_pin=12;
int PIR_value=0; //valoare pentru statusul pinului
char PIR_state=0; // presupunem ca la inceput nu exista miscare

unsigned long previousMillis=0;
long interval=10000; //10s

void PIR();
int mean_PIR();

void setup() {
  pinMode(LED_BUILTIN,OUTPUT);
  pinMode(PIR_pin,INPUT);
  Serial.begin(9600);
  delay(1000);
}

void loop() 
{
    PIR();
    
}


void PIR()
{
  
  unsigned long currentMillis=millis();
  if(currentMillis-previousMillis>interval){
    previousMillis=currentMillis;
    PIR_value=digitalRead(PIR_pin);
    if(PIR_value==HIGH){
      digitalWrite(LED_BUILTIN,HIGH);
      if(PIR_state==0){
        Serial.println("Motion detected...");
        PIR_state=1;  //vrem sa contorizam doar schimbarile de stare ale senzorului PIR, adica sa afiseze o singura data ca a detectat miscare
      }
    }else{
      digitalWrite(LED_BUILTIN,LOW);
      if(PIR_state==1){
        Serial.println("Motion not detected!");
        PIR_state=0;
      }
    }
    
  }
}
