#ifndef LINENTOOLS_PIXEL_UNIT_H
#define LINENTOOLS_PIXEL_UNIT_H
#include <Adafruit_NeoPixel.h>

enum PixelUnitMode { LED_OFF, LED_ON, FLASHING_INDEF, FLASHING_TIMES };

class PixelUnit {
    private:
        uint16_t pixelPos;
        uint16_t rangeStart;
        uint16_t rangeStop;

        Adafruit_NeoPixel *pixelStrip;

        /* led state */
        PixelUnitMode mode;

        /* color values */
        uint8_t r;
        uint8_t g;
        uint8_t b; 

        uint16_t msDelayTime;
        float timestampLast;

        uint8_t currCount;
        uint16_t numTimesToFlash;
        bool isOn;

        bool timeToggleLed();
        void pixelOff();
        void pixelOn();

    public:
        PixelUnit(uint16_t _pixelPos, Adafruit_NeoPixel &_pixelStrip);
        PixelUnit(uint16_t _rangeStart, uint16_t _rangeStop, Adafruit_NeoPixel &_pixelStrip);
        void run();
        void setPixelRGB(uint8_t _r, uint8_t _g, uint8_t _b);
        void flashIndef(uint16_t _msDelayFlash);
        void flashTimes(uint16_t _flashTimes, uint16_t _msDelayFlash);
        void setPixelOn(bool _isOn);
};

#endif
