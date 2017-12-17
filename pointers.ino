int poofer = pgm_read_word(pattern + pattern_position); // use PROGMEM to read the number of poofer being selected
unsigned int duration = pgm_read_word(pattern + (pattern_position + 1)); 
int upcomingduration = 0;
int last_position;
//read through the upcoming measures, and if there is a burst seven measures from now, start the LEDs. R

//once the current duration plus the next durations equal 700
for(pattern_position = 0; pattern_position <= patternLength; pattern_position++) {
    
    upcomingduration += duration;
    upcomingpoofer += poofer;

    if (pattern_positon(upcomingduration >= 700) {
        int remainderTime = (upcomingduration - 700)
        last_position = pattern_position; //figure out what the pattern position is 700 millis from now
        //get the poofers that are 700 or more milliseconds ahead
        // you can tell if there is a burst because several are fired with no zeros in between. 
        //check to see if there is a burst coming up 700 millis from now...
        if (pgm_read_word(pattern + (pattern_position + 1)) != 0) && (pgm_read_word(pattern + (pattern_position + 3)) != 0) {
            //wait the remainderTime, then send the signal //is it possible for me to split note apart to do this?

            Serial1.write(12);
            
            //then start at the beginning or most recent point and play the next part of the pattern
            playPattern(poofer, duration, patternlength);
        } else {
            //just play the next part of the patter
            playPattern(poofer, duration, patternlength);
        }
    
    }
}

void playPattern(int poofer, int duration, int patternlength) {  
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
      }