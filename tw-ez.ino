// Simple strand test for Adafruit Dot Star RGB LED strip.
// This is a basic diagnostic tool, NOT a graphics demo...helps confirm
// correct wiring and tests each pixel's ability to display red, green
// and blue and to forward data down the line.  By limiting the number
// and color of LEDs, it's reasonably safe to power a couple meters off
// the Arduino's 5V pin.  DON'T try that with other code!

#include <Adafruit_DotStar.h>
// Because conditional #includes don't work w/Arduino sketches...
#include <SPI.h>         // COMMENT OUT THIS LINE FOR GEMMA OR TRINKET
//#include <avr/power.h> // ENABLE THIS LINE FOR GEMMA OR TRINKET

#define NUMPIXELS 5 // Number of LEDs in strip

// Here's how to control the LEDs from any two pins:
#define DATAPIN    11
#define CLOCKPIN   5
Adafruit_DotStar strip(NUMPIXELS, DATAPIN, CLOCKPIN, DOTSTAR_BRG);

int sensorValue;
uint32_t red = 0xFF0000;      // 'On' color (starts red)
uint32_t amber = 0xFFBF00;
uint32_t green = 0x00A86B;

int beginningLEDS = 6;
int endingLEDS = 6; // change to the amount of LEDs used
// different recommended pressure values
float currMaterialPressure = 50.5; // update later to tested value

int threshLow = 30.5;
int threshHigh = 70.5;

int yellowGreenInc = (currMaterialPressure - threshLow) / beginningLEDS;
int yellowRedInc = (threshHigh - currMaterialPressure) / endingLEDS;
bool pressureApplied = false;



// The last parameter is optional -- this is the color data order of the
// DotStar strip, which has changed over time in different production runs.
// Your code just uses R,G,B colors, the library then reassigns as needed.
// Default is DOTSTAR_BRG, so change this if you have an earlier strip.

// Hardware SPI is a little faster, but must be wired to specific pins
// (Arduino Uno = pin 11 for data, 13 for clock, other boards are different).
//Adafruit_DotStar strip(NUMPIXELS, DOTSTAR_BRG);

void setup() {

// #if defined(__AVR_ATtiny85__) && (F_CPU == 16000000L)
//   clock_prescale_set(clock_div_1); // Enable 16 MHz on Trinket
// #endif
  strip.begin(); // Initialize pins for output
  strip.show();  // Turn all LEDs off ASAP



}

// Runs 10 LEDs at a time along strip, cycling through red, green and blue.
// This requires about 200 mA for all the 'on' pixels + 1 mA per 'off' pixel.

//int      head  = 0, tail = -10; // Index of first 'on' and 'off' pixels


void loop() {

  int sensorValue = analogRead(A0);
  if (sensorValue > threshLow) {
    strip.setPixelColor(-11, amber);
  }
  if (sensorValue > threshLow + yellowGreenInc) {
    strip.setPixelColor(-10, amber);
  }
  if (sensorValue > threshLow + (2 * yellowGreenInc)) {
    strip.setPixelColor(-9, green);
  }
  if (sensorValue > threshLow + (3 * yellowGreenInc)) {
    strip.setPixelColor(-8, green);
  }
  if (sensorValue > threshLow + (4 * yellowGreenInc)) {
    strip.setPixelColor(-7, green);
  }
  if (sensorValue > threshLow + (5 * yellowGreenInc)) {
    strip.setPixelColor(-6, green);
  }
  if (sensorValue > currMaterialPressure + yellowRedInc) {
    strip.setPixelColor(-5, amber);
  }
  if (sensorValue > currMaterialPressure + (2 * yellowRedInc)) {
    strip.setPixelColor(-4, amber);
  }
  if (sensorValue > currMaterialPressure + (3 * yellowRedInc)) {
    strip.setPixelColor(-3, red);
  }
  if (sensorValue > currMaterialPressure + (4 * yellowRedInc)) {
    strip.setPixelColor(-2, red);
  }
  if (sensorValue > currMaterialPressure + (5 * yellowRedInc)) {
    strip.setPixelColor(-1, red);
  }
  if (sensorValue > currMaterialPressure + (5 * yellowRedInc)) {
    strip.setPixelColor(0, red);
  }
  strip.setPixelColor(0, red);
  strip.show();                     // Refresh strip
  delay(20);   
  
  // sensorValue = analogRead(A0); // value given from Sensor

  // red is the head of the strip
  // yellow is in the middle of the strip
  // green is the tail of the strip
  // if(sensorValue > thresh_inc){
  //   strip.setPixelColor(-1, amber);

  // if(sensorValue > thresh_inc*2) {
  //   strip.setPixelColor(-2, green);

  // if(sensorValue > thresh_inc*2) {
  //   strip.setPixelColor(-3, green);

  // if(sensorValue > thresh_inc*2) {
  //   strip.setPixelColor(-4, red);
  // }
                       // Pause 20 milliseconds (~50 FPS)
}
