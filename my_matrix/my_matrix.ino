// Adafruit_NeoMatrix example for single NeoPixel Shield.
// Scrolls 'Howdy' across the matrix in a portrait (vertical) orientation.

#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>
#include <Fonts/Dialog_plain_5.h>
#ifndef PSTR
 #define PSTR // Make Arduino Due happy
#endif

#define PIN 2

// MATRIX DECLARATION:
// Parameter 1 = width of NeoPixel matrix
// Parameter 2 = height of matrix
// Parameter 3 = pin number (most are valid)
// Parameter 4 = matrix layout flags, add together as needed:
//   NEO_MATRIX_TOP, NEO_MATRIX_BOTTOM, NEO_MATRIX_LEFT, NEO_MATRIX_RIGHT:
//     Position of the FIRST LED in the matrix; pick two, e.g.
//     NEO_MATRIX_TOP + NEO_MATRIX_LEFT for the top-left corner.
//   NEO_MATRIX_ROWS, NEO_MATRIX_COLUMNS: LEDs are arranged in horizontal
//     rows or in vertical columns, respectively; pick one or the other.
//   NEO_MATRIX_PROGRESSIVE, NEO_MATRIX_ZIGZAG: all rows/columns proceed
//     in the same order, or alternate lines reverse direction; pick one.
//   See example below for these values in action.
// Parameter 5 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)


// Example for NeoPixel Shield.  In this application we'd like to use it
// as a 5x8 tall matrix, with the USB port positioned at the top of the
// Arduino.  When held that way, the first pixel is at the top right, and
// lines are arranged in columns, progressive order.  The shield uses
// 800 KHz (v2) pixels that expect GRB color data.
Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(15, 5, PIN,
  NEO_MATRIX_TOP     + NEO_MATRIX_LEFT +
  NEO_MATRIX_ROWS + NEO_MATRIX_PROGRESSIVE,
  NEO_GRB            + NEO_KHZ800);

const uint16_t colors[] = {
  matrix.Color(255, 0, 0), matrix.Color(0, 255, 0), matrix.Color(0, 0, 255) };

void setup() {
  matrix.setFont(&Dialog_plain_5);
  matrix.begin();
  matrix.setTextWrap(false);
  matrix.setBrightness(40);
  matrix.setTextColor(0);
}

int x    = matrix.width();
int pass = 0;

void loop() {
  int clr[ 384 ];
  int rVal, gVal, bVal, count, increment;
  count = 0;

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
  
  count = 0;
  for (int i = 0;  i < 384; i++) {
    increment = 0;
    for (int i = 0; i < 15; i++){
      rVal = (count + increment*6) % 384;
      gVal = (count + increment*6 + 100) % 384;
      bVal = (count + increment*6 + 200) % 384;
      matrix.drawLine(i, 0, i, 5, matrix.Color(clr[rVal], clr[gVal], clr[bVal]));
      increment++;
    }
  matrix.setCursor(0, 5);
  matrix.print(F("12:34"));
  matrix.show(); 
  delay(250);
  count++;
  }
  

  
//  matrix.fillScreen(0);
//  matrix.setTextColor(colors[pass]);
//  matrix.setCursor(0, 5);
//  matrix.print(F("12:34"));
//  if(--x < -45) {
//    x = matrix.width();
//    if(++pass >= 3) pass = 0;
//    matrix.setTextColor(colors[pass]);
//  }
//  matrix.show();
//  delay(100);
}
