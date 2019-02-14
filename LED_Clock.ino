// Date and time functions using a DS3231 RTC connected via I2C and Wire lib
#include <Wire.h>
#include "RTClib.h"
#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>
#include <Fonts/Dialog_plain_5.h>
#define PIN 2

RTC_DS3231 rtc;

char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(15, 5, PIN,
  NEO_MATRIX_TOP     + NEO_MATRIX_LEFT +
  NEO_MATRIX_ROWS + NEO_MATRIX_PROGRESSIVE,
  NEO_GRB            + NEO_KHZ800);

const int buttonPin = 6;     // the number of the pushbutton pin
int buttonState = 0;   

void setup () {
  pinMode(buttonPin, INPUT);

  Serial.begin(9600);

  delay(3000); // wait for console opening

  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }

  if (rtc.lostPower()) {
    Serial.println("RTC lost power, lets set the time!");
    // following line sets the RTC to the date & time this sketch was compiled
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    // This line sets the RTC with an explicit date & time, for example to set
    // January 21, 2014 at 3am you would call:
    // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
  }
  matrix.setFont(&Dialog_plain_5);
  matrix.begin();
  matrix.setTextWrap(false);
  matrix.setBrightness(40);
  matrix.setTextColor(0);
}

int pass = 0;
int delta_min = 0;

void loop() {
  int clr[ 384 ];
  int rVal, gVal, bVal, increment;

  //set up color array
  for (int i = 0; i < 128; i++){
    clr[i] = 0;
  }
  for (int i = 128; i < 192; i++){
    clr[i] = (i-128) * 4;
  }
  for (int i = 192; i < 320; i++){
    clr[i] = 255;
  } 
  for (int i = 320; i < 384; i++){
    clr[i] = 255 - (i-320)*4;
  }

  buttonState = digitalRead(buttonPin);

  if (buttonState == HIGH) {
    // turn LED on:
    delta_min++;
  }
  

  increment = 0;
  for (int i = 0; i < 15; i++){
    rVal = (pass + increment*6) % 384;
    gVal = (pass + increment*6 + 128) % 384;
    bVal = (pass + increment*6 + 256) % 384;
    matrix.drawLine(i, 0, i, 5, matrix.Color(clr[rVal], clr[gVal], clr[bVal]));
    increment++;
  }

  DateTime now = rtc.now();
  DateTime future (now + TimeSpan(0,0,delta_min,0));
  int hr_24, hr_12, mn;
  hr_24=future.hour();
  mn=future.minute();
  if (hr_24==0) hr_12=12;
  else hr_12=hr_24%12;
  String hr_char;
  String mn_char;
  if(hr_12<10) hr_char=" " + String(hr_12);
  else hr_char=String(hr_12);
  if(future.minute()<10) mn_char="0" + String(future.minute());
  else mn_char=String(future.minute());
  
  matrix.setCursor(-2, 5);
  matrix.print(hr_char + ":" + mn_char);
  matrix.show(); 
  Serial.print(future.hour());
  Serial.print(":");
  Serial.print(future.minute());
  Serial.println();
  delay(250);
  pass++;
  
}
