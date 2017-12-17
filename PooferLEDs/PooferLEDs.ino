#include <OctoWS2811.h>

const int ledsPerStrip = 207;

DMAMEM int displayMemory[ledsPerStrip*6];
int drawingMemory[ledsPerStrip*6];

const int config = WS2811_GRB | WS2811_800kHz;

OctoWS2811 leds(ledsPerStrip, displayMemory, drawingMemory, config);

void setup() {
  Serial1.begin(9600);
  random(2000);
  leds.begin();
  leds.show();
}

#define RED    0xFF0000
#define GREEN  0x00FF00
#define BLUE   0x0000FF
#define YELLOW 0xFFFF00
#define PINK   0xFF1088
#define ORANGE 0xE05800
#define WHITE  0xFFFFFF

elapsedMillis frameTime;
int vstate1=10000;
int vstate2=10000;
int vstate3=10000;
float background_hue = 269.0;


void loop() {
  // Check for commands from controller
  if (Serial1.available()) {
    int cmd = Serial1.read();
    //Serial.printf("cmd = %d\n", cmd);
    if (cmd == 10) {
      vstate1 = 0; // Wish #1 vertical up sweep, 35 frames = 700 ms
    }
    if (cmd == 11) {
      vstate2 = 0; // Wish #2 vertical up sweep, 35 frames = 700 ms
    }
    if (cmd == 12) {
      vstate3 = 0; // Wish #3 vertical up sweep, 35 frames = 700 ms
    }
  }
  // Check for commands from Arduino Serial Monitor (testing only)
  if (Serial.available()) {
    int c = Serial.read();
    if (c == 'a') vstate1 = 0;
    if (c == 'b') vstate2 = 0;
    if (c == 'c') vstate3 = 0;
  }
  
  if (frameTime > 20) {
    //Serial.println("draw");
    frameTime -= 20;

    // draw color changing background
    float deltahue = ((float)((int)random(2000) - 1000)) * 0.003; // -2.0 to +2.0
    deltahue += (269.0 - background_hue) * 0.001; // bias towards 269.0
    //Serial.printf("deltahue = %.2f\n", deltahue);
    background_hue += deltahue;
    if (background_hue > 359.0) background_hue = 359.0;
    if (background_hue < 179.0) background_hue = 179.0;
    unsigned int hue = background_hue;
    //Serial.printf("hue = %d\n", hue);
    for (int i=0; i < ledsPerStrip*3; i++) {
      unsigned int saturation = 70 + random(25); 
      unsigned int lightness = 20 + random(10);
      leds.setPixel(i, makeColor(hue, saturation, lightness));
    }

    // vertical up sweep on wish #1
    if (vstate1 < 35) {
      int b = (float)vstate1 * 5.8;
      int e = b + 12;
      if (e >= ledsPerStrip) e = ledsPerStrip-1;
      for (int i=b; i < e; i++) {
        leds.setPixel(i, 0xFF7800);
      }
      //Serial.printf("vstate1 = %d\n", vstate1);
      vstate1++;
    }
    // vertical up sweep on wish #2
    if (vstate2 < 35) {
      int b = (float)vstate2 * 5.8;
      int e = b + 12;
      if (e >= ledsPerStrip) e = ledsPerStrip-1;
      for (int i=b; i < e; i++) {
        leds.setPixel(ledsPerStrip + i, 0xFF7800);
      }
      //Serial.printf("vstate2 = %d\n", vstate2);
      vstate2++;
    }
    // vertical up sweep on wish #3
    if (vstate3 < 35) {
      int b = (float)vstate3 * 5.8;
      int e = b + 12;
      if (e >= ledsPerStrip) e = ledsPerStrip-1;
      for (int i=b; i < e; i++) {
        leds.setPixel(ledsPerStrip*2 + i, 0xFF7800);
      }
      //Serial.printf("vstate3 = %d\n", vstate3);
      vstate3++;
    }
    // always update the LEDs every frame
    leds.show();
  }
}



