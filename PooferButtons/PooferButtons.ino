//Code for Teensy 2.0 that connects to button box
#include <Bounce.h> 

Bounce button1 = Bounce(1, 10);  // 10 = 10 ms debounce time
Bounce button2 = Bounce(2, 10);  // which is appropriate for
Bounce button3 = Bounce(3, 10);  // most mechanical pushbuttons
Bounce button4 = Bounce(4, 10);  // most mechanical pushbuttons

int out1 = 17;
int out2 = 18;
int out3 = 19;

void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial1.begin(9600);
  //declare buttons
  pinMode(1, INPUT_PULLUP);
  pinMode(2, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);
  pinMode(4, INPUT_PULLUP);
  //declare inputs
  pinMode(16, OUTPUT);
  pinMode(out1, OUTPUT);
  pinMode(out2, OUTPUT);
  pinMode(out3, OUTPUT);

  digitalWrite(16, HIGH);
}


void loop() {
    // Update all the buttons.  There should not be any long
    // delays in loop(), so this runs repetitively at a rate
    // faster than the buttons could be pressed and released
    button1.update();
    button2.update();
    button3.update();
    button4.update();
  
  if (button1.fallingEdge()) {
  Serial1.write(1); 
    shaveAndHaircut();
  }

  if (button2.fallingEdge()) {
  Serial1.write(2); 
    fireDance();
  }
  
  if (button3.fallingEdge()) {
  Serial1.write(3); 
    wheelOfFire();
  }
  
  if (button4.fallingEdge()) {
  Serial1.write(4); 
    allOfThem();
  }
}

//pulse - 0.13 SECONDS per round
void pulse(int times, int PIN) {
  for (int i = 0; i < times; i++) {
    digitalWrite(PIN, HIGH);
    delay(100);
    digitalWrite(PIN, LOW);
    delay(60);
  }
  delay(200);
}

//===THE PROGRAMS
//pulsing circles of increasing speed - total time 1185 millis
void wheelOfFire() {
    pulse(6, 19);
    pulse(5, 18);
    pulse(4, 17);
    pulse(3, 19);
    pulse(2, 18);
    pulse(1, 17);
}
// firedance song
void fireDance() {
  for(i=0;i<2;i++){ //loops twice - each loop is 2920 millis
  digitalWrite(out1, HIGH);
  delay(200);
  digitalWrite(out1, LOW);
  delay(150);
  digitalWrite(out1, HIGH);
  delay(200);
  digitalWrite(out1, LOW);
  delay(150);

  digitalWrite(out2, HIGH);
  delay(200);
  digitalWrite(out2, LOW);
  delay(150);
  digitalWrite(out2, HIGH);
  delay(200);
  digitalWrite(out2, LOW);
  delay(150);

  digitalWrite(out1, HIGH);
  delay(200);
  digitalWrite(out1, LOW);
  delay(150);
  digitalWrite(out1, HIGH);
  delay(200);
  digitalWrite(out1, LOW);
  delay(100);

  digitalWrite(out1, HIGH);
  delay(100);
  digitalWrite(out1, LOW);
  delay(20);

  digitalWrite(out2, HIGH);
  delay(200);
  digitalWrite(out2, LOW);
  delay(150);
  digitalWrite(out2, HIGH);
  delay(200);
  digitalWrite(out2, LOW);
  delay(150);
  }
}

//shave and a haircut
void shaveAndHaircut() {
  digitalWrite(out1, HIGH);
  delay(100);
  digitalWrite(out1, LOW);
  delay(150);
  digitalWrite(out1, HIGH);
  delay(100);
  digitalWrite(out1, LOW);
  delay(50);
  digitalWrite(out1, HIGH);
  delay(100);
  digitalWrite(out1, LOW);
  delay(50);
  digitalWrite(out2, HIGH);
  delay(100);
  digitalWrite(out2, LOW);
  delay(300);
  digitalWrite(out1, HIGH);
  delay(100);
  digitalWrite(out1, LOW);
  delay(600);
  digitalWrite(out2, HIGH);
  delay(100);
  digitalWrite(out2, LOW);
  delay(200);
  digitalWrite(out2, HIGH);
  delay(80);
  digitalWrite(out2, LOW);
  delay(200);
}
//ALL OF THEM!!!!!
void allOfThem() { millis - 800
  digitalWrite(out2, HIGH);
  digitalWrite(out1, HIGH);
  digitalWrite(out2, HIGH);
  delay(800);
  digitalWrite(out1, LOW);
  digitalWrite(out2, LOW);
  digitalWrite(out2, LOW);
}
