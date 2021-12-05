/* 
 *  ClockState methods:
 *  - constructor - stores LED pins
 *  - setup - initializes LEDs
 *  - IncrementState - moves to next state when switch is triggered and updates lights
 *  - GetState - returns current state of the sketch
 */
 #include "ClockState.h"
 #include <arduino.h>

 ClockState::ClockState(int h, int m) {
  hourLED = h ;
  minLED = m ;
 }
 void ClockState::setup() {
    pinMode(minLED, OUTPUT);
    pinMode(hourLED, OUTPUT);
    digitalWrite (minLED, HIGH);
    digitalWrite (hourLED, HIGH);
 }
 void ClockState::IncrementState() {
 
    sketchState = (sketchState + 1) % 4 ;

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
       case dark_mode :
        digitalWrite (minLED, LOW);
        digitalWrite (hourLED, LOW);
        break ;             
   }
 }
int ClockState::getState() {
  return sketchState ;
}
