#include "ClockDigit.h"

// Pins
const int dirPin_minute_ones = 5 ;
const int stepPin_minute_ones = 6 ;
const int dirPin_minute_tens = 7 ;
const int stepPin_minute_tens = 8 ;
const int dirPin_hour_ones = 9 ;
const int stepPin_hour_ones = 10 ;
const int dirPin_hour_tens = 11 ;
const int stepPin_hour_tens = 12 ;

// Globals
ClockDigit minute_ones (ClockDigit::REV, stepPin_minute_ones, dirPin_minute_ones) ;
ClockDigit minute_tens (ClockDigit::FWD, stepPin_minute_tens, dirPin_minute_tens) ;
ClockDigit hour_ones (ClockDigit::REV, stepPin_hour_ones, dirPin_hour_ones) ;
ClockDigit hour_tens (ClockDigit::FWD, stepPin_hour_tens, dirPin_hour_tens) ;
int current_minute_ones = 0 ;
int current_minute_tens = 0 ;
int current_hour_ones = 0 ;
int current_hour_tens = 0 ;

void setup()
{
  Serial.begin(57600) ;
  Serial.println("Setup complete.") ;
}
void loop()
{
  static unsigned long now_t = -15000 ;

  if (millis() - now_t > 15000) {
      now_t = millis() ;

    // Set all digits to next number
    if (++current_minute_ones == 10 ) 
        current_minute_ones = 0 ;  
    if (++current_minute_tens == 6 ) 
        current_minute_tens = 0 ;
    if (++current_hour_ones == 10 ) 
        current_hour_ones = 0 ;  
    if (++current_hour_tens == 3 ) 
        current_hour_tens = 0 ;

    // Move to next digits
    minute_ones.setToDigit(current_minute_ones);
    minute_tens.setToDigit(current_minute_tens);
    hour_ones.setToDigit(current_hour_ones);
    hour_tens.setToDigit(current_hour_tens);

    Serial.print("Moving to ") ;
    Serial.print(current_hour_tens) ;
    Serial.print(current_hour_ones) ;
    Serial.print(" : ") ;
    Serial.print(current_minute_tens) ;
    Serial.println(current_minute_ones) ;
  }

  minute_ones.run() ;
  minute_tens.run() ;
  hour_ones.run() ;
  hour_tens.run() ;

}
