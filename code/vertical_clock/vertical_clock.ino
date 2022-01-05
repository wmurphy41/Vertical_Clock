/*
 *  Vertical Clock
 *
 *  Use real time clock to keep track of time.
 *  Drives four stepper motors to move clock digits to match time.
 *  Collects user input from a rotary switch to change modes and adjust
 *  time.
 */

#include <DS3231.h>
#include <Wire.h>
#include "ClockState.h"
#include "ClockDigit.h"
#include "pins.h"         // pin assignments


// Logic constants
const int LOOP_TIMER = 3000 ;     // Time between checks for digit change (3s)

// Globals
// Clock digit and stepper motor
// Local definitions of the static class members
int ClockDigit::enable_pin { ENABLE_PIN } ;
int ClockDigit::sp = 0 ;
ClockDigit *ClockDigit::digit_stack[NUM_DIGITS] ;
// clock digit objects
ClockDigit minute_ones (ClockDigit::REV, STEPPIN_MINUTE_ONES, DIRPIN_MINUTE_ONES) ;
ClockDigit minute_tens (ClockDigit::FWD, STEPPIN_MINUTE_TENS, DIRPIN_MINUTE_TENS) ;
ClockDigit hour_ones (ClockDigit::REV, STEPPIN_HOUR_ONES, DIRPIN_HOUR_ONES) ;
ClockDigit hour_tens (ClockDigit::FWD, STEPPIN_HOUR_TENS, DIRPIN_HOUR_TENS) ;

// State engine
ClockState clockState(HOUR_LED, MINUTE_LED) ;

// Rotary Switch
volatile int lastCLK = 0;
volatile int rotaryCount = 0 ;
volatile bool switchClicked = false ;

// RTC
DS3231 realTimeClock;


/* Setup()
 *
 *
 */
void setup () {
    Serial.begin(57600);
    Serial.println("Starting setup...") ;

    // Setup RTC
    Wire.begin();

    // Set up LEDs and enable pin for the steppers
    ClockDigit::setup() ;
    clockState.setup() ;

    // Setup Rotary Switch
    pinMode(SW_PIN, INPUT);
    digitalWrite(SW_PIN, HIGH);
    pinMode(CLK_PIN, INPUT);
    pinMode(DT_PIN, INPUT);
    attachInterrupt(digitalPinToInterrupt(CLK_PIN), DialRotated_ISR, CHANGE);
    attachInterrupt(digitalPinToInterrupt(SW_PIN), SwitchClicked_ISR, FALLING);

    Serial.println("...completed setup.") ;
}

/*
 * loop()
 * - If the switch was clicked, increment the clock state
 * - If we're in calibrate mode, then jump out of loop (no actions)
 * - Every LOOP_TIMER milliseconds,
 *    - Check if switch was rotated to adjust time
 *    - Update dials to match clock time
 * - Move stepper motors one step until all match
 *     the digits where they are supposed to be.
 */
void loop () {

    static bool firstrun = true ;

    // Check if switch was clicked
    if (switchClicked) {
      switchClicked = false ;
      clockState.incrementState() ;
    }
    clockState.setLEDs() ;

    // If we're still in calibrate state - just end loop now.
    if   (clockState.getState() == ClockState::calibrate_mode) {
      if (firstrun) {
        Serial.println("calibrate mode") ;
        PrintTime() ;
        firstrun = false ;
      }
      return ;
    }

    // Every LOOP_TIMER milliseconds
    // - Check if switch was rotated to adjust time
    // - Update dials to match clock time
    static long int lastTimeRan = 0 ;
    if ((millis() - lastTimeRan) > LOOP_TIMER) {
      lastTimeRan = millis() ;

      // if switch rotated adjust time
      if (rotaryCount != 0)      {

        switch (clockState.getState()) {
          case ClockState::edit_minute :  {
              int newMinute = realTimeClock.getMinute() - rotaryCount ;
              newMinute = max ( min(newMinute, 59), 0) ;
              realTimeClock.setMinute(newMinute) ;
              realTimeClock.setSecond(0) ;            // Always set seconds to zero when adjusting minutes
              rotaryCount = 0 ;
            }
            break ;

          case ClockState::edit_hour : {
              bool hour12, pmTime ;
              int newHour = realTimeClock.getHour(hour12, pmTime) - rotaryCount ;
              newHour = max ( min(newHour, 24), 0) ;
              realTimeClock.setHour(newHour) ;
              rotaryCount = 0 ;
            }
            break ;

          default:
            rotaryCount = 0 ;   // normal and dark mode, ignore clicks
        }
      }

      // Adjust dials to match time
      bool hour12, pmTime ;
      int this_hr = realTimeClock.getHour(hour12, pmTime) ;
      int this_min = realTimeClock.getMinute() ;

      minute_ones.setToDigit(this_min % 10);
      minute_tens.setToDigit(this_min / 10);
      hour_ones.setToDigit(this_hr % 10);
      hour_tens.setToDigit(this_hr / 10);
      PrintTime() ;
   } // end set dials to current time

  // Move stepper motors one step until all match
  // the digits where they are supposed to be.
  ClockDigit::run_all() ;

}

/* Interupt handlers
 *
 *  DialRotated_IRS - updates globals to track number of clicks rotary is turned
 *  SwitchClicked_IRS - Sets global flag when the switch was clicked
 */
//The interrupt handlers
void DialRotated_ISR()
{
  int clkValue = digitalRead(CLK_PIN) ;       //Read the CLK pin level
  int dtValue = digitalRead(DT_PIN) ;         //Read the DT pin level
  if (lastCLK != clkValue)    {
    lastCLK = clkValue;
    if (lastCLK % 2)                        // Increment count every 2 clicks
      rotaryCount += (clkValue != dtValue ? 1 : -1) ;  //CLK and inconsistent DT + 1, otherwise - 1
  }
}

void SwitchClicked_ISR()
{
  static long timeLastClick = 0 ;

  if ( millis() - timeLastClick > 500 ) {  // Avoids spurious double reads of same clicks
    switchClicked = true ;
    timeLastClick = millis() ;
  }
}


 /*
  *  helper functions.  For debugging only.
  */
 void PrintTime() {
    bool hour12, pmTime ;

    Serial.print("time: ");
    Serial.print(realTimeClock.getHour(hour12, pmTime), DEC);
    Serial.print(':');
    Serial.print(realTimeClock.getMinute(), DEC);
    Serial.print(':');
    Serial.print(realTimeClock.getSecond(), DEC);
    Serial.println();
 }
