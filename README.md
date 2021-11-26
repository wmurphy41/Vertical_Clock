# Vertical_Clock
 3D Printed Arduino Vertical Clock

## To do list
- [x] Print larger components
- [ ] Print smaller components
- [ ] Breadboard
  - [ ] RTC module
  - [ ] Single stepper motor with 4988 module
  - [ ] 4 steppers with expansion Board
  - [ ] LED backlight
  - [ ] Switches
  - [ ] Full breadboard
- [ ] Create wiring diagrams
- [ ] Build prototype board
- [ ] Write software
- [ ] Test software
- [ ] Assemble
- [ ] Test
- [ ] Finish readme
- [ ] Publish and post


 ## References and Attributions
 This project is based on this
 [reddit comment](https://www.reddit.com/r/arduino/comments/pnyy3g/i_made_a_physical_version_of_the_oddly_satisfying/) from reddit user [ragusa12](https://www.reddit.com/user/ragusa12).  All props to him for concept and physical design.  This project contributes only by making the project more easily reproduced.

 The original posting did not include wiring diagrams.  In creating the designs for this project, I've made some changes that I found made the project easier to develop:
 - Use A4988 stepper motor driver for the 28BYJ-48 motors instead of their default driver.  It takes a little hacking, but it reduces pin requirement for each motor from 2 to 4.
 - Use the A4988 expansion board to simplify wiring.  You plug the four A4988s directly into the expansion board and then just wire the expansion board to your Arduino



 #### Background Information
 Reference material I found useful in replicating the design
 - [RTC tutorial](https://howtomechatronics.com/tutorials/arduino/arduino-ds3231-real-time-clock-tutorial/)
 - [Using 28BYJ-48 stepper motor with A4988 driver](https://www.instructables.com/28BYJ-48-5V-Stepper-Motor-and-A4988-Driver/)


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
- 1x P-channel MOSFET
- 1x npn BJT- Some wire and resistors
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
xx

#### Code
xxx

#### Assembly
xxx


## Usage
Operating instructions:
- xx


## Contributing
- Pull requests are welcome. For major changes, please open an issue first to discuss what you would like to change.
- Please make sure to update tests as appropriate.

## License
[MIT](https://choosealicense.com/licenses/mit/)
