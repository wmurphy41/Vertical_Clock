/*
 *  Vertical Clock
 *
 *
 *
 *
 *
 *
 *
 */

#include <DS3231.h>
#include <Wire.h>
#include "ClockState.h"
#include "ClockDigit.h"

//Define the pin connection
const int SW_PIN =      2 ;        //monitor for interrupt
const int CLK_PIN =     3 ;        //monitor for interrupt
const int DT_PIN  =     4 ;       
const int dirPin_minute_ones = 5 ;
const int stepPin_minute_ones = 6 ;
const int dirPin_minute_tens = 7 ;
const int stepPin_minute_tens = 8 ;
const int dirPin_hour_ones = 9 ;
const int stepPin_hour_ones = 10 ;
const int dirPin_hour_tens = 11 ;
const int stepPin_hour_tens = 12 ;
const int ENABLE_PIN =  13 ;       // Shared enable pin for all steppers
const int SDA_PIN =     A4 ;       // Used by the RTC (preset config)
const int SCL_PIN =     A5 ;       // Used by RTC (preset config)
const int MINUTE_LED =  A1 ;
const int HOUR_LED =    A2 ; 



// Globals
// Clock digit and stepper motor
int ClockDigit::enable_pin { ENABLE_PIN } ;
ClockDigit minute_ones (ClockDigit::REV, stepPin_minute_ones, dirPin_minute_ones) ;
ClockDigit minute_tens (ClockDigit::FWD, stepPin_minute_tens, dirPin_minute_tens) ;
ClockDigit hour_ones (ClockDigit::REV, stepPin_hour_ones, dirPin_hour_ones) ;
ClockDigit hour_tens (ClockDigit::FWD, stepPin_hour_tens, dirPin_hour_tens) ;

// State engine
ClockState clockState(HOUR_LED, MINUTE_LED) ;

// Rotary Switch
volatile int lastCLK = 0;
volatile int rotaryCount = 0 ;
volatile bool switchClicked = false ;

DS3231 realTimeClock;                 // Real time clock


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
 *
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

    // Every 3 seconds
    // - Check if switch was rotated to adjust time
    // - Update dials to match clock time
    static long int lastTimeRan = 0 ;
    if ((millis() - lastTimeRan) > 3000) {
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

  // Move the dials.
  // If all have stopped moving, disable the steppers to
  // save power.
  bool a, b, c, d ;
  a = minute_ones.run() ;
  b = minute_tens.run() ;
  c = hour_ones.run() ;
  d = hour_tens.run() ;
  if (!a && !b && !c && !d) {
     ClockDigit::disableSteppers() ;
  }
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

  if ( millis() - timeLastClick > 500 ) {  // Avoids spurious double reads of same click
    switchClicked = true ;
    timeLastClick = millis() ;
  }
}


 /*
  *  helper functions
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
