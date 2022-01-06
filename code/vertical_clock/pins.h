#ifndef PINS_H
#define PINS_H

//Define the pin connections for the Rotary Switch
const int SW_PIN =      2 ;        //monitor for interrupt
const int CLK_PIN =     3 ;        //monitor for interrupt
const int DT_PIN  =     4 ;

//Define the pin connections for the Stepper Drivers
const int DIRPIN_MINUTE_ONES = 5 ;
const int STEPPIN_MINUTE_ONES = 6 ;
const int DIRPIN_MINUTE_TENS = 7 ;
const int STEPPIN_MINUTE_TENS = 8 ;
const int DIRPIN_HOUR_ONES = 9 ;
const int STEPPIN_HOUR_ONES = 10 ;
const int DIRPIN_HOUR_TENS = 11 ;
const int STEPPIN_HOUR_TENS = 12 ;
const int ENABLE_PIN =  13 ;       // Shared enable pin for all steppers

//Define the pin connections for the real time clock
const int SDA_PIN =     A4 ;       // Used by the RTC (preset config)
const int SCL_PIN =     A5 ;       // Used by RTC (preset config)

// Pins for LEDs
const int MINUTE_LED =  A1 ;
const int HOUR_LED =    A2 ;


#endif //PINS_H
