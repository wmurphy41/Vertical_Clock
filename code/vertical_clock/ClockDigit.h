#ifndef CLOCKDIGIT_H
#define CLOCKDIGIT_H

#include <AccelStepper.h>


// ClockDigit class
// Built around the AccelStepper classs
// Each clock digit keeps track of what digit it is
// currently representing and then moves the stepper motor
// the relative number of steps needed to get to the next
// digit.
//
// The class has static methods that perform functions that
// affect all registered objects in the class
class ClockDigit {
private:
  // constants
  static const int STEPS_PER_REVOLUTION = 2048 ;
  static const int STEPS_PER_DIGIT = 560 ;
  static const int MAX_DIGIT_SPEED = 2500 ; // steps per sec. 4k is max for arduino
  static const int DIGIT_ACCELERATION = 30 ;
  static const int NUM_DIGITS = 4 ;

  // Static class members
  static int enable_pin ;
  static int sp ;
  static ClockDigit *digit_stack[NUM_DIGITS] ;

  // Digits are zero to (num_digits - 1) [inclusive]
  int current_digit ;
  int next_digit ;
  int invert_direction ;
  AccelStepper stepper ;

public:
  enum Digit_Dir {FWD = 1, REV = -1} ;

  // static class methods
  static void setup() ;
  static void pushClockDigit(ClockDigit *cd_ptr) ;
  static bool run_all() ;
  static void enableSteppers() ;
  static void disableSteppers() ;

  // constructor/methods
  ClockDigit(int dir, int step_pin, int dir_pin) ;
  void setToDigit(int digit) ;
  bool run() ;

};



#endif //CLOCKDIGIT_H
