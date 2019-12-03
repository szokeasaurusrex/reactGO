#ifndef SDP_UTIL
#define SDP_UTIL

/**
 * Type of touch (press or hold). Hold is defined as >=500ms,
 * touch is anything else.
 */
enum TouchType {PRESS, HOLD};

/**
 * Waits for touch.
 * @return Type of touch (press or hold)
 */
enum TouchType waitForTouch();

/**
 * Returns a uniformly distributed random
 * integer between min (inclusive), and max
 * (exclusive).
 * @param min The minimum integer (inclusive).
 * @param max The maximum integer (exclusive).
 *      max > min and max - min <= 32767
 * @return A random integer in the specified range.
 */
int randBetween(int min, int max);

/**
 * Determines whether Proteus is currently detecting
 * a touch. In order to ensure
 * accurate readings, this method clears the touchscreen
 * buffer prior to obtaining a reading.
 * @return true if touch detected, false otherwise
 */
bool touchDetected();

/**
 * Gets the current time as an integer number of milliseconds.
 * @return Milliseconds since Proteus powered on.
 */
unsigned int millis();

#endif