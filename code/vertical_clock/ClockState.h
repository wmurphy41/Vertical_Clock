#ifndef CLOCKSTATE_H
#define CLOCKSTATE_H

class ClockState {
  public:
    enum states { normal, edit_minute, edit_hour, calibrate_mode } ;
    ClockState(int h, int m) ;
    void setup() ;
    void incrementState() ;
    void setLEDs() ;
    int getState() ;

  private:
    int hourLED, minLED ;
    enum states sketchState = normal ;
} ;

#endif //CLOCKSTATE_H
