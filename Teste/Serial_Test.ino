#include <Wire.h> 
//#include <LiquidCrystal_I2C.h>

const int red_pin = 10;
const int green_pin = 9;
const int blue_pin = 11;

const int PWM_max = 15;
const int FADESPEED = 50;
const byte numChars = 32;
char receivedChars[numChars];
char tempChars[numChars];        // temporary array for use when parsing

int red = 0, green = 0, blue = 0, action = 0;


// Set the LCD address to 0x27 for a 20 chars and 4 line display
//LiquidCrystal_I2C lcd(0x27, 20, 04);

boolean newData = false;

//============

void setup() {
    //lcd.begin();
    //lcd.backlight();
    //lcd.setCursor(0,0);
    //lcd.print("Comenzi: ...");
    Serial.begin(9600);
    pinMode(red_pin, OUTPUT);
    pinMode(green_pin, OUTPUT);
    pinMode(blue_pin, OUTPUT);
}

//============

void loop() {
    recvWithStartEndMarkers();
    if (newData == true) {
        strcpy(tempChars, receivedChars);
            // this temporary copy is necessary to protect the original data
            //   because strtok() used in parseData() replaces the commas with \0
        parseData();
        showParsedData();
        newData = false;
    }
    if (action==0)
      setColor(red,green,blue);
      else if (action == 1)
        loop_Fade1();
          else if (action == 2) 
            loop_Fade2();
              else if (action == 3)
                loop_HUE();
}


//-------------------------------------------------

void recvWithStartEndMarkers() {
    static boolean recvInProgress = false;
    static byte ndx = 0;
    char startMarker = '<';
    char endMarker = '>';
    char rc;

    while (Serial.available() > 0 && newData == false) {
        rc = Serial.read();

        if (recvInProgress == true) {
            if (rc != endMarker) {
                receivedChars[ndx] = rc;
                ndx++;
                if (ndx >= numChars) {
                    ndx = numChars - 1;
                }
            }
            else {
                receivedChars[ndx] = '\0'; // terminate the string
                recvInProgress = false;
                ndx = 0;
                newData = true;
            }
        }

        else if (rc == startMarker) {
            recvInProgress = true;
        }
    }
}

//============

void parseData() {      // split the data into its parts

    char * strtokIndx; // this is used by strtok() as an index

    strtokIndx = strtok(tempChars,",");      // get the first part - the string
    red = atoi(strtokIndx);   // convert this part to an integer
 
    strtokIndx = strtok(NULL, ","); // this continues where the previous call left off
    green = atoi(strtokIndx);     

    strtokIndx = strtok(NULL, ",");
    blue = atoi(strtokIndx);     

    strtokIndx = strtok(NULL, ",");
    action = atoi(strtokIndx);

}

//============

void showParsedData() {
    Serial.print("Red ");
    Serial.println(red);
    Serial.print("Green ");
    Serial.println(green);
    Serial.print("Blue ");
    Serial.println(blue);
    Serial.print("Action ");
    Serial.print(action);
}


void loop_HUE() {
  
    for (int hue=0;hue<360;hue++)
    {
      if (action == 0) return;
      setColorHSV(hue,1,1);
      delay(100);
    }
    
    
}


void loop_Fade1(){
    int r, g, b;
  if (action == 0) return;
  // fade from blue to violet
  for (r = 0; r < 30; r++) { 
    analogWrite(red_pin, r);
    delay(FADESPEED);
  }   
  if (action == 0) return;
  // fade from violet to red
  for (b = 30; b > 0; b--) { 
    analogWrite(blue_pin, b);
    delay(FADESPEED);
  }
  if (action == 0) return;
  // fade from red to yellow
  for (g = 0; g < 30; g++) { 
    analogWrite(green_pin, g);
    delay(FADESPEED);
  }
  if (action == 0) return;
  // fade from yellow to green
  for (r = 30; r > 0; r--) { 
    analogWrite(red_pin, r);
    delay(FADESPEED);
  } 
  if (action == 0) return;
  // fade from green to teal
  for (b = 0; b < 30; b++) { 
    analogWrite(blue_pin, b);
    delay(FADESPEED);
  } 
  if (action == 0) return;
  // fade from teal to blue
  for (g = 30; g > 0; g--) { 
    analogWrite(green_pin, g);
    delay(FADESPEED);
  } 
}


void loop_Fade2()
{
  if (action == 0) return;
  int i;
  for (i = 0; i <= 30; i++) { 
    analogWrite(red_pin, 30-i);
    analogWrite(green_pin,i);
    delay(130);
  } 
  if (action == 0) return;
  for (i = 0; i <= 30; i++) { 
    analogWrite(green_pin, 30-i);
    analogWrite(blue_pin,i);
    delay(130);
  } 
  if (action == 0) return;
  for (i = 0; i <= 30; i++) { 
    analogWrite(blue_pin, 30-i);
    analogWrite(red_pin,i);
    delay(130);
  } 

}


boolean timeout(unsigned long *current,unsigned long interval) /// o functie care suplineste folosirea unui delay()
{
  if(millis()-*current>=interval){
    *current+=interval;
    return true;
  }
  else
    return false;
}

void setColor(int redV,int greenV,int blueV)
{
  analogWrite(red_pin,redV);
  analogWrite(green_pin,greenV);
  analogWrite(blue_pin,blueV);
}

void setColorHSV(int h,double s,double v)
{
  double r=0;
  double g=0;
  double b=0;

  double hf=h/60.0;
  int i=(int)floor(h/60.0);
  double f=h/60.0-i;
  double pv=v*(1-s);
  double qv=v*(1-s*f);
  double tv=v*(1-s*(1-f));

   switch (i)
  {
  case 0: 
    r = v;
    g = tv;
    b = pv;
    break;
  case 1: 
    r = qv;
    g = v;
    b = pv;
    break;
  case 2: 
    r = pv;
    g = v;
    b = tv;
    break;
  case 3: 
    r = pv;
    g = qv;
    b = v;
    break;
  case 4:
    r = tv;
    g = pv;
    b = v;
    break;
  case 5: 
    r = v;
    g = pv;
    b = qv;
    break;
  }

  int redV=constrain((int)30*r,0,30);
  int greenV=constrain((int)30*g,0,30);
  int blueV=constrain((int)30*b,0,30);

  setColor(redV,greenV,blueV);
}
