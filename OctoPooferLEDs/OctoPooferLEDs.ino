//This is the LED code for three strips of LEDs.
//It's written for the Teensy 3.2, which receives button press signals
// from the Teensy 2.0 that has PooferButtons.ino loaded on it.
#include <OctoWS2811.h>
int rainbowColors[180];
const int ledsPerStrip = 240;

DMAMEM int displayMemory[ledsPerStrip * 6];
int drawingMemory[ledsPerStrip * 6];

const int config = WS2811_GRB | WS2811_800kHz;

OctoWS2811 leds(ledsPerStrip, displayMemory, drawingMemory, config);


int buttonValue;

void setup() {
  //initialize the 180 rainbow colors
  for (int i = 0; i < 180; i++) {
    int hue = i * 2;
    int saturation = 100;
    int lightness = 50;
    // pre-compute the 180 rainbow colors
    rainbowColors[i] = makeColor(hue, saturation, lightness);
  }
  Serial1.begin(9600); //begin the communication with the Teensy 2.0 button box
  Serial.begin(9600);
  leds.begin();
  leds.show();
}
//predefine some colors
#define RED    0xFF0000
#define GREEN  0x00FF00
#define BLUE   0x0000FF
#define YELLOW 0xFFFF00
#define PINK   0xFF1088
#define ORANGE 0xE05800
#define WHITE  0xFFFFFF
#define OFF    0x000000

void loop() {
  int microsec = 100 / leds.numPixels();  // change them all in 2 seconds

  if (Serial1.available()) {
    buttonValue = Serial1.read();

    if (buttonValue == 1) {
      Serial.println(String("button 1")); //BOTTOM BUTTON 'shave and a haircut' - rainbow LEDs.
      rainbow(10, 800);
    }

    else if (buttonValue == 2) { //LEFT BUTTON 'fire dance' single colored lights whiz around for a bit
      Serial.println(String("button 2"));
      for (int i = 0; i < ledsPerStrip; i = i + 5) {
        leds.setPixel(i, YELLOW);
        leds.setPixel(i + ledsPerStrip, ORANGE);
        leds.setPixel(i + 480, RED);
        leds.show();
        delayMicroseconds(5);
        leds.setPixel(i, 0);
        leds.setPixel(i + ledsPerStrip, 0);
        leds.setPixel(i + 480, 0);
        leds.show();
        delayMicroseconds(1);
      }
      for (int i = ledsPerStrip; i > 0; i = i - 5) {
        leds.setPixel(i, PINK);
        leds.setPixel(i + ledsPerStrip, BLUE);
        leds.setPixel(i + 480, GREEN);
        leds.show();
        delayMicroseconds(5);
        leds.setPixel(i, 0);
        leds.setPixel(i + ledsPerStrip, 0);
        leds.setPixel(i + 480, 0);
        leds.show();
        delayMicroseconds(1);
      }
    }

    else if (buttonValue == 3) { //TOP BUTTON 'wheel of fire' this one is actually decent
      Serial.println(String("button 3"));
      wipe(RED, 1, 10, 0);
      wipe(PINK, 1, 2, 0);
      wipe(OFF, 1, 3, 0);
      wipe(GREEN, 1, 10, 0);
      wipe(YELLOW, 1, 3, 0);
    }

    else if (buttonValue == 4) { //RIGHT BUTTON 'ALL OF THEM' - REALLY BORING
      Serial.println(String("button 4"));
      for (int i = 0; i < ledsPerStrip; i++) {
        leds.setPixel(i, RED);
        leds.setPixel(i + ledsPerStrip, BLUE);
        leds.setPixel(i + (ledsPerStrip * 2), WHITE);
        leds.show();
        delayMicroseconds(1);
        for (int i = 0; i < ledsPerStrip; i++) {
          leds.setPixel(i, WHITE);
          leds.setPixel(i + ledsPerStrip, RED);
          leds.setPixel(i + (ledsPerStrip * 2), BLUE);
          leds.show();
        }
      }
    }
  }
}
//the wipe function changes the LEDs on each strip one by one
//add the color value. the wait time, the step
//(makes it go faster by skipping LEDs) and the direction
void wipe(int color, int wait, int step, byte direction) {
  if (direction == 0) { //0 makes the direction go forward, or up the strip // any other value for direction is reverse
    for (int i = 0; i < ledsPerStrip; i + step) {
      leds.setPixel(i, color);
      leds.setPixel(i + ledsPerStrip, color);
      leds.setPixel(i + (ledsPerStrip * 2), color);
      leds.show();
      delayMicroseconds(wait);
    }
  } else {
    for (int i = ledsPerStrip; i > 0; i = i - step) {
      leds.setPixel(i, color);
      leds.setPixel(i + ledsPerStrip, color);
      leds.setPixel(i + (ledsPerStrip * 2), color);
      leds.show();
      delayMicroseconds(wait);
    }
  }
}
// The rainbow function
// phaseShift is the shift between each row.  phaseShift=0
// causes all rows to show the same colors moving together.
// phaseShift=180 causes each row to be the opposite colors
// as the previous.
//
// cycleTime is the number of milliseconds to shift through
// the entire 360 degrees of the color wheel:
// Red -> Orange -> Yellow -> Green -> Blue -> Violet -> Red
void rainbow(int phaseShift, int cycleTime) {
  int color, x, y, offset, wait;

  wait = cycleTime * 1000 / ledsPerStrip;
  for (color = 0; color < 180; color++) {
    digitalWrite(1, HIGH);
    for (x = 0; x < ledsPerStrip; x++) {
      for (y = 0; y < 8; y++) {
        int index = (color + x + y * phaseShift / 2) % 180;
        leds.setPixel(x + y * ledsPerStrip, rainbowColors[index]);
      }
    }
    leds.show();
    digitalWrite(1, LOW);
    delayMicroseconds(wait);
  }
}

