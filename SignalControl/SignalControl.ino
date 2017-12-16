//Code for Teensy 2.0 that connects to button box
#include <Bounce.h> 
elapsedMillis ledTime;

Bounce btn_bk2 = Bounce(1, 10);  // 10 = 10 ms debounce time
Bounce btn_b3 = Bounce(2, 10);  
Bounce btn_b1 = Bounce(3, 10);  
Bounce btn_bk1 = Bounce(4, 10);  
Bounce btn_b2 = Bounce(5, 10);  
Bounce btn_bk3 = Bounce(6, 10);  

Bounce btn_r = Bounce(15, 10);  // 10 = 10 ms debounce time
Bounce btn_y = Bounce(16, 10);

// TODO: figure out which is which...
Bounce btn_jup = Bounce(18, 10);
Bounce btn_jdown = Bounce(19, 10);
Bounce btn_jleft = Bounce(17, 10);
Bounce btn_jright = Bounce(20, 10);

// joystick state
uint8_t jstate=0;      // 1=up, 2=down, 4=left, 8=right
uint8_t jpriorstate=0; // state previously send to valve controller
bool jchange=false;    // true when changed but not yet processed
elapsedMillis jmillis; // time since most recent change

// joystick codes
//  m - up
//  n - up-right
//  o - right
//  p - down-right
//  q - down
//  r - down-left
//  s - left
//  t - up-left
//  u - neutral

const char jstate_to_jcode[16] = {
  'u', // 0000 = neutral
  'm', // 0001 = up
  'q', // 0020 = down
  'u', // 0021 = down+up            ILLEGAL
  's', // 0400 = left
  't', // 0401 = left+up
  'r', // 0420 = left+down
  'u', // 0421 = left+down+up       ILLEGAL
  'o', // 8000 = right
  'n', // 8001 = right+up
  'p', // 8020 = right+down
  'u', // 8021 = right+down+up      ILLEGAL
  'u', // 8400 = right+left         ILLEGAL
  'u', // 8401 = right+left+up      ILLEGAL
  'u', // 8420 = right+left+down    ILLEGAL
  'u'  // 8421 = right+left+down+up ILLEGAL
};


void setup() {
  Serial.begin(9600);
  Serial1.begin(9600);

  pinMode(11, OUTPUT);
  
  pinMode(1, INPUT_PULLUP);
  pinMode(2, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);
  pinMode(4, INPUT_PULLUP);
  pinMode(5, INPUT_PULLUP);
  pinMode(6, INPUT_PULLUP);
  
  pinMode(15, INPUT_PULLUP);
  pinMode(16, INPUT_PULLUP);   
  pinMode(17, INPUT_PULLUP);
  pinMode(18, INPUT_PULLUP);   
  pinMode(19, INPUT_PULLUP);
  pinMode(20, INPUT_PULLUP);

}

