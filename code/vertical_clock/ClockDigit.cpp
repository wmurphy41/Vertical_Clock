#include "ClockDigit.h"

ClockDigit::ClockDigit(int dir, int step_pin, int dir_pin) :
  current_digit(0) ,    // all digits start at 0
  invert_direction(dir) ,
  stepper(AccelStepper(AccelStepper::DRIVER, step_pin, dir_pin))  {

    stepper.setMaxSpeed(MAX_DIGIT_SPEED);
    stepper.setAcceleration(DIGIT_ACCELERATION);

}

void ClockDigit::setToDigit(uint8_t digit) {
  int delta_digits = digit - current_digit ;
  if (delta_digits) {
    stepper.move(invert_direction * STEPS_PER_DIGIT * delta_digits) ;
    Serial.print("CD::sTD: Moving to position: ") ;
    Serial.println(stepper.targetPosition()) ;
    current_digit = digit ;
  }
}

void ClockDigit::run() {
  stepper.run() ;
}
