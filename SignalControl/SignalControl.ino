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
Bounce btn_j2 = Bounce(17, 10);  
Bounce btn_j3 = Bounce(18, 10);  
Bounce btn_j1 = Bounce(19, 10);  
Bounce btn_x = Bounce(20, 10); 


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
    btn_x.update();
    btn_j1.update();
    btn_j2.update();
    btn_j3.update();

    if (btn_b1.fallingEdge()) {
      Serial1.write("a"); 
      Serial.println("btn_b1 pressed");
      ledTime = 0;
    }
    if (btn_b1.risingEdge()) {
      Serial1.write("A"); 
      Serial.println("btn_b1 released");
    }
    if (btn_b2.fallingEdge()) {
      Serial1.write("b");    
      Serial.println("btn_b2 pressed");
      ledTime = 0;
    }
    if (btn_b2.risingEdge()) {
      Serial1.write("B"); 
      Serial.println("btn_b2 released");
    }
    
    if (btn_b3.fallingEdge()) {
      Serial1.write("c"); 
      Serial.println("btn_b3 pressed");
      ledTime = 0;
    }
    if (btn_b3.risingEdge()) {
      Serial1.write("C"); 
      Serial.println("btn_b3 released");
    }
    
    if (btn_bk1.fallingEdge()) {
      Serial1.write("d"); 
      Serial.println("btn_bk1 pressed");
      ledTime = 0;
    }
    if (btn_bk1.risingEdge()) {
      Serial1.write("D"); 
      Serial.println("btn_bk1 released");
    }
    
    if (btn_bk2.fallingEdge()) {
      Serial1.write("e"); 
      Serial.println("btn_bk2 pressed");
      ledTime = 0;
    }
    if (btn_bk2.risingEdge()) {
      Serial1.write("E"); 
      Serial.println("btn_bk2_released");
    }
    
    if (btn_bk3.fallingEdge()) {
      Serial1.write("f"); 
      Serial.println("btn_bk3 pressed");
      ledTime = 0;
    }
    if (btn_bk3.risingEdge()) {
      Serial1.write("F"); 
      Serial.println("btn_bk3 released");
    }


    
    if (btn_y.fallingEdge()) {
      Serial1.write("g"); 
      Serial.println("btn_y pressed");
      ledTime = 0;
    }
    if (btn_y.risingEdge()) {
      Serial1.write("G"); 
      Serial.write("btn_y released");
    }
    if (btn_r.fallingEdge()) {
      Serial1.write("h");
      Serial.println("btn_r pressed");
      ledTime = 0;
    }
    if (btn_r.risingEdge()) {
      Serial1.write("H"); 
      Serial.println("btn_r released");
    }
    if (btn_x.fallingEdge()) {
      Serial1.write("i");      
      Serial.println("btn_x pressed");
      ledTime = 0;
    }
    if (btn_x.risingEdge()) {
      Serial1.write("I"); 
      Serial.println("btn_x released");
    }
    if (btn_j1.fallingEdge()) {
      Serial1.write("j");  
      Serial.println("btn_j1 pressed");
      ledTime = 0;  
     }
    if (btn_j1.risingEdge()) {
      Serial1.write("J");
      Serial.println("j1 released");
    }
    if (btn_j2.fallingEdge()) {
      Serial1.write("k");   
      Serial.println("btn_j2 pressed"); 
      ledTime = 0;
    }
    if (btn_j2.risingEdge()) {
      Serial1.write("K"); 
      Serial.println("btn_j2 released");
    }
    if (btn_j3.fallingEdge()) {
      Serial1.write("l");    
      Serial.println("btn_j3 pressed");
      ledTime = 0;
    }
    if (btn_j3.risingEdge()) {
      Serial1.write("L"); 
      Serial.println("btn_j3 released");
    }

    if (ledTime < 100) {
      digitalWrite(11, HIGH);
    } else {
      digitalWrite(11, LOW);
    }
}
