#include "ClockDigit.h"


void ClockDigit::setup() {
  pinMode(enable_pin, OUTPUT) ;
  disableSteppers() ;
}

void ClockDigit::enableSteppers() {
    Serial.print("Enabling steppers though pin: ") ;
    Serial.println(enable_pin) ; 
    digitalWrite (enable_pin, LOW);
}

void ClockDigit::disableSteppers() {
    digitalWrite (enable_pin, HIGH);
}

ClockDigit::ClockDigit(int dir, int step_pin, int dir_pin) :
  current_digit(0) ,    // all digits start at 0
  next_digit(0) ,
  invert_direction(dir) ,
  stepper(AccelStepper(AccelStepper::DRIVER, step_pin, dir_pin))  {

    stepper.setMaxSpeed(MAX_DIGIT_SPEED);
    stepper.setAcceleration(DIGIT_ACCELERATION);

}

void ClockDigit::setToDigit(int digit) {

  if (digit == current_digit) {
    return ;
  }

  if (stepper.isRunning()) {
    next_digit = digit ;
    Serial.print("Queuing digit: ") ;
    Serial.println(digit) ;
    return ;
  }

  int delta_digits = digit - current_digit ;
  enableSteppers() ;
  stepper.move(invert_direction * STEPS_PER_DIGIT * delta_digits) ;
  current_digit = digit ;
  next_digit = current_digit;
  Serial.print("Setting digit: ") ;
  Serial.println(digit) ;
  return ;
}

bool ClockDigit::run() {
  if (!stepper.isRunning() && (next_digit != current_digit)) {
    setToDigit(next_digit) ;
  }
  stepper.run() ;
  return (stepper.isRunning()) ;
}
