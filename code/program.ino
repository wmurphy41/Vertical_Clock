#include <Stepper.h>
#include "RTClib.h"

#define STEPPER_ON 14

RTC_DS3231 rtc;

class ClockDigit {
  // Digits are zero to (num_digits - 1) [inclusive]
  int8_t current_digit = 0; // All digits should start at zero
  int8_t invert_direction = 1;

  static const int STEPS_PER_REVOLUTION = 2038;
  static const int STEPS_PER_DIGIT = 560;

  Stepper stepper;
  
public:
  ClockDigit(int8_t dir, int blu, int yel, int pnk, int ora) 
    : invert_direction(dir), stepper(Stepper(STEPS_PER_REVOLUTION, blu, yel, pnk, ora)) {
      stepper.setSpeed(15);
  }

  void set_to_digit(uint8_t digit) {
    int delta_digits = digit - current_digit;
    stepper.step(invert_direction * STEPS_PER_DIGIT * delta_digits);
    
    current_digit = digit;
  }
};

ClockDigit hour_ms(1, 16,15,17,5);
ClockDigit hour_ls(-1, 3,15,2,5);
ClockDigit minute_ms(1, 8,6,7,4);
ClockDigit minute_ls(-1, 12,9,11,10);

void setup() {
  pinMode(STEPPER_ON, OUTPUT);
  
//  Serial.begin(57600);
  delay(1000);

  // Stop execution if the RTC clock is not present
  if (!rtc.begin()) {
    abort();
  }
  
  //rtc.adjust(DateTime(2021,8,2,23,58,0)); 
  
  // If the RTC has lost power, set the time to the time at compilation (this is really only for the first time setup),
  // if the battery in the RTC dies we must reprogram to get correct time. (or plug it in again at the time it thinks it is)
  if (rtc.lostPower()) {
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__))); 
  }
}

void loop() {
  DateTime t = rtc.now();
  
  digitalWrite(STEPPER_ON, HIGH);
  hour_ms.set_to_digit((t.hour() / 10) % 3);
  hour_ls.set_to_digit(t.hour() % 10);
  minute_ms.set_to_digit((t.minute() / 10) % 6);
  minute_ls.set_to_digit(t.minute() % 10);
  digitalWrite(STEPPER_ON, LOW);
  
  delay(5000);
}
