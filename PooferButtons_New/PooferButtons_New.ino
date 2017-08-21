#include <Bounce.h>
#include <avr/pgmspace.h>

class Poofer
{
    //CLass Member Variables
    //These are initialized at startup
    int pooferPin; // the number of Poofer pins
    unsigned int OnTime; // milliseconds of on-time
    elapsedMillis elapsedOn;

    //these maintain the current state
    int pooferState; //pooferState used to set the poofer

    // Constructor - creates a Poofer
    // and initiliazes the member variables and state
  public:
    Poofer(int pin)
    {
      pooferPin = pin;
      pinMode(pooferPin, OUTPUT);

      OnTime = 0;

      pooferState = LOW;
    }

    void On(unsigned int ms)
    {
      if (pooferState == HIGH) {
        unsigned int remainingTime = OnTime - elapsedOn;
        if (remainingTime < ms) {
          OnTime = ms;
        }
      } else
      {
        OnTime = ms;
      }
      elapsedOn = 0;
      pooferState = HIGH; //turn it on
      digitalWrite(pooferPin, pooferState); //update the actual Poofer
    }

    void Off()
    {
      if (pooferState == HIGH) {
        pooferState = LOW;
        digitalWrite(pooferPin, pooferState);
      }
    }

    void patternOn(unsigned int ms)
    {
      elapsedMillis currentMillis;

      while (currentMillis < ms) {
        pooferState = HIGH;
        digitalWrite(pooferPin, pooferState);
      }
      pooferState = LOW;
      digitalWrite(pooferPin, pooferState);
      currentMillis = 0;
    }

    void patternOff(unsigned int ms)
    {
      elapsedMillis currentMillis;

      while (currentMillis < ms) {
        pooferState = LOW;
        digitalWrite(pooferPin, pooferState);
      }
      currentMillis = 0;
    }

    void Update()
    {
      if (pooferState == HIGH) {
        if (elapsedOn > OnTime) {
          pooferState = LOW;
          digitalWrite(pooferPin, pooferState);
        }
      }
    }
};

//buttons on the magic wish lamp
Bounce btn1 = Bounce(1, 10);
Bounce btn2 = Bounce(2, 10);
Bounce btn3 = Bounce(3, 10);

//controller input read through serial
int buttonValue;

int out1 = 19;
int out2 = 18;
int out3 = 17;

int out4 = 16;
int out5 = 15;
int out6 = 14;

Poofer poofLittle1(out1);
Poofer poofLittle2(out2);
Poofer poofLittle3(out3);

Poofer poofBig1(out4);
Poofer poofBig2(out5);
Poofer poofBig3(out6);



//Moopi's fire patterns

