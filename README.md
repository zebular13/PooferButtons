# PooferButtons
## Setup
PooferButtons and OctoPooferLEDs control three fire poofers and three LED strips via 6 buttons in a triangle (btn_bk1, btn_bk2, btn_bk3 [the black outer ones], btn_b1, btn_b2, btn_b3 [the blue inner ones]), a red button (r) a yellow button (y) and a 4 axis joystick . 


**Parts List:**
* Teensy 3.2
* Teensy 2.0 (x2)
* Teensy breakout board (name?)
* 5 RS45s
* 3 4 meter LED strips with (?) LEDs per strip
* FIRE STUFF & PROPANE!


*PooferButtons* is used on Teensy 2.0 that sits on breakout board with three outputs that control solenoids on the three poofers. 
The control box has four buttons, two potentiometers and kill switch. It also sends a different byte each time a different button is pressed to the Teensy 3.2 loaded with OctoPooferLEDs. Currently the buttons are set up to run these patterns:
* Button 1: shave and a haircut rhythm
* Button 2: "fire dance" rhythm
* Button 3: "wheel of fire" - faster and faster poofs in a circle
* Button 4: ALL OF THEM!

*OctoPooferLEDs* receives the byte that PooferButtons sends when each button is pressed. It controls the LED strips.

## TO DO:
- [X] Make sure Button control sends values to start LED patterns
- [X] Create new LED patterns:
  - [X] Whoosh - streak of LEDs that runs up the strip and arrives at the top as flame as it bursts out
  - [X] Sparkle - math.random to make sparkle effect
- [ ] Fix patterns so they actually sound good (just Ragg Mopp and Mexican Hat Dance)
- [ ] Add other colors to the background
- [ ] Add pointers to make it easy to time LEDs to match patterns 
- [ ] Wire kill switch to main controller to override poofers and turn off LEDs 
- [ ] Create code for holding two buttons at once to trigger patterns

## POTENTIAL FEATURES
- [ ] Add potentiometer control to change speed and open length of poofs (look at Walking Beast's code)
- [ ] Add potentiometer control to LED patterns

## ISSUES:
- [ ] Only one LED per poofer can run at a time during pattern playback (only stores the state of one orange bar. Code would have to be expanded to have an array and remember where 4-5 bars are at once)
