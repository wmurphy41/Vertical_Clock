/*
 *  ClockState methods:
 *  - constructor - stores LED pins
 *  - setup - initializes LEDs and enable PIN
 *  - IncrementState - moves to next state when switch is triggered and updates lights
 *  - GetState - returns current state of the sketch
 */
 #include "ClockState.h"
 #include <arduino.h>

 ClockState::ClockState(int h, int m) {
  hourLED = h ;
  minLED = m ;
  sketchState = calibrate_mode ;
 }

void ClockState::setup() {
    pinMode(minLED, OUTPUT);
    pinMode(hourLED, OUTPUT);
    digitalWrite (minLED, LOW);
    digitalWrite (hourLED, LOW);
 }


// Cycles through the clock states
// calibrate -> normal -> edit_hour -> edit_minute
//                ^                        |
//                +------------------------+
void ClockState::incrementState() {

   if (sketchState == calibrate_mode) {
     sketchState = normal ;
   }
   else {
      sketchState = (sketchState + 1) % 3 ;
   }
}

// Set the LEDs to match the state
//  - Normal - both on
//  - Edit Minutes - hour off, minute fast blinking
//  - Edit Hours - minute off, hour fast blinking
//  - Calibration mode - both slow blinking
void ClockState::setLEDs() {

    switch (sketchState) {
    case normal :
      digitalWrite (minLED, HIGH);
      digitalWrite (hourLED, HIGH);
      break ;
    case edit_minute :
      if (millis() % (2*FAST_BLINK) > FAST_BLINK ) {
        digitalWrite (minLED, LOW);
      }
      else {
        digitalWrite (minLED, HIGH);
      }
      digitalWrite (hourLED, LOW);
      break ;
    case edit_hour :
      digitalWrite (minLED, LOW);
      if (millis() % (2*FAST_BLINK) > FAST_BLINK ) {
        digitalWrite (hourLED, LOW);
      }
      else {
        digitalWrite (hourLED, HIGH);
      }
      break ;
    case calibrate_mode :
      if (millis() % (2*SLOW_BLINK) > SLOW_BLINK ) {
        digitalWrite (minLED, LOW);
        digitalWrite (hourLED, LOW);
      }
      else {
        digitalWrite (minLED, HIGH);
        digitalWrite (hourLED, HIGH);
      }
      break ;
   }
}

int ClockState::getState() {
  return sketchState ;
}