//the choo choo train
const int pattern0[] PROGMEM = {
  1, 500, 0, 510,
  2, 500, 0, 510, 
  3, 500, 0, 510,
  4, 500, 0, 510,
  
  2, 500, 0, 510,
  3, 500, 0, 510,
  1, 500, 0, 510,
  4, 500, 0, 510,
  
  3, 500, 0, 510,
  1, 500, 0, 510,
  2, 500, 0, 510,
  6, 500, 0, 510,
  
  1, 500, 0, 510,
  2, 500, 0, 510,
  3, 500, 0, 510,
  4, 500, 0, 510,
  //faster!
  2, 250, 0, 260,
  3, 250, 0, 260,
  2, 250, 0, 260,
  5, 250, 0, 260,
  
  3, 250, 0, 260,
  1, 250, 0, 260,
  2, 250, 0, 260,
  6, 250, 0, 260,
  
  1, 250, 0, 260,
  2, 250, 0, 260,
  3, 250, 0, 260,
  4, 250, 0, 260,
  
  2, 250, 0, 260,
  3, 250, 0, 260,
  1, 250, 0, 260,
  4, 250, 0, 260,
  //faster and faster!
  3, 120, 0, 130,
  1, 120, 0, 130,
  2, 120, 0, 130,
  4, 120, 0, 130,
  
  1, 120, 0, 130,
  2, 120, 0, 130,
  3, 120, 0, 130,
  4, 120, 0, 130,
  
  2, 120, 0, 130,
  3, 120, 0, 130,
  1, 120, 0, 130,
  5, 250, 0, 630,
 //BOOM!
  1, 1000, 
  2, 1000, 
  3, 1000, 
  4, 1000, 
  5, 1000, 
  6, 1000,  0, 1600,
 //BOOM!
  1, 1000, 
  2, 1000, 
  3, 1000, 
  4, 1000, 
  5, 1000, 
  6, 1000,
};
///pop goes the weasel
const int pattern1[] PROGMEM = {
  //Round and round the mulberry bush 
  2, 500, 0, 510,
  3, 500, 0, 510,
  1, 500, 0, 610,
  
  2, 500, 0, 510,
  3, 250, 0, 260,
  4, 250, 0, 260,
  
  2, 250, 0, 260,
  3, 500, 0, 810, 
  //the monkey chased the weasel 
  1, 250, 0, 260,
  2, 250, 0, 260,
  3, 250, 0, 260,
  
  1, 500, 0, 510,
  
  1, 250, 0, 260,
  2, 250, 0, 260,
  3, 250, 0, 260,
  
  1, 500, 0, 810,
  //the monkey thought 'twas all in good fun
  2, 500, 0, 510,
  3, 250, 0, 260,
  1, 250, 0, 360,
  
  2, 250, 0, 260,
  3, 250, 0, 260,
  1, 250, 0, 260,
  2, 250, 0, 260,
  
  3, 250, 0, 260,
  1, 500, 0, 810,
  //POP! 
  1, 1000, 
  2, 1000, 
  3, 1000, 
  4, 1000, 
  5, 1000, 
  6, 1000,  0, 1500,
//Goes 
  2, 250, 0, 360,
  //the weasel
  3, 250, 0, 260,
  1, 250, 0, 260,
  2, 250, 0, 1250,
  //surprise burst
  1, 1000, 
  2, 1000, 
  3, 1000, 
  4, 1000, 
  5, 1000, 
  6, 1000,  
};
//Safety Dance/ Shave and a Haircut 
const int pattern2[] PROGMEM = {
  //safety dance
  3, 500, 0, 510,
  3, 500, 0, 510,
  2, 500, 0, 510,
  2, 500, 0, 510,
  
  3, 500, 0, 510,
  3, 500, 0, 510,
  3, 250, 0, 260,
  2, 500, 0, 510,
  2, 500, 0, 1010,

  2, 500, 0, 510,
  2, 500, 0, 510,
  1, 500, 0, 510,
  1, 500, 0, 510,
  2, 500, 0, 510,
  2, 500, 0, 510,
  2, 250, 0, 260,
  1, 500, 0, 510,
  1, 500, 0, 1010,

  //you can dance if you want to
  1, 250, 0, 260,
  2, 120, 0, 130,
  3, 250, 0, 260,
  1, 250, 0, 260,
  2, 500, 0, 510,
  3, 250, 0, 260,
  3, 250, 0, 760,

  //shave and a haircut
  1, 100, 0, 250,
  1, 100, 0, 150,
  
  1, 100, 0, 150,
  4, 100, 0, 400,
  
  1, 100, 0, 700,
  
  //burst
  1, 100, 
  2, 100, 
  3, 100, 
  4, 100, 
  5, 100, 
  6, 100, 0, 300,

  //burst
  1, 80,
  2, 80,
  3, 80,
  4, 80,
  5, 80,
  6, 80, 0, 280
};
//Ragg Mopp
const int pattern3[] PROGMEM = {
  //ragg mopp!
  1, 500,
  2, 500,
  3, 500,
  4, 500,
  5, 500,
  6, 500, 0, 510,
  
  1, 500,
  2, 500,
  3, 500,
  4, 500,
  5, 500,
  6, 500, 0, 1010,

  //doodley doo de doo doo
  2, 120, 0, 130,
  2, 120, 0, 130,
  1, 120, 0, 130,
  1, 120, 0, 130,
  3, 120, 0, 130,
  3, 500, 0, 510,
  3, 500, 0, 1010,

  1, 500,
  2, 500,
  3, 500,
  4, 500,
  5, 500,
  6, 500, 0, 510,
  
  1, 500,
  2, 500,
  3, 500,
  4, 500,
  5, 500,
  6, 500, 0, 1010,

  1, 120, 0, 130,
  1, 120, 0, 130,
  3, 120, 0, 130,
  3, 120, 0, 130,
  2, 120, 0, 130,
  2, 500, 0, 510,
  2, 500, 0, 1010,

    //ragg mopp!
  1, 500,
  2, 500,
  3, 500,
  4, 500,
  5, 500,
  6, 500, 0, 510,
  
  1, 500,
  2, 500,
  3, 500,
  4, 500,
  5, 500,
  6, 500, 0, 1010,

  //doodley doo de doo doo
  3, 120, 0, 130,
  3, 120, 0, 130,
  2, 120, 0, 130,
  2, 120, 0, 130,
  1, 120, 0, 130,
  1, 500, 0, 510,
  1, 500, 0, 1010,

  1, 500,
  2, 500,
  3, 500,
  4, 500,
  5, 500,
  6, 500, 0, 510,
  
  1, 500,
  2, 500,
  3, 500,
  4, 500,
  5, 500,
  6, 500, 0, 1010,

  2, 120, 0, 130,
  2, 120, 0, 130,
  1, 120, 0, 130,
  1, 120, 0, 130,
  3, 120, 0, 130,
  3, 500, 0, 510,
  3, 500, 0, 1010,

  //R.-A.-G.-G. - M.-O.-P.-P 
  1, 500, 0, 510,
  2, 500, 0, 510,
  3, 500, 0, 510,
  1, 500, 0, 510,
  1, 500, 0, 510,
  2, 500, 0, 510,
  3, 500, 0, 510,
  1, 500, 0, 1010,
  
  //Ragg mopp!  (plus flourish) 
  1, 1000, 
  2, 1000, 
  3, 1000, 
  4, 1000, 
  5, 1000, 
  6, 1000, 0, 1500,

  1, 1000, 
  2, 1000, 
  3, 1000, 
  4, 1000, 
  5, 1000, 
  6, 1000, 0, 1500,
  
  1, 120,
  2, 120,
  3, 120,
  4, 120,
  5, 120,
  6, 120, 0, 130,

  1, 250,
  2, 250,
  3, 250,
  4, 250,
  5, 250,
  6, 250, 0, 260 
};
//Mexican Hat Dance 
const int pattern4[] PROGMEM = {
  //  Di-di di-dee-dee-di-dee, 
  1, 120, 0, 130,
  1, 120, 0, 130,
  2, 250, 0, 260,
  3, 250, 0, 260,
  2, 250, 0, 260,
  3, 250, 0, 260,
  2, 250, 0, 260,
  1, 120, 0, 130,
  4, 250, 0, 260,
  3, 500, 0, 1010,
//  Di-di di-dee-dee-di-doo,  
  3, 120, 0, 130,
  3, 120, 0, 130,
  1, 250, 0, 260,
  2, 250, 0, 260,
  1, 250, 0, 260,
  2, 250, 0, 260,
  1, 250, 0, 260,
  3, 120, 0, 130,
  1, 250, 0, 260,
  4, 500, 0, 1010,
  //  Di-di di-dee-dee-di-dee, 
  2, 120, 0, 130,
  2, 120, 0, 130,
  3, 250, 0, 260,
  1, 250, 0, 260,
  3, 250, 0, 260,
  1, 250, 0, 260,
  3, 250, 0, 260,
  2, 120, 0, 130,
  6, 250, 0, 260,
  1, 500, 0, 510,
  //  Dee-di-dee-dee di dee-
  1, 250, 0, 260,
  1, 120, 0, 130,
  2, 250, 0, 260,
  2, 120, 0, 130,
  3, 250, 0, 260,
  3, 250, 0, 260,
  3, 120, 0, 130,
  2, 250, 0, 260,
  1, 500, 0, 1010,
//pause
  3, 250, 0, 260,
//O-LE!
  1, 1000, 
  2, 1000, 
  3, 1000, 
  4, 1000, 
  5, 1000, 
  6, 1000
};
//Wipe Out 
const int pattern5[] PROGMEM = {
  2, 120, 0, 130,
  3, 250, 0, 260,
  3, 120, 0, 230, //pause
  
  1, 250, 0, 260,
  2, 250, 0, 260,
  3, 250, 0, 260,
  
  4, 250, 0, 260,
  4, 120, 0, 130,
  3, 120, 0, 130,
  1, 250, 0, 260,
  1, 120, 0, 230, //pause
  
  2, 250, 0, 260,
  2, 250, 0, 260,
  3, 250, 0, 260,
  
  1, 250, 0, 260,
  5, 250, 0, 260,
  5, 120, 0, 130,
  
  6, 120, 0, 130,
  4, 250, 0, 260,
  4, 120, 0, 230, //pause
  
  5, 250, 0, 260,
  6, 250, 0, 260,
  4, 250, 0, 260,
  
  2, 250, 0, 260,
  2, 120, 0, 130,
  4, 120, 0, 130,
  
  5, 250, 0, 260,
  5, 250, 0, 360, //pause
  
  6, 250, 0, 260,
  4, 250, 0, 260,
  5, 250, 0, 260,
  3, 250, 0, 260,
  3, 120, 0, 130,
  
  1, 120, 0, 130,
  2, 250, 0, 260,
  2, 120, 0, 230, //pause
  
  3, 250, 0, 260,
  3, 250, 0, 260,
  1, 250, 0, 260,
  5, 250, 0, 260,
  5, 120, 0, 130,
  5, 120, 0, 130,
  5, 120, 0, 130,

  1, 250,
  2, 250,
  3, 250,
  4, 250,
  5, 250,
  6, 250, 0, 260,

  1, 250,
  2, 250,
  3, 250,
  4, 250,
  5, 250,
  6, 250, 0, 260,

  1, 500, 
  2, 500, 
  3, 500, 
  4, 500, 
  5, 500, 
  6, 500, 0, 1500,
  //RANDOM
  1, 120, 0, 121,
  1, 100,
  4, 120,
  1, 80, 0, 131,

  1, 90,
  2, 60,
  3, 120,
  4, 160,
  5, 120,
  6, 180, 0, 190,

  1, 90,
  2, 60,
  3, 120,
  4, 160,
  5, 120,
  6, 180, 0, 201,
  3, 200, 0, 211,
  5, 100,
  4, 120,
  1, 80, 0, 91,

  1, 150, 0, 150,
  6, 120, 0, 180,
  3, 40, 0, 40
};

