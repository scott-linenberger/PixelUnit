#include "PixelUnit.h"

PixelUnit::PixelUnit(uint16_t _pixelPos, Adafruit_NeoPixel &_pixelStrip) {
    pixelPos = _pixelPos;
    pixelStrip = &_pixelStrip;
    mode = LED_OFF;
}

PixelUnit::PixelUnit(uint16_t _rangeStart, uint16_t _rangeStop, Adafruit_NeoPixel &_pixelStrip) {
    rangeStart = _rangeStart;
    rangeStop = _rangeStop;
    pixelStrip = &_pixelStrip;
    mode = LED_OFF;
}

/** returns true when time has been toggled */
bool PixelUnit::timeToggleLed() {
    /* check if the timestamp has expired */
    if (millis() - timestampLast >= msDelayTime) {
        /* toggle on/off state */
        isOn = !isOn;
        
        /* update LED */
        if (isOn) {
            pixelOn();
        } else {
            pixelOff();
        }

        pixelStrip->show(); // show changes

        /* update the timestamp */
        timestampLast = millis();
        
        return true;
    }

    return false;
}

void PixelUnit::run() {
    yield();
    /* --- FLASHING INDEFINITELY --- */
    if (mode == FLASHING_INDEF) {
        timeToggleLed();
    }

    /* --- FLASHING TIMES, NOT FINISHED YET ---*/
    if (mode == FLASHING_TIMES && currCount < numTimesToFlash) {
        bool isChanged = timeToggleLed();

        if (isChanged) {
            /* increment times flashed */
            currCount++;
        }
    }

    /* --- FLASHING TIMES, FINISHED --- */
    if (mode == FLASHING_TIMES && currCount >= numTimesToFlash) {
        /* turn LED OFF with state change */
        setPixelOn(false);
    }

    /* --- LED ON / OFF STATE UPDATES HANDLED IMMEDIATELY --- */
    /* --- NO NEED TO CONTINUALLY RUN CHECK THOSE STATES  ---*/
   yield();
}

/**
 * INTERNAL METHOD FOR TURUNING LIGHT OFF, DOES NOT CHANGE STATE
 */
void PixelUnit::pixelOff() {
    if (rangeStop > 0) {
        for (uint16_t i = rangeStart; i < rangeStop; i++) {
            /* turn off the led */
            pixelStrip->setPixelColor(i, 0, 0, 0);    
        }
    } else {
        /* turn off the led */
        pixelStrip->setPixelColor(pixelPos, 0, 0, 0);
    }

    pixelStrip->show(); // show changes
}

/**
 * INTERNAL METHOD FOR TURUNING LIGHT ON, DOES NOT CHANGE STATE
 */
void PixelUnit::pixelOn() {
    if (rangeStop > 0) {
        for (uint16_t i = rangeStart; i < rangeStop; i++) {
            /* turn off the led */
            pixelStrip->setPixelColor(i, r, g, b);    
        }
    } else {
        /* turn off the led */
        pixelStrip->setPixelColor(pixelPos, r, g, b);
    }

    pixelStrip->show(); // show changes
}

void PixelUnit::setPixelRGB(uint8_t _r, uint8_t _g, uint8_t _b) {
    /* set color */
    r = _r;
    g = _g;
    b = _b;
}

/**
 * EXTERNALLY FACING METHOD THAT UPDATES STATE
 */
void PixelUnit::setPixelOn(bool _isOn) {
    /* set state var */
    mode = _isOn ? LED_ON : LED_OFF;
    
    if (_isOn) {
        pixelOn();
    } else {
        pixelOff();
    }

    /* update state var */
    isOn = _isOn;
    pixelStrip->show(); // show changes
}

void PixelUnit::flashTimes(uint16_t _flashTimes, uint16_t _msDelayFlash) {
    /* set the mode */
    mode = FLASHING_TIMES;

    /* set delay time */
    msDelayTime = _msDelayFlash;

    /* set the number of times to flash */
    numTimesToFlash = _flashTimes * 2;

    /* set the count */
    currCount = 0;

    /* set flashing state OFF so it's toggled */
    isOn = false;
    
    /* reset the timestamp delay */
    timestampLast = millis() +  _msDelayFlash;

    pixelOff();
}

void PixelUnit::flashIndef(uint16_t _msDelayFlash) {
    /* update status to flashing indefinitely */
    mode = FLASHING_INDEF;

    /* set delay time */
    msDelayTime = _msDelayFlash;
    
    /* set flashing state OFF so it's toggled */
    isOn = false;
    
    /* reset the timestamp delay */
    timestampLast = 0;

    pixelOff();
}


