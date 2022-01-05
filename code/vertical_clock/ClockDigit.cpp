#include "ClockDigit.h"

// Static class methods
// Setup - sets up the enable pin and sets to low voltage (enabled)
void ClockDigit::setup() {
  pinMode(enable_pin, OUTPUT) ;
  disableSteppers() ;
}

// called during constructor... adds digit to the
// array of all digits.
void ClockDigit::pushClockDigit(ClockDigit *cd_ptr) {
  if (sp < NUM_DIGITS) {
    digit_stack[sp++] = cd_ptr ;
    Serial.println("Added to stack...") ;
  }
  else {
    Serial.println("Overstack error...") ;
  }
}

// Runs all clock digits one step.
bool ClockDigit::run_all() {
  bool any_running = false ;
  for(int i=0; i<sp; i++) {
    bool this_running = digit_stack[i]->run() ;
    any_running = this_running || any_running ;
  }
  if (!any_running) {
    disableSteppers() ;
  }
  return any_running ;
}

// EnableSteppers - sets pin low (enabled)
void ClockDigit::enableSteppers() {
    digitalWrite (enable_pin, LOW);
}

// EnableSteppers - sets pin high (disabled)
void ClockDigit::disableSteppers() {
    digitalWrite (enable_pin, HIGH);
}


// Constructor
// Initalizes the steper driver with pins and constants
// Adds this digit to the array of all digits in the class so that
// run_all works.
ClockDigit::ClockDigit(int dir, int step_pin, int dir_pin) :
  current_digit(0) ,    // all digits start at 0
  next_digit(0) ,
  invert_direction(dir) ,
  stepper(AccelStepper(AccelStepper::DRIVER, step_pin, dir_pin))  {

    stepper.setMaxSpeed(MAX_DIGIT_SPEED);
    stepper.setAcceleration(DIGIT_ACCELERATION);

    pushClockDigit(this) ;  // Register this digit with class

}

// setToDigit
// If the stepper is running, then just queue up the next digit
// We'll wait until the dial has stopped running before we start
// moving to the new digit.
//
// Enable the steppers then move to the next digit the relative
// number of steps needed between where we are now and the new
// digit.
void ClockDigit::setToDigit(int digit) {

  if (digit == current_digit) {
    return ;
  }

  if (stepper.isRunning()) {
    next_digit = digit ;
    return ;
  }

  int delta_digits = digit - current_digit ;
  enableSteppers() ;
  stepper.move(invert_direction * STEPS_PER_DIGIT * delta_digits) ;
  current_digit = digit ;
  next_digit = current_digit;
  return ;
}

// run
// If the stepper just stopped and we have a digit queued up
// start moving to that new digits
//
// Return true if the stepper is running.
bool ClockDigit::run() {
  if (!stepper.isRunning() && (next_digit != current_digit)) {
    setToDigit(next_digit) ;
  }
  stepper.run() ;
  return (stepper.isRunning()) ;
}