const int * listOfPatterns[] = {
  pattern0,
  pattern1,
  pattern2,
  pattern3,
  pattern4, 
  pattern5
};
const int patternLengths[] = {
  sizeof(pattern0) / sizeof(int), //do I need to get these using progmem?
  sizeof(pattern1) / sizeof(int),
  sizeof(pattern2) / sizeof(int),
  sizeof(pattern3) / sizeof(int),
  sizeof(pattern4) / sizeof(int),
  sizeof(pattern5) / sizeof(int)
};
const int numberOfPatterns = sizeof(listOfPatterns) / sizeof(const int *);
int pattern_position;
elapsedMillis pattern_elapsed;
bool delayStarted;
int whichPattern = 100;

void start_pattern(int num) //the function that gets called to start the pattern
{
  whichPattern = num;
  delayStarted = false;
  pattern_position = 0; //start at the beginning of the array
  pattern_elapsed = 0;
}

void update_pattern() //runs in the loop
{ 
  if (whichPattern < numberOfPatterns) {
    const int * pattern = listOfPatterns[whichPattern];
    int patternlength = patternLengths[whichPattern];

    int poofer = pgm_read_word(pattern + pattern_position); // use PROGMEM to read the number of poofer being selected
    unsigned int duration = pgm_read_word(pattern + (pattern_position + 1)); //

    if (poofer == 0) { // if the poofer is zero, create a musical rest or delay
      if (delayStarted == false) {
        pattern_elapsed = 0; //we're just starting this beat, so no time has passed
        delayStarted = true;
      } else {
        if (pattern_elapsed > duration) {
          delayStarted = false;
          pattern_position = pattern_position + 2; //move on to the next poofer in the array
          if (pattern_position >= patternlength) {
            whichPattern = 100;
          } else {
            //do nothing - this is the musical rest or beat
            Serial.println("rest");
          }
        }
      }
    } else { // if the poofer isn't zero, fire the poofer number
      poofer_on(poofer, duration);
      pattern_position = pattern_position + 2;
      if (pattern_position >= patternlength) {
        whichPattern = 100;
      }
    }
  }
}