void loop() {
    btn_b1.update();
    btn_b2.update();
    btn_b3.update();
    btn_bk1.update();
    btn_bk2.update();
    btn_bk3.update();

    btn_y.update();
    btn_r.update();
    btn_jup.update();
    btn_jdown.update();
    btn_jleft.update();
    btn_jright.update();

    if (btn_b1.fallingEdge()) {
      Serial1.write("a"); 
      Serial.println(F("btn_b1 pressed"));
      ledTime = 0;
    }
    if (btn_b1.risingEdge()) {
      Serial1.write("A"); 
      Serial.println(F("btn_b1 released"));
    }
    if (btn_b2.fallingEdge()) {
      Serial1.write("b");    
      Serial.println(F("btn_b2 pressed"));
      ledTime = 0;
    }
    if (btn_b2.risingEdge()) {
      Serial1.write("B"); 
      Serial.println(F("btn_b2 released"));
    }
    
    if (btn_b3.fallingEdge()) {
      Serial1.write("c"); 
      Serial.println(F("btn_b3 pressed"));
      ledTime = 0;
    }
    if (btn_b3.risingEdge()) {
      Serial1.write("C"); 
      Serial.println(F("btn_b3 released"));
    }
    
    if (btn_bk1.fallingEdge()) {
      Serial1.write("d"); 
      Serial.println(F("btn_bk1 pressed"));
      ledTime = 0;
    }
    if (btn_bk1.risingEdge()) {
      Serial1.write("D"); 
      Serial.println(F("btn_bk1 released"));
    }
    
    if (btn_bk2.fallingEdge()) {
      Serial1.write("e"); 
      Serial.println(F("btn_bk2 pressed"));
      ledTime = 0;
    }
    if (btn_bk2.risingEdge()) {
      Serial1.write("E"); 
      Serial.println(F("btn_bk2_released"));
    }
    
    if (btn_bk3.fallingEdge()) {
      Serial1.write("f"); 
      Serial.println(F("btn_bk3 pressed"));
      ledTime = 0;
    }
    if (btn_bk3.risingEdge()) {
      Serial1.write("F"); 
      Serial.println(F("btn_bk3 released"));
    }


    
    if (btn_y.fallingEdge()) {
      Serial1.write("g"); 
      Serial.println(F("btn_y pressed"));
      ledTime = 0;
    }
    if (btn_y.risingEdge()) {
      Serial1.write("G"); 
      Serial.println(F("btn_y released"));
    }
    if (btn_r.fallingEdge()) {
      Serial1.write("h");
      Serial.println(F("btn_r pressed"));
      ledTime = 0;
    }
    if (btn_r.risingEdge()) {
      Serial1.write("H"); 
      Serial.println(F("btn_r released"));
    }

    
    if (btn_jup.fallingEdge()) {  
      jstate |= 1;
      jchange = true;
      jmillis = 0;
      ledTime = 0;
      Serial.println(F("jup pressed"));
    }
    if (btn_jup.risingEdge()) {
      jstate &= ~1;
      jchange = true;
      jmillis = 0;
      ledTime = 0;
      Serial.println(F("jup released"));
    }
    if (btn_jdown.fallingEdge()) {
      jstate |= 2;
      jchange = true;
      jmillis = 0;
      ledTime = 0;
      Serial.println(F("jdown pressed"));
    }
    if (btn_jdown.risingEdge()) {
      jstate &= ~2;
      jchange = true;
      jmillis = 0;
      ledTime = 0;
      Serial.println(F("jdown released"));
    }
    if (btn_jleft.fallingEdge()) {
      jstate |= 4;
      jchange = true;
      jmillis = 0;
      ledTime = 0;
      Serial.println(F("jleft pressed")); 
    }
    if (btn_jleft.risingEdge()) {
      jstate &= ~4;
      jchange = true;
      jmillis = 0;
      ledTime = 0;
      Serial.println(F("jleft released"));
    }
    if (btn_jright.fallingEdge()) {
      jstate |= 8;
      jchange = true;
      jmillis = 0;
      ledTime = 0;   
      Serial.println(F("jright pressed"));
    }
    if (btn_jright.risingEdge()) {
      jstate &= ~8;
      jchange = true;
      jmillis = 0;
      ledTime = 0;
      Serial.println(F("jright released"));
    }

    // handle change in joystick, but only after a waiting period
    // hopefully the wait period is long enough to ignore
    // intermediate positions (brief moment where left or up
    // connects first when actual position is diagonal up+left)
    // but still short enough to feel responsive to the operator
    if (jchange && jmillis > 50) {
      if (jstate != jpriorstate) {
        Serial1.write(jstate_to_jcode[jpriorstate] - 32);
        Serial1.write(jstate_to_jcode[jstate]);
        jpriorstate = jstate;
        Serial.print(F("  joystick position: "));
        Serial.println(jstate_to_jcode[jstate]);
      }
      jchange = false;
    }

    if (ledTime < 100) {
      digitalWrite(11, HIGH);
    } else {
      digitalWrite(11, LOW);
    }
}
