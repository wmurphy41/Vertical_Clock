// Date and time functions using a DS1307 RTC connected via I2C and Wire lib

#include <DS3231.h>
#include <Wire.h>

//Define the pin connection
const int CLK_PIN = 2 ;        //CLK->D2.  We will monitor for interrupt
const int SW_PIN = 3 ;         //SW->D3.  We will monitor for interrupt
const int DT_PIN  = 4 ;        //DT->D4 
const int MINUTE_LED = A1 ;
const int HOUR_LED = A2 ;


// Globals
// State engine

enum { normal = 0, edit_minutes = 1, edit_hours = 2, dark_mode = 3 } sketchState ;

// Rotary Switch
volatile int lastCLK = 0;                      
volatile int rotaryCount = 0 ;
volatile bool switchClicked = false ; 

DS3231 realTimeClock;                 // Real time clock

void setup () {
    Serial.begin(57600);
    Serial.println("Starting setup...") ;
  
    // Setup RTC
    Wire.begin();

    // Set up LEDs
    pinMode(MINUTE_LED, OUTPUT);
    pinMode(HOUR_LED, OUTPUT);
    
    // Setup Rotary Switch
    pinMode(SW_PIN, INPUT);
    digitalWrite(SW_PIN, HIGH);
    pinMode(CLK_PIN, INPUT);
    pinMode(DT_PIN, INPUT);
    attachInterrupt(digitalPinToInterrupt(CLK_PIN), DialRotated_ISR, CHANGE);
    attachInterrupt(digitalPinToInterrupt(SW_PIN), SwitchClicked_ISR, FALLING);

    // Set initial state
    sketchState = normal ; 
    digitalWrite (MINUTE_LED, HIGH);
    digitalWrite (HOUR_LED, HIGH);
  
    Serial.println("...completed setup.") ;
}

void loop () {

    // Check if switch was clicked
    if (switchClicked) {
      switchClicked = false ;
      sketchState = (sketchState + 1) % 4 ;
        
      Serial.println("Switch clicked...") ; 
      Serial.print("New sketchState is... ") ;
      Serial.println(sketchState) ;
       
      switch (sketchState) {
        case normal :
          digitalWrite (MINUTE_LED, HIGH);
          digitalWrite (HOUR_LED, HIGH);
          break ;
        case edit_minutes :
          digitalWrite (MINUTE_LED, HIGH);
          digitalWrite (HOUR_LED, LOW);
          break ;
        case edit_hours :
          digitalWrite (MINUTE_LED, LOW);
          digitalWrite (HOUR_LED, HIGH);
          break ;
         case dark_mode :
          digitalWrite (MINUTE_LED, LOW);
          digitalWrite (HOUR_LED, LOW);
          break ;             
      }
    }
    
    
    // Every 3 seconds
    // - Check clock
    // - Check if switch was rotated to adjust time
    static long int lastTimeRan = 0 ;
    if ((millis() - lastTimeRan) > 3000) {
      lastTimeRan = millis() ;

      // Printing Time
      bool hour12, pmTime ;
      Serial.print(realTimeClock.getHour(hour12, pmTime), DEC);
      Serial.print(':');
      Serial.print(realTimeClock.getMinute(), DEC);
      Serial.print(':');
      Serial.print(realTimeClock.getSecond(), DEC);
      Serial.println();
  
      // If the switch has been rotated since the last check-in
      // Adjust minutes
      if (rotaryCount |= 0) {
        int newMinutes = realTimeClock.getMinute() + rotaryCount ;
        newMinutes = max ( min(newMinutes, 59), 0) ;
        
        Serial.print("Adding " ) ;
        Serial.print(rotaryCount) ;
        Serial.print(" minutes to set new minutes to ") ;
        Serial.println(newMinutes) ;
        
        realTimeClock.setMinute(newMinutes) ;  
        realTimeClock.setSecond(0) ;            // Always set seconds to zero when adjusting minutes
        rotaryCount = 0 ;
      }
    }
}

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

  if ( millis() - timeLastClick > 500 ) {
    switchClicked = true ;
    timeLastClick = millis() ;
  }
} 
