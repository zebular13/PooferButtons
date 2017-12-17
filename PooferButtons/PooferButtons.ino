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

int eighthnote = 100;
int quarternote = 200;
int dotquarternote = 300;
int halfnote = 400;
int wholenote = 800;

int eighthrest = 101;
int quarterrest = 201;
int dotquarterrest = 301;
int halfrest = 401;
int wholerest = 801;

//Safety Dance
const int pattern0[] PROGMEM = {
  //safety dance
  10, 0,// 12 equals a vertical led animation, duration is 700
  10, 0,
  1, 200, 0, 350,
  1, 200, 0, 350,

  4, 200, 0, 350,
  4, 200, 0, 280,
  11, 0,
  11, 0, 0, 70,
  1, 200, 0, 350,
  1, 200, 0, 201,
  2, 100, 0, 120,

  4, 200, 0, 350,
  4, 200, 0, 350,

  10, 0,
  10, 0,
  1, 200, 0, 350,
  1, 200, 0, 350,

  4, 200, 0, 350,
  4, 200, 0, 280,
  10, 0,
  10, 0, 0, 70,
  1, 200, 0, 350,
  1, 200, 0, 201,
  2, 100, 0, 120,

  4, 200, 0, 350,
  4, 200, 0, 2350,

  //burst
  1, 100,
  2, 100,
  4, 100,
  5, 100, 101,

  //burst
  1, 80,
  2, 80,
  4, 80,
  5, 80, 0, 81
};

//Ragg Mopp for two poofers 4/4 timing
const int pattern1[] PROGMEM = {
  //ragg! 
  1, 200,
  2, 200,
  4, 200,
  5, 200, 0, 201,
  //mopp!
  1, 200,
  2, 200,
  4, 200,
  5, 190, 0, 201,

  //doodley de
  5, eighthnote, 0, 101,
  5, eighthnote, 0, 101,
  2, 190, 0, 101,
  //daaa
  4, 300, 0, 301,
  //da
  2, 100, 0, 101,
  //da
  5, 100, 0, 101,
  //da
  5, 250, 0, 101,
  
  //doodley de
  5, 100, 0, 101,
  5, 100, 0, 101,
  2, 190, 0, 201,
  //daaa
  4, 300, 0, 301,
  //da
  2, 100, 0, 101,
  //da
  5, 100, 0, 101,
  //da
  5, 250, 0, 301,
  
  //doodley de
  5, 100, 0, 101,
  5, 100, 0, 101,
  2, 190, 0, 201,
  //daaa
  4, 300, 0, 301,
  //da
  2, 100, 0, 101,
  //da
  5, 100, 0, 101,
  //da
  5, 250, 0, 301,
  
  //doodley de
  5, 100, 0, 101,
  5, 0, 101,
  2, 190, 0, 201,
  //daaa
  4, 300, 0, 301,
  //da
  2, 100, 0, 101,
  //da
  5, 100, 0, 101,
  //da
  5, 250, 0, 301,

  //R.-A.-G.-G. - M.-O.-P.-P
  1, 200, 0, 201,
  2, 200, 0, 201,
  1, 200, 0, 201,
  2, 200, 0, 201,
  4, 200, 0, 201,
  5, 200, 0, 201,
  4, 200, 0, 201,
  5, 190, 0, 201,

  //Ragg mopp!  (plus flourish)
  //ragg! 
  1, 200,
  2, 200,
  4, 200,
  5, 200, 0, 201,
  //mopp!
  1, 200,
  2, 200,
  4, 200,
  5, 200, 0, 201
};
//Mexican Hat Dance for 2 poofers 3/3 timing
const int pattern2[] PROGMEM = {
  //  Di-di di-dee-dee-di-dee,
  1, 120, 0, 121,
  1, 120, 0, 121,
  2, 250, 0, 251,
  5, 250, 0, 251,
  2, 250, 0, 251,
  5, 250, 0, 251,
  2, 250, 0, 251,
  1, 120, 0, 121,
  4, 250, 0, 251,
  5, 500, 0, 1010,
  //  Di-di di-dee-dee-di-doo,
  5, 120, 0, 121,
  5, 120, 0, 121,
  1, 250, 0, 251,
  2, 250, 0, 251,
  1, 250, 0, 251,
  2, 250, 0, 251,
  1, 250, 0, 251,
  5, 120, 0, 121,
  1, 250, 0, 251,
  4, 500, 0, 1010,
  //  Di-di di-dee-dee-di-dee,
  2, 120, 0, 121,
  2, 120, 0, 121,
  5, 250, 0, 251,
  1, 250, 0, 251,
  5, 250, 0, 251,
  1, 250, 0, 251,
  5, 250, 0, 251,
  2, 120, 0, 121,
  4, 250, 0, 251,
  1, 500, 0, 501,
  //  Dee-di-dee-dee di dee-
  1, 250, 0, 251,
  1, 120, 0, 121,
  2, 250, 0, 251,
  2, 120, 0, 121,
  5, 250, 0, 251,
  5, 250, 0, 251,
  5, 120, 0, 121,
  2, 250, 0, 251,
  1, 500, 0, 1010,
  //pause
  5, 250, 0, 251,
  //O-LE!
  1, 800,
  2, 800,
  5, 800
};

