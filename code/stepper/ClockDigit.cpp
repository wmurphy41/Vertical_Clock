#include "ClockDigit.h"

ClockDigit::ClockDigit(int dir, int step_pin, int dir_pin) :
  current_digit(0) ,    // all digits start at 0
  next_digit(0) ,
  invert_direction(dir) ,
  stepper(AccelStepper(AccelStepper::DRIVER, step_pin, dir_pin))  {

    stepper.setMaxSpeed(MAX_DIGIT_SPEED);
    stepper.setAcceleration(DIGIT_ACCELERATION);

}

void ClockDigit::setToDigit(int digit) {

  if (stepper.isRunning()) {
    next_digit = digit ;
    Serial.print("Queuing digit: ") ;
    Serial.println(digit) ;
  }
  else {
  
    int delta_digits = digit - current_digit ;
    if (delta_digits) {
      stepper.move(invert_direction * STEPS_PER_DIGIT * delta_digits) ;
      current_digit = digit ;
      next_digit = current_digit;
      Serial.print("Setting digit: ") ;
      Serial.println(digit) ;
    }
  }
}

void ClockDigit::run() {
  if (!stepper.isRunning() && (next_digit != current_digit)) {
    setToDigit(next_digit) ;
  }
  stepper.run() ;
}
