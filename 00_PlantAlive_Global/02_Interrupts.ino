//***********************************************All Interrupt Service Routines****************************************

void IRAM_ATTR isr1() {
  debounce(1);
}

void IRAM_ATTR isr2() {
  debounce(2);
}

void IRAM_ATTR isr3() {
  debounce(3);
}

void IRAM_ATTR isr4() {
  debounce(4);
}
