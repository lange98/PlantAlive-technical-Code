//***********************************************All Interrupt Service Routines****************************************

void IRAM_ATTR isrBack() {
  setButton("back");
}

void IRAM_ATTR isrMinus() {
  setButton("minus");
}

void IRAM_ATTR isrPlus() {
  setButton("plus");
}

void IRAM_ATTR isrEnter() {
  setButton("enter");
}
