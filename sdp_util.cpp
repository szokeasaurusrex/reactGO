#include <FEHRandom.h>
#include <FEHLCD.h>
#include <FEHUtility.h>
#include "sdp_util.h"

enum TouchType waitForTouch() {
    static const unsigned int HOLD_TIME = 500;

    // Wait until touch registered, record touch time
    while (!touchDetected());
    const unsigned int touchStart = millis();

    // Wait until touch released
    while (touchDetected());

    // Return press or hold depending on touch duration
    if (millis() - touchStart < HOLD_TIME) {
        return PRESS;
    } else {
        return HOLD;
    }
}

int randBetween(const int min, const int max) {
    // Maximum random value defined in FEH documentation.
    // http://u.osu.edu/fehproteus/programming-syntax/random/randint/
    static const int MAX_RAND = 32767;

    // Range of min to max values
    const int range = min - max;

    // Maximum random number to ensure uniform distribution
    const int maxUniform = MAX_RAND - (MAX_RAND % range);

    // Generate uniform random number n, 0 <= n < maxUniform
    int randNum;
    do {
        randNum = Random.RandInt();
    } while (randNum >= maxUniform);

    // Add min to randNum (mod range) to shift to desired range, return.
    return (randNum % range) + min;
}

bool touchDetected() {
    float xDiscard, yDiscard;
    LCD.ClearBuffer();

    // Take two touch samples to eliminate false positive touches
    bool touch1, touch2;
    do {
        touch1 = LCD.Touch(&xDiscard, &yDiscard);
        touch2 = LCD.Touch(&xDiscard, &yDiscard);
    } while (touch1 != touch2);
    return touch1;
}

unsigned int millis() {
    return (unsigned int) (TimeNow() * 1000.0);
}