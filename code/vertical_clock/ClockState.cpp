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

void ClockState::incrementState() {

   if (sketchState == calibrate_mode) {
     sketchState = normal ;
   }
   else {
      sketchState = (sketchState + 1) % 3 ;
   }
}
void ClockState::setLEDs() {
    switch (sketchState) {
    case normal :
      digitalWrite (minLED, HIGH);
      digitalWrite (hourLED, HIGH);
      break ;
    case edit_minute :
      digitalWrite (minLED, HIGH);
      digitalWrite (hourLED, LOW);
      break ;
    case edit_hour :
      digitalWrite (minLED, LOW);
      digitalWrite (hourLED, HIGH);
      break ;
    case calibrate_mode :  
      if (millis() % 4000 > 2000 ) {
        digitalWrite (minLED, LOW);
        digitalWrite (hourLED, LOW);
      } else {
        digitalWrite (minLED, HIGH);
        digitalWrite (hourLED, HIGH);
      }
      break ;    
   }
}

int ClockState::getState() {
  return sketchState ;
}
