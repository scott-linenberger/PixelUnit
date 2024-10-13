#include <PixelUnit.h>

/* NeoPixel Setup */
#define PIN 14
#define NUMPIXELS 8
#define LIGHT_NEOPIXEL_BRIGHTNESS_DEFAULT 100

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

/* create 4x controllable pixels units from the NeoPixel strip */
PixelUnit pixelUnit1 = PixelUnit(
  0,  // pixel start
  3,  // pixel end
  pixels);

PixelUnit pixelUnit2 = PixelUnit(
  3,  //pixel start
  5,  // pixel end
  pixels);

PixelUnit pixelUnit3 = PixelUnit(
  5,  // pixel start
  8,  // pixel end
  pixels);

void setup() {
  // LEDs
  pixels.begin();
  pixels.setBrightness(LIGHT_NEOPIXEL_BRIGHTNESS_DEFAULT);
  pixels.clear();
  pixels.show();
}



int msDemoRunTime = 10000;  // 10 seconds
unsigned long msLastSwitch = msDemoRunTime + 1;
int modeMax = 4;
int currMode;

void loop() {
  // cycle modes
  if (millis() - msLastSwitch >= msDemoRunTime) {
    currMode++;

    if (currMode > modeMax) {
      currMode = 0;
    }

    if (currMode == 0) {
      pixelUnit1.setPixelRGB(255, 0, 0);      // red
      pixelUnit2.setPixelRGB(255, 255, 255);  // white
      pixelUnit3.setPixelRGB(0, 0, 255);      // blue


      /* units flashing at a different rate */
      pixelUnit1.flashIndef(250);
      pixelUnit2.flashIndef(100);
      pixelUnit3.flashIndef(275);
    }

    if (currMode == 1) {
      pixelUnit1.setPixelRGB(255, 255, 255);  // red
      pixelUnit2.setPixelRGB(255, 255, 255);  // white
      pixelUnit3.setPixelRGB(255, 255, 255);  // blue


      /* units flashing at a different rate */
      pixelUnit1.flashIndef(1000);
      pixelUnit2.flashIndef(1000);
      pixelUnit3.flashIndef(1000);
    }

    if (currMode == 2) {
      pixelUnit1.setPixelRGB(0, 255, 255);
      pixelUnit2.setPixelRGB(0, 255, 255);
      pixelUnit3.setPixelRGB(0, 255, 255);


      /* units flashing at a different rate */
      pixelUnit1.setPixelOn(true);
      pixelUnit2.setPixelOn(true);
      pixelUnit3.setPixelOn(true);
    }

    if (currMode == 3) {
      /* all units off */
      pixelUnit1.setPixelOn(false);
      pixelUnit2.setPixelOn(false);
      pixelUnit3.setPixelOn(false);
    }

    if (currMode == 4) {
      /* flash unit 1 pink, n times */
      pixelUnit1.setPixelOn(false);
      pixelUnit2.setPixelOn(false);
      pixelUnit3.setPixelOn(false);

      pixelUnit1.setPixelRGB(255, 20, 50);
      pixelUnit1.flashTimes(5, 250);
    }

    msLastSwitch = millis();  // update timeout
  }

  // put your main code here, to run repeatedly:
  pixelUnit1.run();  // pixels must run on loop to execute timer and function logic
  pixelUnit2.run();
  pixelUnit3.run();
}
