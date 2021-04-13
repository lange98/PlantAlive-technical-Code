//***********************************************All Interrupt Service Routines****************************************

void IRAM_ATTR isrBack() {
  //Serial.println("Back");
  setButton("back");
}

void IRAM_ATTR isrMinus() {
  //Serial.println("Minus");
  setButton("minus");
}

void IRAM_ATTR isrPlus() {
  //Serial.println("Plus");
  setButton("plus");
}

void IRAM_ATTR isrEnter() {
  //Serial.println("Enter");
  setButton("enter");
}