void poofer_on(int num, int duration) //translates the array numbers to the corresponding poofers
{
  if (num == 1) {
    poofLittle1.On(duration);
  } else if (num == 2) {
    poofLittle2.On(duration);
  } else if (num == 3) {
    poofLittle3.On(duration);
  } else if (num == 4) {
    poofBig1.On(duration);
  } else if (num == 5) {
    poofBig2.On(duration);
  } else if (num == 6) {
    poofBig3.On(duration);
  }
}
void setup() {
  Serial1.begin(9600);
  Serial.begin(9600);

  pinMode(1, INPUT_PULLUP);
  pinMode(2, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);

  pinMode(out1, OUTPUT);
  pinMode(out2, OUTPUT);
  pinMode(out3, OUTPUT);

  pinMode(out4, OUTPUT);
  pinMode(out5, OUTPUT);
  pinMode(out6, OUTPUT);

  Serial.println(patternLengths[0]);
}
void loop() {

  btn1.update();
  btn2.update();
  btn3.update();

  // shuts poofers off if they've been on too long
  poofLittle1.Update();
  poofLittle2.Update();
  poofLittle3.Update();

  poofBig1.Update();
  poofBig2.Update();
  poofBig3.Update();

  update_pattern();

  if (Serial1.available())
  {
    buttonValue = Serial1.read();

    //a is b1
    if (buttonValue == 'a')
    {
      Serial1.write(1);
      poofLittle1.On(4000);
    }
    else if (buttonValue == 'A')
    {
      poofLittle1.Off();
    }//c = b2
    else if (buttonValue == 'c')
    {
      Serial1.write(2);
      poofLittle2.On(4000);
    }
    else if (buttonValue == 'C')
    {
      poofLittle2.Off();
    }//f is b3
    else if (buttonValue == 'f')
    {
      Serial1.write(3);
      poofLittle3.On(4000);
    } else if (buttonValue == 'F')
    {
      poofLittle3.Off();
    }//button b4
    else if (buttonValue == 'd')
    {
      Serial1.write(4);
      poofBig1.On(4000);
    }
    else if (buttonValue == 'D')
    {
      poofBig1.Off();
    }
    else if (buttonValue == 'e')
    { //button b5
      Serial1.write(5);
      poofBig2.On(4000);
    }
    else if (buttonValue == 'E')
    {
      poofBig2.Off();
    }
    //b is btn6
    else if (buttonValue == 'b')
    {
      Serial1.write(6);
      poofBig3.On(4000);
    } else if (buttonValue == 'B')
    {
      poofBig3.Off();
    }

    //all little ones on
    else if (buttonValue == 'g')
    {
      poofLittle1.On(4000);
      poofLittle2.On(4000);
      poofLittle3.On(4000);
      Serial1.write(7);
    }
    else if  (buttonValue == 'G')
    {
      poofLittle1.Off();
      poofLittle2.Off();
      poofLittle3.Off();
    }//all big ones on
    else if (buttonValue == 'h')
    {
      poofBig1.On(4000);
      poofBig2.On(4000);
      poofBig3.On(4000);
      Serial1.write(8);
    }
    else if  (buttonValue == 'H')
    {
      poofBig1.Off();
      poofBig2.Off();
      poofBig3.Off();
    }
    //j is x
    else if (buttonValue == 'j')
    {
      Serial1.write(9);
      Serial.println("x");
    }
    else if (buttonValue == 'J')
    {

    }
    // i is j1
    else if (buttonValue == 'i')
    {
      poofLittle1.On(4000);
      poofBig1.On(4000);
      Serial1.write(10);
      Serial.println("j1");
    }
    else if (buttonValue == 'I')
    {
      poofLittle1.Off();
      poofBig1.Off();
    }
    // l is j2
    else if (buttonValue == 'l')
    {
      poofLittle2.On(4000);
      poofBig2.On(4000);
      Serial1.write(11);
      Serial.println("j2");
    }
    else if (buttonValue == 'L')
    {
      poofLittle2.Off();
      poofBig2.Off();
    }
    // k is j3
    else if (buttonValue == 'k')
    {
      poofLittle3.On(4000);
      poofBig3.On(4000);
      Serial1.write(12);
      Serial.println("j3");
    }
    else if (buttonValue == 'K')
    {
      poofLittle3.Off();
      poofBig3.Off();
    }
  }

  //pattern buttons
  if (btn1.fallingEdge())
  {
    start_pattern(5);
    Serial.println("btn 1 pressed");
  }
  //pattern buttons
  if (btn2.fallingEdge())
  {
    start_pattern(1);
    Serial.println("btn 2 pressed");
  }
  //pattern buttons
  if (btn3.fallingEdge())
  {
    start_pattern(2);
    Serial.println("btn 3 pressed");
  }

}
