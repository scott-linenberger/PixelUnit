#include "PixelUnit.h"

/* NeoPixel Setup */
#define PIN       14 
#define NUMPIXELS 8
#define LIGHT_NEOPIXEL_BRIGHTNESS_DEFAULT 100

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

/* create 4x controllable pixels units from the NeoPixel strip */
PixelUnit pixelUnit1 = PixelUnit(
  0, // pixel start
  3, // pixel end
  pixels
);

PixelUnit pixelUnit2 = PixelUnit(
  3, //pixel start
  5, // pixel end
  pixels
);

PixelUnit pixelUnit3 = PixelUnit(
  5, // pixel start
  8, // pixel end
  pixels
);

void setup() {
  // LEDs
  pixels.begin();
  pixels.setBrightness(LIGHT_NEOPIXEL_BRIGHTNESS_DEFAULT);
  pixels.clear();
  pixels.show();

  // set pixel colors (can be changed later, must be called on setup)
  pixelUnit1.setPixelRGB(255, 0, 0); // red
  pixelUnit2.setPixelRGB(255, 255, 255); // white
  pixelUnit3.setPixelRGB(0, 0, 255); // blue


  /* units flashing at a different rate */
  pixelUnit1.flashIndef(250);
  pixelUnit2.flashIndef(100);
  pixelUnit3.flashIndef(275); // little stagger
}

void loop() {
  // put your main code here, to run repeatedly:
  pixelUnit1.run(); // pixels must run on loop to execute timer and function logic
  pixelUnit2.run();
  pixelUnit3.run();
}
