#include <OctoWS2811.h>

const int ledsPerStrip = 207;

DMAMEM int displayMemory[ledsPerStrip * 6];
int drawingMemory[ledsPerStrip * 6];

const int config = WS2811_GRB | WS2811_800kHz;

OctoWS2811 leds(ledsPerStrip, displayMemory, drawingMemory, config);

void setup() {
  Serial1.begin(9600);
  random(2000);
  leds.begin();
  leds.show();
}

elapsedMillis frameTime;
int vstate1 = 100;
int vstate2 = 100;
int vstate3 = 100;
int vstate4 = 100;
int vstate5 = 100;
int vstate6 = 100;
float background_hue = 189.0; //default to mid-blue


void loop() {
  // Check for commands from controller
  checkSerial();
  if (frameTime > 20) {
    frameTime -= 20; //update every 2ms. 35 frames x 20 ms per frame = 700

    // draw color changing background
    colorBackground();

    // vertical up sweep on wish #1
    if (vstate1 < 35) {
      int b = (float)vstate1 * 5.8; // 207/35 = 5.9
      int e = b + 12; //for the first it's 12, 17.8, 23.6 - this is the width of the strip
      if (e >= ledsPerStrip) e = ledsPerStrip - 1;
      for (int i = b; i < e; i++) { // (i = 5.8, i < 17.8, i++)
        leds.setPixel(i, 0xFF7800);
      }
      //Serial.printf("vstate1 = %d\n", vstate1);
      vstate1++;
    }
    // vertical up sweep on wish #2
    if (vstate2 < 35) {
      int b = (float)vstate2 * 5.8;
      int e = b + 12;
      if (e >= ledsPerStrip) e = ledsPerStrip - 1;
      for (int i = b; i < e; i++) {
        leds.setPixel(ledsPerStrip + i, 0xFF7800);
      }
      //Serial.printf("vstate2 = %d\n", vstate2);
      vstate2++;
    }
    // vertical up sweep on wish #3
    if (vstate3 < 35) {
      int b = (float)vstate3 * 5.8;
      int e = b + 12;
      if (e >= ledsPerStrip) e = ledsPerStrip - 1;
      for (int i = b; i < e; i++) {
        leds.setPixel(ledsPerStrip * 2 + i, 0xFF7800);
      }
      //Serial.printf("vstate3 = %d\n", vstate3);
      vstate3++;
    }

    //FAST SWOOSHES
    // vertical up sweep on wish #1
    if (vstate4 < 12.5) { // 250/20 = 12.5
      int b = (float)vstate4 * 16.56;
      int e = b + 12;
      if (e >= ledsPerStrip) e = ledsPerStrip - 1;
      for (int i = b; i < e; i++) {
        leds.setPixel(i, 0xFF7800);
      }
      //Serial.printf("vstate1 = %d\n", vstate1);
      vstate4++;
    }
    // vertical up sweep on wish #2
    if (vstate5 < 12.5) {
      int b = (float)vstate5 * 16.56;
      int e = b + 12;
      if (e >= ledsPerStrip) e = ledsPerStrip - 1;
      for (int i = b; i < e; i++) {
        leds.setPixel(ledsPerStrip + i, 0xFF7800);
      }
      //Serial.printf("vstate2 = %d\n", vstate2);
      vstate5++;
    }
    // vertical up sweep on wish #3
    if (vstate6 < 12.5) {
      int b = (float)vstate6 * 16.56;
      int e = b + 12;
      if (e >= ledsPerStrip) e = ledsPerStrip - 1;
      for (int i = b; i < e; i++) {
        leds.setPixel(ledsPerStrip * 2 + i, 0xFF7800);
      }
      //Serial.printf("vstate3 = %d\n", vstate3);
      vstate6++;
    }
    // always update the LEDs every frame
    leds.show();
  }
}

void checkSerial() {
  if (Serial1.available()) {
    int cmd = Serial1.read();
    Serial.printf("cmd = %d\n", cmd);
    if (cmd == 10) {
      vstate1 = 0; // Wish #1 vertical up sweep, 35 frames = 700 ms
    }
    if (cmd == 11) {
      vstate2 = 0; // Wish #2 vertical up sweep, 35 frames = 700 ms
    }
    if (cmd == 12) {
      vstate3 = 0; // Wish #3 vertical up sweep, 35 frames = 700 ms
    }

    //faster swooshes
    if (cmd == 13) {
      vstate4 = 0; // Wish #1 vertical up sweep, 35 frames = 700 ms
    }
    if (cmd == 14) {
      vstate5 = 0; // Wish #2 vertical up sweep, 35 frames = 700 ms
    }
    if (cmd == 15) {
      if (vstate6 > 0 && vstate6 < 35) {

      } else {
        vstate6 = 0; // Wish #3 vertical up sweep, 35 frames = 700 ms
      }
    }
  }
}
void colorBackground() {
  float deltahue = ((float)((int)random(2000) - 1000)) * 0.003; // -2.0 to +2.0
  deltahue += (background_hue - background_hue) * 0.001; // bias towards 269.0
  //Serial.printf("deltahue = %.2f\n", deltahue);
  background_hue += deltahue;
  if (background_hue > 309.0) background_hue = 309.0; //don't get too purple
  if (background_hue < 20.0) background_hue = 20.0; //don't get too yellow-green
  unsigned int hue = background_hue;
  //Serial.printf("hue = %d\n", hue);

  for (int i = 0; i < ledsPerStrip; i++) {
    unsigned int saturation = 70 + random(25);
    unsigned int lightness = 20 + random(10);
    leds.setPixel(i, makeColor(hue - (i * 0.6), saturation + (i * 0.6), lightness));
  }
  for (int i = ledsPerStrip; i < ledsPerStrip * 2; i++) {
    unsigned int saturation = 70 + random(25);
    unsigned int lightness = 20 + random(10);
    leds.setPixel(i, makeColor(hue - ((i - ledsPerStrip) * 0.6), saturation + ((i - ledsPerStrip) * 0.6), lightness));
  }
}