const int * listOfPatterns[] = {
  pattern0,
  pattern1,
  pattern2
};
const int patternLengths[] = {
  sizeof(pattern0) / sizeof(int),
  sizeof(pattern1) / sizeof(int),
  sizeof(pattern2) / sizeof(int)
};
const int numberOfPatterns = sizeof(listOfPatterns) / sizeof(const int *);
int pattern_position;
elapsedMillis pattern_elapsed;
bool delayStarted;
int whichPattern = 100;

void start_pattern(int num) //the function that gets called by the buttons to start the pattern
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
    if (buttonValue == 'd')
    {
      Serial1.write('d');
      poofLittle1.On(3000);
      Serial.println("black btn 1 pressed. Little poofer 1 turns on.");
    }
    else if (buttonValue == 'D')
    {
      Serial1.write('D');
      poofLittle1.Off();
    }
    else if (buttonValue == 'c')
    {
      Serial1.write('c');
      poofLittle2.On(3000);
      Serial.println("black btn 2 pressed. Little poofer 2 turns on.");
    }
    else if (buttonValue == 'C')
    {
      Serial1.write('C');
      poofLittle2.Off();
    }
    else if (buttonValue == 'f')
    {
      Serial1.write('f');
      poofLittle3.On(3000);
      Serial.println("black btn 3 pressed. Little poofer 3 turns on.");
    } else if (buttonValue == 'F')
    {
      Serial1.write('F');
      poofLittle3.Off();
    }
    else if (buttonValue == 'a')
    {
      Serial1.write('a');
      poofBig1.On(3000);
      Serial.println("blue btn 1 pressed. Big poofer 1 turns on.");
    }
    else if (buttonValue == 'A')
    {
      Serial1.write('A');
      poofBig1.Off();
    }
    else if (buttonValue == 'e')
    { 
      Serial1.write('e');
      poofBig2.On(3000);
      Serial.println("blue btn 2 pressed. Big poofer 2 turns on.");
    }
    else if (buttonValue == 'E')
    {
      Serial1.write('E');
      poofBig2.Off();
    }
    else if (buttonValue == 'b')
    {
      Serial1.write('b');
      poofBig3.On(3000);
      Serial.println("blue btn 3 pressed. Big poofer 3 turns on.");
    }
    else if (buttonValue == 'B')
    {
      Serial1.write('B');
      poofBig3.Off();
    }

    //all little ones on
    else if (buttonValue == 'h')
    {
      Serial1.write('h');
      poofBig1.On(3000);
      poofBig2.On(3000);
      poofBig3.On(3000);
      poofLittle1.On(3000);
      poofLittle2.On(3000);
      poofLittle3.On(3000);
      Serial.println("Red btn pressed. All poofers on.");
    }
    else if  (buttonValue == 'H')
    {
      Serial1.write('H');
      poofBig1.Off();
      poofBig2.Off();
      poofBig3.Off();
      poofLittle1.Off();
      poofLittle2.Off();
      poofLittle3.Off();
    } //all big ones on
    else if (buttonValue == 'g')
    {
      Serial1.write('g');
      poofLittle1.On(3000);
      poofLittle2.On(3000);
      poofLittle3.On(3000);
      Serial.println("Yellow btn pressed. All small poofers on.");
    }
    else if  (buttonValue == 'G')
    {
      Serial1.write('G');
      poofLittle1.Off();
      poofLittle2.Off();
      poofLittle3.Off();
    }

    //Joystick (letters proceed clockwise around joystick)
    //'m' is the top position
    else if (buttonValue == 'm')
    {
      Serial1.write('m');
      poofLittle1.On(3000);
      poofBig1.On(3000);
      Serial.println("Joystick in top position. Big1 and small1 on.");
    }
    else if (buttonValue == 'M')
    {
      Serial1.write('M');
      poofLittle1.Off();
      poofBig1.Off();
    }
    else if (buttonValue == 'n')
    {
      Serial1.write('n');
      poofLittle2.On(3000);
      poofBig2.On(3000);
      poofLittle1.On(3000);
      poofBig1.On(3000);
      Serial.println("Joystick in top right position. Big2, small2, big1, small1 on.");
    }
    else if (buttonValue == 'N')
    {
      Serial1.write('N');
      poofLittle2.Off();
      poofBig2.Off();
      poofLittle1.Off();
      poofBig1.Off();
    }
    else if (buttonValue == 'o')
    {
      Serial1.write('o');
      poofLittle2.On(3000);
      poofBig2.On(3000);
      Serial.println("Joystick in right position. Big2, small2 on.");
    }
    else if (buttonValue == 'O')
    {
      Serial1.write('O');
      poofLittle2.Off();
      poofBig2.Off();
    }

    else if (buttonValue == 'p')
    {
      Serial1.write('p');
      poofLittle1.On(3000);
      poofLittle2.On(3000);
      poofLittle3.On(3000);
      Serial.println("Joystick in lower right position. All little poofers on.");
    }
    else if (buttonValue == 'P')
    {
      Serial1.write('P');
      poofLittle1.Off();
      poofLittle2.Off();
      poofLittle3.Off();
    }

    //bottom position of the joystick
    else if (buttonValue == 'q')
    {
      Serial1.write('q');
      poofLittle2.On(3000);
      poofBig2.On(3000);
      poofLittle3.On(3000);
      poofBig3.On(3000);
      Serial.println("Joystick in bottom position. Big2, small2, big3, small3 on.");
    }
    else if (buttonValue == 'Q')
    {
      Serial1.write('Q');
      poofLittle2.Off();
      poofBig2.Off();
      poofLittle3.Off();
      poofBig3.Off();
    }
    else if (buttonValue == 'r')
    {
      Serial1.write('r');
      poofBig1.On(3000);
      poofBig2.On(3000);
      poofBig3.On(3000);
      Serial.println("Joystick in lower left position. All big poofers on.");
    }
    else if (buttonValue == 'R')
    {
      Serial1.write('R');
      poofBig1.Off();
      poofBig2.Off();
      poofBig3.Off();
    }
    else if (buttonValue == 's')
    {
      Serial1.write('s');
      poofLittle3.On(3000);
      poofBig3.On(3000);
      Serial.println("Joystick in left position. Big3, small3, on.");
    }
    else if (buttonValue == 'S')
    {
      Serial1.write('S');
      poofLittle3.Off();
      poofBig3.Off();
    }
    else if (buttonValue == 't')
    {
      Serial1.write('t');
      poofLittle1.On(3000);
      poofBig1.On(3000);
      poofLittle3.On(3000);
      poofBig3.On(3000);
      Serial.println("Joystick in top left position. Big1, small1, big3, small 3 on.");
    }
    else if (buttonValue == 'T')
    {
      Serial1.write('T');
      poofLittle1.Off();
      poofBig1.Off();
      poofLittle3.Off();
      poofBig3.Off();
    }

    //when the joystick returns to center position it turns them off
    else if (buttonValue == 'u')
    {
      Serial1.write('u');
      poofLittle1.Off();
      poofBig1.Off();
      poofLittle2.Off();
      poofBig2.Off();
      poofLittle3.Off();
      poofBig3.Off();
      Serial.println("Joystick in middle position. All off.");
    }
    //default to off, just in case (might cause problems)
    else
    {
      poofLittle1.Off();
      poofBig1.Off();
      poofLittle2.Off();
      poofBig2.Off();
      poofLittle3.Off();
      poofBig3.Off();
      Serial.println("Joystick in unknown position. All off.");
    }
  }

  //magic lamp buttons
  if (btn1.fallingEdge()) //shave and a haircut
  {
    //    Serial.println(randomNumber);
    //    start_pattern(randomNumber);
    start_pattern(0);
    Serial.println("green btn 1 pressed");
  }
  //pattern buttons
  if (btn2.fallingEdge()) //mexican hat dance
  {
   start_pattern(1);
    Serial.println("red btn 2 pressed");
  }
  //pattern buttons
  if (btn3.fallingEdge()) //ragg mopp
  {
    start_pattern(2);
    Serial.println("yellow btn 3 pressed");
  }
}
