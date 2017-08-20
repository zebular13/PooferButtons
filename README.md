# PooferButtons
## Setup
PooferButtons and OctoPooferLEDs control three fire poofers and three LED strips via 4 buttons and two potentiometer. **Note:** *PooferButtons_New* hasn't been tested - it's where I'm adding the potentiometer control. 

**Parts List:**
* Teensy 3.2
* Teensy 2.0
* Teensy breakout board (name?)
* 2 RS45s
* 3 4 meter LED strips with 60 LEDs per strip
* FIRE STUFF & PROPANE!


*PooferButtons* is used on Teensy 2.0 that sits on breakout board with three outputs that control solenoids on the three poofers. 
The control box has four buttons, two potentiometers and kill switch. It also sends a different byte each time a different button is pressed to the Teensy 3.2 loaded with OctoPooferLEDs. Currently the buttons are set up to run these patterns:
* Button 1: shave and a haircut rhythm
* Button 2: "fire dance" rhythm
* Button 3: "wheel of fire" - faster and faster poofs in a circle
* Button 4: ALL OF THEM!

*OctoPooferLEDs* receives the byte that PooferButtons sends when each button is pressed. It controls the LED strips.

## TO DO:
- [ ] Create code for holding two buttons at once to trigger patterns
- [ ] Wire kill switch
- [ ] Make kill switch override poofers 
- [ ] Add potentiometer control to change speed and open length of poofs (look at Walking Beast's code)
- [ ] Create new LED patterns:
  - [ ] Whoosh - streak of LEDs that runs up the strip and arrives at the top as flame as it bursts out
  - [ ] Sparkle - math.random to make sparkle effect
- [ ] Fix timing in Button control to match LED patterns
- [ ] Add potentiometer control to LED patterns

## ISSUES:
makeColor.ino file is not always recognized when OctoPooferLEDs is loaded.
