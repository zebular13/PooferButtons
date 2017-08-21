#include <OctoWS2811.h>

const int ledsPerStrip = 240;
const int nStrips = 3;
const int nLeds = 692;
DMAMEM int displayMemory[ledsPerStrip * 6];
int drawingMemory[ledsPerStrip * 6];
const int config = WS2811_GRB | WS2811_800kHz;
OctoWS2811 leds(ledsPerStrip, displayMemory, drawingMemory, config);

#define RED    0x040000
#define RED2   0x0A0000
#define GREEN  0x000400
#define GREEN2 0x000A00
#define BLUE   0x000004
#define BLUE2  0x00000A
#define YELLOW 0x020300
#define YELLOW2 0x050700
#define PINK   0x020002
#define PINK2  0x050005
#define ORANGE 0x030300
#define ORANGE2 0x050500
#define WHITE  0x020202

int rainbowColors[180];
elapsedMillis elapsed_time; 
int buttonValue; //controller input read through serial


void setup() {
  Serial1.begin(9600); //begin the communication with the Teensy 2.0 button box
  Serial.begin(9600);
  leds.begin();
  leds.show();
}

void loop() {
  unsigned long currentTime = 0;
  
  if (Serial1.available()) //listen for signals from the controller
  {//read values from the first teensy to tell which button has been pressed
    buttonValue = Serial1.read();
    //a is b1
    if (buttonValue == 'a')
    {
     //chase yellow up poofer1
    }
    else if (buttonValue == 'A')
    {
      //finish chasing yellow up poofer 1
      //find where it is in the sequence and stop it
    }//c = b2
    else if (buttonValue == 'c')
    {
     //chase red up poofer2
    }
    else if (buttonValue == 'C')
    {
      //find where it is in the sequence and stop it
    }//f is b3
    else if (buttonValue == 'f')
    {
      //chase blue up poofer3
    } else if (buttonValue == 'F')
    {
      //find where it is in the sequence and stop it
    }//button b4
    else if (buttonValue == 'd')
    {
      //chase green up poofer1
    }
    else if (buttonValue == 'D')
    {
      //find where it is in the sequence and stop it
    }
    else if (buttonValue == 'e')
    { //e is b5
      //chase up poofer2
    }
    else if (buttonValue == 'E')
    {
      //find where it is in the sequence and stop it
    }
    //b is btn6
    else if (buttonValue == 'b')
    {
     //chase up poofer2
    } else if (buttonValue == 'B')
    {
      //find where it is in the sequence and stop it
    }
}

