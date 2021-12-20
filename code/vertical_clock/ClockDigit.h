#ifndef CLOCKDIGIT_H
#define CLOCKDIGIT_H

#include <AccelStepper.h>

class ClockDigit {
  static const int STEPS_PER_REVOLUTION = 2048 ;
  static const int STEPS_PER_DIGIT = 560 ;
  static const int MAX_DIGIT_SPEED = 2500 ; // steps per sec. 4k is max for arduino
  static const int DIGIT_ACCELERATION = 30 ;

  // Digits are zero to (num_digits - 1) [inclusive]
  int current_digit ;
  int invert_direction ;
  AccelStepper stepper ;

public:
  enum Digit_Dir {FWD = 1, REV = -1} ;
  ClockDigit(int dir, int step_pin, int dir_pin) ;
  void setToDigit(uint8_t digit) ;
  void run() ;
 
 };

#endif //CLOCKDIGIT_H
