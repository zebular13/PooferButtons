//   //all little ones on
//    else if (buttonValue == 'g')
//    {
//      poofLittle1.On(4000);
//      poofLittle2.On(4000);
//      poofLittle3.On(4000);
//    }
//    else if  (buttonValue == 'G')
//    {
//      poofLittle1.Off();
//      poofLittle2.Off();
//      poofLittle3.Off();
//    }//all big ones on
//    else if (buttonValue == 'h')
//    {
//      poofBig1.On(4000);
//      poofBig2.On(4000);
//      poofBig3.On(4000);
//    }
//    else if  (buttonValue == 'H')
//    {
//      poofBig1.Off();
//      poofBig2.Off();
//      poofBig3.Off();
//    }
//    //j is x
//    else if (buttonValue == 'j')
//    {
//      
//    }
//    else if (buttonValue == 'J')
//    {
//      
//    }
//    // i is j1
//    else if (buttonValue == 'i')
//    {
//      poofLittle1.On(4000);
//      poofBig1.On(4000);
//    }
//    else if (buttonValue == 'I')
//    {
//      poofLittle1.Off();
//      poofBig1.Off();
//    }
//    // l is j2
//    else if (buttonValue == 'l')
//    {
//      poofLittle2.On(4000);
//      poofBig2.On(4000);
//    }
//    else if (buttonValue == 'L')
//    {
//      poofLittle2.Off();
//      poofBig2.Off();
//    }
//    // k is j3
//    else if (buttonValue == 'k')
//    {
//      poofLittle3.On(4000);
//      poofBig3.On(4000);
//    }
//    else if (buttonValue == 'K')
//    {
//      poofLittle3.Off();
//      poofBig3.Off();
//    }
//  }
}
  
void wipe(int color, int wait, int step, byte direction, int duration) {
  if (direction == 0) { //0 makes the direction go forward, or up the strip // any other value for direction is reverse
    for (int i = 0; i < ledsPerStrip; i + step) {
      leds.setPixel(i, color);
      leds.setPixel(i + ledsPerStrip, color);
      leds.setPixel(i + (ledsPerStrip * 2), color);
      while (elapsed_time < 40) ; //wait: 40ms = 25 Hz frame rate
      elapsed_time -= 40;
      leds.show();
    }
  } else {
    for (int i = ledsPerStrip; i > 0; i = i - step) {
      leds.setPixel(i, color);
      leds.setPixel(i + ledsPerStrip, color);
      leds.setPixel(i + (ledsPerStrip * 2), color);
      while (elapsed_time < 40) ; 
      elapsed_time -= 40;
      leds.show();
    }
  }
}
void chaser() {
  
}


// phaseShift is the shift between each row. phaseShift=0
// causes all rows to show the same colors moving together.
// phaseShift=180 causes each row to be the opposite colors
// as the previous.
//
// cycleTime is the number of milliseconds to shift through
// the entire 360 degrees of the color wheel:
// Red -> Orange -> Yellow -> Green -> Blue -> Violet -> Red
//
void rainbow(int phaseShift, int cycleTime)
{
  int color, x, y, offset, wait;
  int white = makeColor(0, 0, 100);
  
  wait = cycleTime * 1000 / ledsPerStrip;
  for (color=0; color < 180; color++) {
    digitalWrite(1, HIGH);
    for (x=0; x < ledsPerStrip; x++) {
      for (y=0; y < 8; y++) {
        int index = (color + x + y*phaseShift/2) % 180;
        //leds.setPixel(x + y*ledsPerStrip, rainbowColors[index]);
        leds.setPixel(x + y*ledsPerStrip, x+y*256); //gives you a two color gradient across the matrix
        }
      }
    leds.show();
    digitalWrite(1, LOW);
    delayMicroseconds(wait);
  }
}

