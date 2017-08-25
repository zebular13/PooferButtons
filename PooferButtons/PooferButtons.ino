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

    void On(unsigned int ms) //this one turns them on and off at the same time.
    { // Use with the pattern function
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

    //    void patternOn(unsigned int ms) //this one turns them on and off sequentially
    //    {
    //      elapsedMillis currentMillis;
    //
    //      while (currentMillis < ms) {
    //        pooferState = HIGH;
    //        digitalWrite(pooferPin, pooferState);
    //      }
    //      pooferState = LOW;
    //      digitalWrite(pooferPin, pooferState);
    //      currentMillis = 0;
    //    }

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
Bounce btn1 = Bounce(1, 10); //buttons on the magic wish lamp
Bounce btn2 = Bounce(2, 10);
Bounce btn3 = Bounce(3, 10);

int buttonValue; //controller input read through serial

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

long randomNumber; //random number for selecting a random pattern
//-----------Moopi's fire patterns------------//
//FOR LEDS:
//10 is poofer 4
//11 is poofer 5
//12 is poofer 6
//if we have enough time, add code for the short bursts

//The choo choo train
const int pattern0[] PROGMEM = {
  1, 500, 0, 501, // 1 is the valve #, 500 is how long the valve is open in milliseconds,
  2, 500, 0, 501, //0 means the valve is closed. 501 - (how long the valve was open) is how long the valve is closed
  3, 500, 0, 501, // 501 - 500 = 10 milliseconds or 1/10th of a second
  4, 500, 0, 501,
  
  2, 500, 0, 501,
  3, 500, 0, 501,
  1, 500, 0, 501,
  4, 500, 0, 501,

  3, 500, 0, 501,
  1, 500, 0, 501,
  2, 500, 0, 501,
  6, 500, 0, 501,

  1, 500, 0, 501,
  2, 500, 0, 501,
  3, 500, 0, 501,
  4, 500, 0, 501,
  //faster!
  2, 250, 0, 251,
  3, 250, 0, 251,
  2, 250, 0, 251,
  5, 250, 0, 251,

  3, 250, 0, 251,
  1, 250, 0, 251,
  2, 250, 0, 251,
  6, 250, 0, 251,

  1, 250, 0, 251,
  2, 250, 0, 251,
  3, 250, 0, 251,
  4, 250, 0, 251,

  2, 250, 0, 251,
  3, 250, 0, 251,
  1, 250, 0, 251,
  4, 250, 0, 251,
  //faster and faster!
  3, 120, 0, 121,
  1, 120, 0, 121,
  2, 120, 0, 121,
  4, 120, 0, 121,
  
  1, 120, 0, 121,
  3, 25, 0, 26,
  10, 0, //start sending the yellow leds 7 milliseconds before the first burst
  11, 0, 
  12, 0, 
  3, 94, 0, 95,
  2, 120, 0, 121,


  4, 120, 0, 121,
  2, 120, 0, 121,
  3, 120, 0, 121,
  10, 0, //start sending the yellow leds 7 milliseconds before the second burst
  11, 0, 
  12, 0, 
  1, 120, 0, 121,

  //BOOM!
  1, 800,
  2, 800,
  3, 800,
  4, 500,
  5, 500,
  6, 500, 0, 579,

  //BOOM!
  
  1, 800,
  2, 800,
  3, 800,
  4, 500,
  5, 500,
  6, 500, 0,500
};
///pop goes the weasel - not too bad - a little fast
const int pattern1[] PROGMEM = {
  //Round and round the mulberry bush
  2, 500, 0, 501,
  3, 500, 0, 501,
  1, 402, 0, 403,
  10, 0,
  1, 197, 0, 198,
  2, 250, 0, 251,
  3, 250, 0, 251,
  4, 250, 0, 251,

  2, 250, 0, 251,
  3, 500, 0, 810,
  //the monkey chased the weasel
  1, 250, 0, 251,
  2, 250, 0, 251,
  3, 250, 0, 251,

  1, 500, 0, 501,

  1, 250, 0, 251,
  2, 250, 0, 251,
  3, 250, 0, 251,

  1, 500, 0, 810,
  //the monkey thought 'twas all in good fun
  2, 500, 0, 501,
  3, 250, 0, 251,
  1, 250, 0, 351,

  2, 250, 0, 251,
  3, 250, 0, 251,
  1, 250, 0, 251,
  2, 250, 0, 251,

  3, 250, 0, 251,
  1, 109, 0, 110,
  10, 0, 
  11, 0, 
  12, 0, 
  1, 391, 0, 700,
  //POP!

  1, 900,
  2, 900,
  3, 900,
  4, 900,
  5, 900,
  6, 900,  0, 1500,
  //Goes
  2, 250, 0, 351,
  //the weasel
  3, 250, 0, 251,
  1, 250, 0, 251,
  2, 250, 0, 550,
  //surprise burst
  10, 0, 
  11, 0, 
  12, 0, 0, 700,
   
  1, 200,
  2, 200,
  3, 200,
  4, 100,
  5, 100,
  6, 700
};
//Safety Dance/ Shave and a Haircut
const int pattern2[] PROGMEM = {
  //safety dance
  12, 0,// 12 equals a vertical led animation, duration is 700
  12, 0,
  3, 200, 0, 350,
  3, 200, 0, 350,

  6, 200, 0, 350,
  6, 200, 0, 280,
  10, 0,
  10, 0, 0, 70,
  3, 200, 0, 350,
  3, 200, 0, 300,
  1, 100, 0, 120,

  4, 200, 0, 350,
  4, 200, 0, 350,

  12, 0,
  12, 0,
  3, 200, 0, 350,
  3, 200, 0, 350,

  6, 200, 0, 350,
  6, 200, 0, 280,
  10, 0,
  10, 0, 0, 70,
  3, 200, 0, 350,
  3, 200, 0, 300,
  1, 100, 0, 120,
  
  4, 200, 0, 350,
  4, 200, 0, 2350,

  //you can dance if you want to
  //  1, 250, 0, 251,
  //  2, 120, 0, 121,
  //  3, 250, 0, 251,
  //  1, 250, 0, 251,
  //  2, 500, 0, 501,
  //  3, 250, 0, 251,
  //  3, 250, 0, 760,

  //shave and a haircut
  1, 100, 0, 250,
  1, 100, 0, 150,

  1, 100, 0, 150,
  4, 100, 0, 400,
  10, 0,
  11, 0,
  12, 0,
  1, 100, 0, 300,
  10, 0,
  11, 0,
  12, 0,
  1, 100, 0, 400,
  //burst
  1, 100,
  2, 100,
  3, 100, 
  4, 100,
  5, 100,
  6, 300,

  //burst
  1, 80,
  2, 80,
  3, 80,
  4, 80,
  5, 80,
  6, 80, 0, 280,
};
//Ragg Mopp
const int pattern3[] PROGMEM = {
  10, 0,
  11, 0,
  12, 0,
  0, 700,
  10, 0,
  11, 0,
  12, 0,
  //ragg mopp!
  
  1, 500,
  2, 500,
  3, 500,
  4, 500,
  5, 500,
  5, 500,
  6, 500, 0, 700,
  
  1, 500,
  2, 500,
  3, 500,
  4, 500,
  5, 500,
  6, 500, 0, 1010,

  //doodley doo de doo doo
  2, 120, 0, 121,
  2, 120, 0, 121,
  1, 120, 0, 121,
  1, 120, 0, 121,
  3, 120, 0, 121,
  3, 500, 0, 501,
  3, 500, 0, 811,

  10, 0,
  11, 0,
  12, 0, 0, 199,
  1, 500,
  2, 500,
  3, 500, 0, 501,

  1, 500,
  2, 500,
  3, 500,
  4, 500,
  5, 500,
  6, 500, 0, 1010,

  1, 120, 0, 121,
  1, 120, 0, 121,
  3, 120, 0, 121,
  3, 120, 0, 121,
  2, 120, 0, 121,
  2, 500, 0, 501,
  2, 300, 0, 301,

  10, 0,
  11, 0,
  12, 0, 
  2, 200, 0, 500,
  10, 0,
  11, 0,
  12, 0, 
  2, 200, 0, 200,
  //ragg mopp!

  4, 400,
  5, 400,
  6, 400, 0, 500,

  1, 500,
  2, 500,
  3, 500,
  4, 500,
  5, 500,
  6, 500, 0, 1001,

  //doodley doo de doo doo
  3, 120, 0, 121,
  3, 120, 0, 121,
  2, 120, 0, 121,
  2, 120, 0, 121,
  1, 120, 0, 121,
  1, 500, 0, 501,
  1, 500, 0, 702,
  10, 0,
  11, 0,
  12, 0, 0, 199,
  1, 500,
  2, 500,
  3, 500, 0, 501,
  

  1, 500,
  2, 500,
  3, 500,
  4, 500,
  5, 500,
  6, 500, 0, 1010,

  2, 120, 0, 121,
  2, 120, 0, 121,
  1, 120, 0, 121,
  1, 120, 0, 121,
  3, 120, 0, 121,
  3, 500, 0, 501,
  3, 500, 0, 1010,

  //R.-A.-G.-G. - M.-O.-P.-P
  1, 500, 0, 501,
  2, 500, 0, 501,
  3, 500, 0, 501,
  1, 500, 0, 501,
  1, 500, 0, 501,
  2, 500, 0, 501,
  3, 500, 0, 501,
  1, 300, 0, 301,
  10, 0,
  11, 0,
  12, 0,
  1, 200, 0, 700,
  //Ragg mopp!  (plus flourish)
  1, 1000,
  2, 1000,
  3, 1000,
  4, 1000,
  5, 1000,
  6, 1000, 0, 800,
  10, 0,
  11, 0,
  12, 0,0, 700,
  
  1, 1000,
  2, 1000,
  3, 1000,
  4, 1000,
  5, 1000,
  6, 1000, 0, 800,
  10, 0,
  11, 0,
  12, 0,0, 121,
  10, 0,
  11, 0,
  12, 0,0, 579,

  1, 120,
  2, 120,
  3, 120,
  4, 120,
  5, 120,
  6, 120, 0, 121,

  1, 250,
  2, 250,
  3, 250,
  4, 250,
  5, 250,
  6, 250, 0, 251
};
//Mexican Hat Dance
const int pattern4[] PROGMEM = {
  //  Di-di di-dee-dee-di-dee,
  1, 120, 0, 121,
  1, 120, 0, 121,
  2, 250, 0, 251,
  3, 250, 0, 251,
  2, 250, 0, 251,
  3, 250, 0, 251,
  2, 250, 0, 251,
  1, 120, 0, 121,
  4, 250, 0, 251,
  3, 500, 0, 1010,
  //  Di-di di-dee-dee-di-doo,
  3, 120, 0, 121,
  3, 120, 0, 121,
  1, 250, 0, 251,
  2, 250, 0, 251,
  1, 250, 0, 251,
  2, 250, 0, 251,
  1, 250, 0, 251,
  3, 120, 0, 121,
  1, 250, 0, 251,
  4, 500, 0, 1010,
  //  Di-di di-dee-dee-di-dee,
  2, 120, 0, 121,
  2, 120, 0, 121,
  3, 250, 0, 251,
  1, 250, 0, 251,
  3, 250, 0, 251,
  1, 250, 0, 251,
  3, 250, 0, 251,
  2, 120, 0, 121,
  6, 250, 0, 251,
  1, 500, 0, 501,
  //  Dee-di-dee-dee di dee-
  1, 250, 0, 251,
  1, 120, 0, 121,
  2, 250, 0, 251,
  2, 120, 0, 121,
  3, 250, 0, 251,
  3, 250, 0, 251,
  3, 120, 0, 121,
  2, 250, 0, 251,
  1, 500, 0, 1010,
  //pause
  3, 250, 0, 251,
  //O-LE!
  1, 800,
  2, 800,
  3, 800,
};
//Wipe Out - this one is terrible for some reason
const int pattern5[] PROGMEM = {
  0, 100,
  2, 120, 0, 121,
  3, 250, 0, 251,
  3, 120, 0, 221, //pause

  1, 250, 0, 251,
  2, 250, 0, 251,
  3, 250, 0, 251,

  4, 250, 0, 251,
  4, 120, 0, 121,
  3, 120, 0, 121,
  1, 250, 0, 251,
  1, 120, 0, 221, //pause

  2, 250, 0, 251,
  2, 250, 0, 251,
  3, 250, 0, 251,

  1, 250, 0, 251,
  5, 250, 0, 251,
  5, 120, 0, 121,

  6, 120, 0, 121,
  4, 250, 0, 251,
  4, 120, 0, 221, //pause

  5, 250, 0, 251,
  6, 250, 0, 251,
  4, 250, 0, 251,

  2, 250, 0, 251,
  2, 120, 0, 121,
  4, 120, 0, 121,

  5, 250, 0, 251,
  5, 250, 0, 351, //pause

  6, 250, 0, 251,
  4, 250, 0, 251,
  5, 250, 0, 251,
  3, 250, 0, 251,
  3, 120, 0, 121,

  1, 120, 0, 121,
  2, 250, 0, 251,
  2, 120, 0, 221, //pause

  3, 250, 0, 251,
  3, 250, 0, 251,
  1, 250, 0, 251,
  5, 250, 0, 251,
  5, 120, 0, 121,
  5, 120, 0, 121,
  5, 120, 0, 121,

  1, 250,
  2, 250,
  3, 250,
  4, 250,
  5, 250,
  6, 250, 0, 251,

  1, 250,
  2, 250,
  3, 250,
  4, 250,
  5, 250,
  6, 250, 0, 251,

  1, 500,
  2, 500,
  3, 500,
  4, 500,
  5, 500,
  6, 500, 0, 1500,
  //RANDOM values
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
//personal jesus
const int pattern6[] PROGMEM = {
  1, 120, 0, 121,
  2, 120, 0, 121,
  3, 120, 0, 121,
  4, 250, 0, 251,
  5, 85, 0, 86,

  10, 0,
  11, 0,
  12, 0,
  5, 34, 0, 35,
  
  6, 120, 0, 121,
  1, 250, 0, 251,
  2, 120, 0, 121,
  3, 120, 0, 121,

  1, 500,
  2, 500,
  3, 500,
  4, 500,
  5, 500,
  6, 500, 0, 1500,

  1, 120, 0, 121,
  2, 120, 0, 121,
  3, 120, 0, 121,
  4, 250, 0, 251,
  5, 85, 0, 86,

  10, 0,
  11, 0,
  12, 0,
  5, 34, 0, 35,
  
  6, 120, 0, 121,
  1, 250, 0, 251,
  2, 120, 0, 121,
  3, 120, 0, 121,

  1, 500,
  2, 500,
  3, 500,
  4, 500,
  5, 500,
  6, 500, 0, 1500,

  1, 500, 0, 501,
  5, 120, 0, 121,
  3, 120, 0, 121,
  4, 120, 0, 121,
  2, 250, 0, 251,
  6, 120, 0, 121,
  1, 500, 0, 501,
  5, 250, 0, 251,
  6, 301, 0, 302,
  10, 0,
  11, 0,
  12, 0,
  6, 197, 0, 198,
  6, 500, 0, 501,

  4, 600,
  5, 600,
  6, 600
};
// Wedding March
const int pattern7[] PROGMEM = {
  10, 0,
  0, 700,
  4, 600, 0, 800, //here
  1, 210, 0, 310, //comes
  1, 350, 0, 550, //the
  1, 900, 0, 1000, //briiide
  11, 0, 0, 700, //briiide
  
  5, 600, 0, 800, //all
  1, 210, 0, 310, //dressed
  2, 350, 0, 550, //in
  1, 900, 0, 1000, //whiite
  12, 0, 0, 700, //whiite

  6, 600, 0, 800,
  1, 210, 0, 310,
  2, 350, 0, 550,

  3, 600, 0, 800,
  2, 210, 0, 310,
  1, 350, 0, 550,
  
  1, 99, 0, 100,
  12, 0,
  1, 99, 0, 100,
  1, 400, 0, 600,
  6, 210, 0, 310,
  1, 310, 0, 410,
  1, 1100, 0, 1210,
};
const int * listOfPatterns[] = {
  pattern0,
  pattern1,
  pattern2,
  pattern3,
  pattern4,
  pattern5,
  pattern6,
  pattern7
};
const int patternLengths[] = {
  sizeof(pattern0) / sizeof(int), 
  sizeof(pattern1) / sizeof(int),
  sizeof(pattern2) / sizeof(int),
  sizeof(pattern3) / sizeof(int),
  sizeof(pattern4) / sizeof(int),
  sizeof(pattern5) / sizeof(int),
  sizeof(pattern6) / sizeof(int),
  sizeof(pattern7) / sizeof(int)
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
    playPattern();
  }
}
void playPattern() {
      const int * pattern = listOfPatterns[whichPattern];
      int patternlength = patternLengths[whichPattern];
      
      int poofer = pgm_read_word(pattern + pattern_position); // use PROGMEM to read the number of poofer being selected
      unsigned int duration = pgm_read_word(pattern + (pattern_position + 1)); 
      
      if (poofer == 0) { // if the poofer is zero, create a musical rest or delay
      if (delayStarted == false) {
        pattern_elapsed = 0; //we're just starting this beat, so no time has passed
        delayStarted = true;
      } else if (pattern_elapsed > duration) {
          delayStarted = false;
          pattern_position = pattern_position + 2; //move on to the next poofer in the array
          if (pattern_position >= patternlength) {
            whichPattern = 100;
          } else {
            //do nothing - this is the musical rest or beat
          }
        }
      } else if ((poofer >= 1) && (poofer < 10)) { // if the poofer isn't zero, fire the poofer number
      poofer_on(poofer, duration);
      pattern_position = pattern_position + 2;
        if (pattern_position >= patternlength) {
          whichPattern = 100;
        }
      } else if (poofer == 10) { //sends the value to the led controller
      Serial1.write(10);
      pattern_position = pattern_position + 2;
        if (pattern_position >= patternlength) {
          whichPattern = 100;
        }
      } else if (poofer == 11) {
      Serial1.write(11);
      pattern_position = pattern_position + 2;
        if (pattern_position >= patternlength) {
          whichPattern = 100;
        }
      } else if (poofer == 12) {
      Serial1.write(12);
      pattern_position = pattern_position + 2;
        if (pattern_position >= patternlength) {
          whichPattern = 100;
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
  randomSeed(analogRead(0)); //get a random number to select the function we want
}

void loop() {
  randomNumber = random(6);

  btn1.update();
  btn2.update();
  btn3.update();

  poofLittle1.Update();  // shuts poofers off if they've been on too long
  poofLittle2.Update();
  poofLittle3.Update();
  poofBig1.Update();
  poofBig2.Update();
  poofBig3.Update();

  update_pattern();

  if (Serial1.available())
  { //read values from the main controller to tell which button has been pressed
    buttonValue = Serial1.read();
    //a is b1
    if (buttonValue == 'a')
    {
      Serial1.write('a');
      poofLittle1.On(4000);
    }
    else if (buttonValue == 'A')
    {
      Serial1.write('A');
      poofLittle1.Off();
    }//c = b2
    else if (buttonValue == 'c')
    {
      Serial1.write('c');
      poofLittle2.On(4000);
    }
    else if (buttonValue == 'C')
    {
      Serial1.write('C');
      poofLittle2.Off();
    }//f is b3
    else if (buttonValue == 'f')
    {
      Serial1.write('f');
      poofLittle3.On(4000);
    } else if (buttonValue == 'F')
    {
      Serial1.write('F');
      poofLittle3.Off();
    }//button b4
    else if (buttonValue == 'd')
    {
      Serial1.write('d');
      poofBig1.On(4000);
    }
    else if (buttonValue == 'D')
    {
      Serial1.write('D');
      poofBig1.Off();
    }
    else if (buttonValue == 'e')
    { //e is b5
      Serial1.write('e');
      poofBig2.On(4000);
    }
    else if (buttonValue == 'E')
    {
      Serial1.write('E');
      poofBig2.Off();
    }
    //b is btn6
    else if (buttonValue == 'b')
    {
      Serial1.write('b');
      poofBig3.On(4000);
    } else if (buttonValue == 'B')
    {
      Serial1.write('B');
      poofBig3.Off();
    }

    //all little ones on
    else if (buttonValue == 'g')
    {
      Serial1.write('g');
      poofLittle1.On(4000);
      poofLittle2.On(4000);
      poofLittle3.On(4000);
    }
    else if  (buttonValue == 'G')
    {
      Serial1.write('G');
      poofLittle1.Off();
      poofLittle2.Off();
      poofLittle3.Off();
    }//all big ones on
    else if (buttonValue == 'h')
    {
      Serial1.write('h');
      poofBig1.On(4000);
      poofBig2.On(4000);
      poofBig3.On(4000);
    }
    else if  (buttonValue == 'H')
    {
      Serial1.write('H');
      poofBig1.Off();
      poofBig2.Off();
      poofBig3.Off();
    }
    //j is x
    else if (buttonValue == 'j')
    {
      Serial1.write('j');
    }
    else if (buttonValue == 'J')
    {
      Serial1.write('J');
    }
    // i is j1
    else if (buttonValue == 'i')
    {
      Serial1.write('i');
      poofLittle1.On(4000);
      poofBig1.On(4000);
    }
    else if (buttonValue == 'I')
    {
      Serial1.write('I');
      poofLittle1.Off();
      poofBig1.Off();
    }
    // l is j2
    else if (buttonValue == 'l')
    {
      Serial1.write('l');
      poofLittle2.On(4000);
      poofBig2.On(4000);
    }
    else if (buttonValue == 'L')
    {
      Serial1.write('L');
      poofLittle2.Off();
      poofBig2.Off();
    }
    // k is j3
    else if (buttonValue == 'k')
    {
      Serial1.write('k');
      poofLittle3.On(4000);
      poofBig3.On(4000);
    }
    else if (buttonValue == 'K')
    {
      Serial1.write('K');
      poofLittle3.Off();
      poofBig3.Off();
    }
  }

  //magic lamp buttons
  if (btn1.fallingEdge())
  {
    Serial.println(randomNumber); //random patters on #1 & #2
    start_pattern(randomNumber);
    Serial.println("btn 1 pressed");
  }
  //pattern buttons
  if (btn2.fallingEdge())
  {
    Serial.println(randomNumber);
    start_pattern(randomNumber);
    Serial.println("btn 2 pressed");
  }
  //pattern buttons
  if (btn3.fallingEdge()) //wedding march on #3
  {
    start_pattern(7);
    Serial.println("btn 3 pressed");
  }
}

