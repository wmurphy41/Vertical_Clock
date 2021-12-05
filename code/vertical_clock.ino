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

//Define the pin connection
const int CLK_PIN =     2 ;        //CLK->D2.  We will monitor for interrupt
const int SW_PIN =      3 ;        //SW->D3.  We will monitor for interrupt
const int DT_PIN  =     4 ;        //DT->D4 
const int MINUTE_LED =  A2 ;
const int HOUR_LED =    A1 ;


// Globals
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

    // Set up LEDs
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
 * 
 */
void loop () {

    // Check if switch was clicked
    if (switchClicked) {
      switchClicked = false ;
      clockState.IncrementState() ;
    }
        
    // Every 3 seconds
    // - Check if switch was rotated to adjust time
    // - Update dials to match clock time
    static long int lastTimeRan = 0 ;
    if ((millis() - lastTimeRan) > 3000) {
      lastTimeRan = millis() ;

      // if switch rotated adjust time
      if (rotaryCount |= 0)      {

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
      PrintTime() ;
        
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
    
    Serial.print(realTimeClock.getHour(hour12, pmTime), DEC);
    Serial.print(':');
    Serial.print(realTimeClock.getMinute(), DEC);
    Serial.print(':');
    Serial.print(realTimeClock.getSecond(), DEC);
    Serial.println();
 }
