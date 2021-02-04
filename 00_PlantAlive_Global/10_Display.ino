//***********************************************All code related to display functionality****************************************

//Functions
void setupDisplay(){
  tft.init();
  tft.setRotation(0);
  tft.setTextColor(TFT_WHITE, TFT_BLACK);
  tft.fillScreen(TFT_BLACK);
  tft.setFreeFont(CF_OL24);
  //create display layout
  tft.drawString("Moisture: ", 10, 40, 4);
  tft.drawString("M. Water:", 10, 80, 4);
  tft.drawString("M. Air:", 10, 120, 4);
  tft.drawString("Temp.:", 10, 160, 4);
  tft.drawString("Waterlevel:", 10, 200, 4);
  tft.setTextColor(TFT_BLACK, TFT_WHITE); // for variable values
}

void setupButtons(){
  pinMode(buttonLeft, INPUT_PULLUP);
  pinMode(buttonMidLeft, INPUT_PULLUP);
  pinMode(buttonMidRight, INPUT_PULLUP);
  pinMode(buttonRight, INPUT_PULLUP);
  attachInterrupt(buttonLeft, isr1, FALLING);
  attachInterrupt(buttonMidLeft, isr2, FALLING);
  attachInterrupt(buttonMidRight, isr3, FALLING);
  attachInterrupt(buttonRight, isr4, FALLING);
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
}


void updateDisplay (int soilmoisturepercent, int distance, float temperatureC){
  //display
  //tft.fillScreen(TFT_BLACK);
  String valMoi = String(soilmoisturepercent);
  String valWat = String(distance);
  String valTemp = String(temperatureC);
  // Set the padding to the maximum width that the digits could occupy in font 4
  // This ensures small numbers obliterate large ones on the screen
  tft.setTextPadding( tft.textWidth("100%", 4) );//setzt einen Raum der länge und Größe des angegebenen Strings (hier: Schriftgröße 4)
  tft.drawString(valMoi+"%", x, 40, 4);
  tft.drawString("100%", x, 80, 4);
  tft.drawString("0%", x, 120, 4);
  tft.drawString(valTemp+"°C", x, 160, 4);
  tft.setTextPadding( tft.textWidth("88888ml", 4) );//setzt einen Raum der länge und Größe des angegebenen Strings (hier: Schriftgröße 4)
  tft.drawString(valWat+"ml", x+20, 200, 4);
  // Reset text padding to 0 otherwise all future rendered strings will use it!
  tft.setTextPadding(0);
}

void button(int btn){
    Serial.println("button"+String(btn)+" pressed!");
}

void debounce(int btn){
  delay(100);
  button(btn);
}
