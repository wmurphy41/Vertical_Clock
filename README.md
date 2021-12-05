# Vertical_Clock
 3D Printed Arduino Vertical Clock

## To do list
- [x] Print larger components
- [ ] Print smaller components - in progress
- [ ] Breadboard
  - [x] RTC module
  - [x] Rotary Switch
  - [ ] Single stepper motor with 4988 module
  - [ ] 4 steppers with expansion Board
  - [ ] LED backlight
  - [ ] Full breadboard
- [ ] Create wiring diagrams
- [ ] Build prototype board
- [ ] Write software
- [ ] Test software
- [ ] Assemble
- [ ] Test
- [ ] Finish readme
- [ ] Publish and post


 ## Project Overview
 A clock that tells the time with backlit numbers aligned vertically in four number arrays moved by a rack and pinion mechanism with exposed gears.  The clock mechanism comprises an Arduino microcontroller reading the time from an embedded real-time clock (RTC) and driving the four gears through stepper motors based on the time maintained.  A rotary switch allows the user to adjust the time manually.

 #### References and Attributions

 This project is based on this
 [reddit comment](https://www.reddit.com/r/arduino/comments/pnyy3g/i_made_a_physical_version_of_the_oddly_satisfying/) from reddit user [ragusa12](https://www.reddit.com/user/ragusa12).  All props to him for concept and physical design.

 #### Modifications from original
  The original posting did not include wiring diagrams.  I've created them for this project and you can find them in the circuits folder.

 In creating the designs for this project, I've made some changes that I found made the project easier to develop and improved usage:
 - Use A4988 stepper motor driver for the 28BYJ-48 motors instead of their default driver.  It takes a little hacking, but it reduces pin requirement for each motor from 2 to 4.
 - Use the A4988 expansion board to simplify wiring.  You plug the four A4988s directly into the expansion board and then just wire the expansion board to your Arduino
 - Incorporated a voltage regulator to create a 5v bus to simplify the wiring
 - Added a rotary switch for adjusting the time for daylight savings or if the RTC battery dies.


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
- 5v voltage regulator
- 2x 220 ohm resistors
- PLA cable for 3D printer
- 1x C2032 battery


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

#### Electronics
1. Hack the stepper motors.  The 28BYJ-48 stepper motors are unipolar and the
A4988 driver needs bipolar motors.  Take the red wire out of the connector,
cut it near the motor and discard.  Reorder the wires in the connector so that
are in order orange, yellow, pink, blue, reading left to right when looking at
the flat side of the connector.  More info on this step [here](https://www.instructables.com/28BYJ-48-5V-Stepper-Motor-and-A4988-Driver/)

#### Code
xxx

#### Assembly
1. Attach the two halves of the case with Gorilla glue.  Have acetone or rubbing
alcohol ready to clean up the overspills


## Usage
Operating instructions:
- xx


## Contributing
- Pull requests are welcome. For major changes, please open an issue first to discuss what you would like to change.
- Please make sure to update tests as appropriate.

## License
[MIT](https://choosealicense.com/licenses/mit/)
