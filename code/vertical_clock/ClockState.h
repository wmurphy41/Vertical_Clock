#ifndef CLOCKSTATE_H
#define CLOCKSTATE_H

// ClockState class keeps track of the current state of the clock
// and manages the behavior of the LEDs to match.
class ClockState {
  public:
    enum states { normal, edit_minute, edit_hour, calibrate_mode } ;
    ClockState(int h, int m) ;
    void setup() ;
    void incrementState() ;
    void setLEDs() ;
    int getState() ;

  private:
    static const int FAST_BLINK = 1000 ; // Blinks every 1s
    static const int SLOW_BLINK = 2000 ; // Blinks ever 2s
    int hourLED, minLED ;
    enum states sketchState = normal ;
} ;

#endif //CLOCKSTATE_H
