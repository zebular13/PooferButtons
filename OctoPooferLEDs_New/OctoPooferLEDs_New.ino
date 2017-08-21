int buttonValue; //controller input read through serial

void setup() {

}

void loop() {

  if (Serial1.available()) //listen for signals from the controller
  {//read values from the first teensy to tell which button has been pressed
    buttonValue = Serial1.read();
    //a is b1
    if (buttonValue == 'a')
    {
      poofLittle1.On(4000);
    }
    else if (buttonValue == 'A')
    {
      poofLittle1.Off();
    }//c = b2
    else if (buttonValue == 'c')
    {
      poofLittle2.On(4000);
    }
    else if (buttonValue == 'C')
    {
      poofLittle2.Off();
    }//f is b3
    else if (buttonValue == 'f')
    {
      poofLittle3.On(4000);
    } else if (buttonValue == 'F')
    {
      poofLittle3.Off();
    }//button b4
    else if (buttonValue == 'd')
    {
      poofBig1.On(4000);
    }
    else if (buttonValue == 'D')
    {
      poofBig1.Off();
    }
    else if (buttonValue == 'e')
    { //e is b5
      poofBig2.On(4000);
    }
    else if (buttonValue == 'E')
    {
      poofBig2.Off();
    }
    //b is btn6
    else if (buttonValue == 'b')
    {
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
    }
    else if  (buttonValue == 'G')
    {
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
  
}
