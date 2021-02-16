//***********************************************All code related to button functionality****************************************

//Functions
void setupButtons(){
  pinMode(btnPinBack, INPUT_PULLUP);
  pinMode(btnPinMinus, INPUT_PULLUP);
  pinMode(btnPinPlus, INPUT_PULLUP);
  pinMode(btnPinEnter, INPUT_PULLUP);
  attachInterrupt(btnPinBack, isrBack, HIGH);
  attachInterrupt(btnPinMinus, isrMinus, HIGH);
  attachInterrupt(btnPinPlus, isrPlus, HIGH);
  attachInterrupt(btnPinEnter, isrEnter, HIGH);
    /*  attachInterrupt(GPIOPin, ISR, Mode);
     *   GPIOPin – Sets the GPIO pin as an interrupt pin, which tells the ESP32 which pin to monitor.
     *   ISR – Is the name of the function that will be called every time the interrupt is triggered.
     *   Mode – Defines when the interrupt should be triggered. Five constants are predefined as valid
     *   
     *   Modes: 
     *    LOW Triggers interrupt whenever the pin is LOW
     *    HIGH  Triggers interrupt whenever the pin is HIGH
     *    CHANGE  Triggers interrupt whenever the pin changes value, from HIGH to LOW or LOW to HIGH
     *    FALLING Triggers interrupt when the pin goes from HIGH to LOW
     *    RISING  Triggers interrupt when the pin goes from LOW to HIGH
     */
  btnBack = false;
  btnMinus = false;
  btnPlus = false;
  btnEnter = false;
  debounceTime = millis();
}

void setButton(String btn){
  if (btn == "back"){
    btnBack = true;
  }
  else if (btn == "minus"){
    btnMinus = true;
  }
  else if (btn == "plus"){
    btnPlus = true;
  }
  else if (btn == "enter"){
    btnEnter = true;
  }
  //Serial.println("Button set");
  debounceTime = millis() + debouncePeriod; // wait at least <debouncePeroid> ms from now on
}

/*
void unsetButton(int btn){
  switch(btn){
    case 0: btnBack = false;break;
    case 1: btnMinus = false;break;
    case 2: btnPlus = false;break;
    case 3: btnEnter = false;break;
  }
}*/

void unsetAllButtons(){
  btnBack = false;
  btnMinus = false;
  btnPlus = false;
  btnEnter = false;
  //Serial.println("All Buttons unset");
}

bool isButtonPressed(){
    return(btnBack || btnMinus || btnPlus || btnEnter); // return true if any button is pressed
}

void doButtons(){ //display control via buttons
  // check if any button has been pressed
  if (!isButtonPressed()){
    return;
  }
  
  String btn;
  if (btnEnter){
    btn = "enter";
  }
  else if(btnPlus){
    btn = "plus";
  }
  else if(btnMinus){
    btn = "minus";
  }
  else if(btnBack){
    btn = "back";
  }
  Serial.println("button "+btn+" pressed!");

  updateDisplay(true, btn);
  unsetAllButtons();
}
