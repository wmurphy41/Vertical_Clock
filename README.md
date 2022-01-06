# Vertical_Clock
 3D Printed Arduino Vertical Clock


 ## Project Overview
 A clock that tells the time with backlit numbers aligned vertically in four number arrays moved by a rack and pinion mechanism with exposed gears.  The clock mechanism comprises an Arduino microcontroller reading the time from an embedded real-time clock (RTC) and driving the four gears through stepper motors.  A rotary switch allows the user to adjust the time manually.

 #### References and Attributions

 This project is based on this
 [reddit comment](https://www.reddit.com/r/arduino/comments/pnyy3g/i_made_a_physical_version_of_the_oddly_satisfying/) from reddit user [ragusa12](https://www.reddit.com/user/ragusa12).  All props to him for concept and physical design.

 #### Modifications from original
  The original posting did not include wiring diagrams.  I've created them for this project and you can find them in the circuits folder.

 In creating the designs for this project, I've made some changes that I found made the project easier to develop and improved usage:
 - Used A4988 stepper motor driver for the 28BYJ-48 motors instead of their default driver.  It takes a little hacking, but it reduces pin requirement for each motor from 2 to 4.
 - Added a rotary switch for adjusting the time for daylight savings or if the RTC battery dies.  Feature allows you to adjust either minutes or hours.
 - Added a calibration mode.  On first starting, the numbers need to be set to be reset to zero before starting to tell time.  Any time there is a power outage, on restart the system goes to calibration mode with the LEDs blinking.  Once you have set the numbers to zero, you push the rotary switch and it starts telling time.


 #### Background Information
 Reference material I found useful in developing this version:
 - [RTC tutorial](https://howtomechatronics.com/tutorials/arduino/arduino-ds3231-real-time-clock-tutorial/)


## Files
Content of the project folders:
- **code** - Arduino code
- **physical** - STL Files
- **circuits** - electronic circuit design
- **media** - pictures and video of project

## Bill of Materials
- 1x Arduino nano
- 1x [A4988 Expansion Board](https://www.amazon.com/gp/product/B01D2HL9T8/ref=ppx_yo_dt_b_asin_title_o01_s00?ie=UTF8&psc=1)
- 4x [12v 28BYJ-48 stepper motors](https://www.amazon.com/gp/product/B015RQ97W8/ref=ppx_yo_dt_b_asin_title_o00_s00?ie=UTF8&psc=1)
- 2x [small led backlight module](amazon.com/gp/product/B01N6XME2Q/ref=ox_sc_act_title_1?smid=ATVPDKIKX0DER&psc=1)
- 4x [A4988 stepper motor drivers](https://www.amazon.com/gp/product/B09FQ3G5XQ/ref=ppx_yo_dt_b_asin_title_o00_s00?ie=UTF8&psc=1)
- 1x [RTC module](https://www.amazon.com/gp/product/B07XY2STMF/ref=ox_sc_act_title_2?smid=A2JLTKYCWT3GQ2&psc=1)
- 1x [12v power supply](https://www.amazon.com/gp/product/B01GD4ZQRS/ref=ppx_yo_dt_b_asin_title_o00_s00?ie=UTF8&th=1)
- 1x [rotary switch](https://www.amazon.com/dp/B07M631J1Q/ref=cm_sw_em_r_mt_dp_0N9X54H6T59A8A89X890?_encoding=UTF8&psc=1)
- 4x 100 mF capacitors
- 2x npn transistors
- 4x 1k ohm resistors
- PLA cable for 3D printer
- 1x C2032 battery for the RTC
- hot glue gun and glue
- nylon spacers and nuts


## Installation
Instructions for building the printed components, electronics, software, and assembly of the Vertical Clock.

#### Printed Components
Print all components in PLA.

| Component  | Count | Color |
| ---------- | ----: | ----- |
| BaseA (1)  |     1 | black |
| BaseB (1)  |     1 | black |
| Gear (4)   |     4 | black |
| LightBrick |     4 | white |
| FullDigit  |     2 | black |
| 6Digit     |     1 | black |
| 3Digit     |     1 | black |
| knob       |     1 | black |

#### Electronics
1. Hack the stepper motors.  The 28BYJ-48 stepper motors are unipolar and the
A4988 driver only works with bipolar motors.  Take the red wire out of the connector,
cut it near the motor and discard.  Reorder the wires in the connector so that
are in order orange, yellow, pink, blue, reading left to right when looking at
the flat side of the connector.  More info on this step [here](https://www.instructables.com/28BYJ-48-5V-Stepper-Motor-and-A4988-Driver/)  I ignored adjusting
the current potentiometer.
2. Build prototype board based on circuit diagrams.  Pins.h matches the pin
configuration of the prototype circuit diagram.  Breadboard diagram used different pins.

#### Code
1. Vertical_Clock - Main folder for final product.  Move this folder to Arduino environment, compile, and upload.  You'll need to install into your Arduino environment all of the libraries referenced in the include files.
  - vertical_clock.ino - primary Arduino file
  - ClockDigit.h and ClockDigit.cpp - class files for controlling stepper motors
  - ClockState.h and ClockState.cpp - class files for managing system state of clock.
2. led_via_npn - folder containing code for breadboarding the led
3. rotary_and_rtc - folder containing code for testing rtc and rotary switch modules
4. stepper - folder containing code for testing stepper motors and clock digits

## Assembly
1. Attach the two halves of the case with Gorilla glue.  Have acetone or rubbing
alcohol on hand to clean up the overspills
2. Install white backplates and affix with hot glue
2. Install motors with bolts and nuts and press on gears
3. Affix LEDs with hot glue
4. Drill hole in case and attach Rotary Switch with nut.  Affix knob.
5.  Affix power socket with hot glue
6. Affix circuit boards with nylon hex spacers hot glued to case and secure with
nylon nuts.

## Usage
Operating instructions

#### Setup and calibration
- Plug in power
- Both lights will flash slowly.  It is in calibration modes
- Gently raise or lower the number bars until each number is set to zero
- Depress the rotary switch to move into normal mode.  
- Both lights will turn on and stop blinking
- The number bars will start moving until the numbers match the current time
in the RTC.

Note that if the clock loses power while running, when power is restored, it will
start in calibration mode.  Use the steps above to set the numbers to zero
before pressing the switch to move it into normal mode.

#### Adjusting time
- _Setting the Minutes:_ Depress the rotary switch.  The clock is now in adjust
minutes mode.  The hour light will turn off
and the minutes light will blink quickly.  Slowly turn the rotary switch.  Each
click will adjust one minute.  Clockwise will add minutes. Counterclockwise will
subtract.  There will be a slight delay from turning the dial to when the numbers
move.  Once the numbers start moving, they will continue until stopped.  If
you turn the dial while the numbers are moving, the numbers will finish the move
until then moving to the new number.  You can only adjust the minutes up to 59
or down to 0.  Once at 59, continuing to turn clockwise will have no effect.  
Once at 0, continuing to turn counterclockwise will have no effect.
- _Setting the Hour:_  From adjust minutes mode, depress the rotary switch.
The clock is now in adjust hour mode.  The minute light will turn off and the
hour light will blink quickly.  Adjust the hours just as with the minutes.  As
with the minutes, you can only adjust the hours up to 23 and down to 0. They
won't roll over from 0 to 23 or from 23 to 0.
- _Returning to Normal Mode:_ From adjust hour mode, depress the switch once.
Both lights will turn on.


## Ideas for Future Enhancements
1. Shift from 24 to 12 hour module.  May need an LED to indicate AM/PM
2. Enable a temperature mode.  Just read the temp from the RTC module and display with the digits. Would need to change the design of the number bars.


## Contributing
- Pull requests are welcome. For major changes, please open an issue first to discuss what you would like to change.
- Please make sure to test updates as appropriate.

## License
[MIT](https://choosealicense.com/licenses/mit/)
