#ifndef CLOCKDIGIT_H
#define CLOCKDIGIT_H

#include <AccelStepper.h>

class ClockDigit {
private:
  static const int STEPS_PER_REVOLUTION = 2048 ;
  static const int STEPS_PER_DIGIT = 560 ;
  static const int MAX_DIGIT_SPEED = 2500 ; // steps per sec. 4k is max for arduino
  static const int DIGIT_ACCELERATION = 30 ;
  static int enable_pin ;

  // Digits are zero to (num_digits - 1) [inclusive]
  int current_digit ;
  int next_digit ;
  int invert_direction ;
  AccelStepper stepper ;

public:
  static void setup() ;
  static void enableSteppers() ;
  static void disableSteppers() ;
  enum Digit_Dir {FWD = 1, REV = -1} ;
  ClockDigit(int dir, int step_pin, int dir_pin) ;
  void setToDigit(int digit) ;
  bool run() ;
  
};



#endif //CLOCKDIGIT_H
