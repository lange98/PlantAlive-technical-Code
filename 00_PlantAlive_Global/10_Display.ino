//***********************************************All code related to display functionality****************************************

//Functions
void setupDisplay(){
  tft.init();
  tft.setRotation(0);
  tft.fillScreen(TFT_BLACK);
  tft.setFreeFont(CF_OL24);

  currentState = "init";
  currentState = stateMachine("");
}

void updateDisplay (bool isBtnPressed, String btn){
  //Serial.println(currentState);
  /*
   * main function and link for display control
   * checks is button has been pressed --> statemachine
   * if not and not in editing mode --> update Values in defaultDisplay
   * if in editing mode --> do nothing
   */
  if (!isBtnPressed){
    if (currentState == "default"){
      displayDefault(); //show default display
    }
    return;
  }
  currentState = stateMachine(btn);
}

void changeState(){
  tft.fillScreen(TFT_BLACK);
}

void displayDefault(){

  //create display layout
  tft.setTextColor(TFT_WHITE, TFT_BLACK); // white font, black background
  tft.drawString("Moisture: ", 10, 40, 4);//parameters: strint to print, x-coord, y-coord, font size
  tft.drawString("M. Limit:", 10, 80, 4);
  tft.drawString("M. Air:", 10, 120, 4);
  tft.drawString("Temp.:", 10, 160, 4);
  tft.drawString("Waterlevel:", 10, 200, 4);
  
  /* 
   *  tft.setTextPadding( tft.textWidth("xxxx", 4) );
   *  Set the padding to the maximum width that the digits could occupy in font 4. 
   *  This ensures small numbers obliterate large ones on the screen
   */ 
  
  //moisture
  tft.setTextPadding( tft.textWidth("100%", 4) );//setzt einen Raum der länge und Größe des angegebenen Strings (hier: Schriftgröße 4) --> zum Überschreiben falls noch alter Werte drin stehen
  tft.setTextColor(TFT_BLACK, TFT_WHITE);// for variable values (black font, white background)  
  tft.drawString(String(soilmoisturePercent)+"%", x, 40, 4);
  //moisture limit
  tft.setTextPadding( tft.textWidth("100%", 4) );
  tft.drawString(String(soilMoistureLimit), x, 80, 4);
  //unnötig
  tft.drawString("0%", x, 120, 4);
  
  //temperature
  tft.setTextPadding( tft.textWidth("88.88C", 4) );
  tft.drawString(String(temperatureC)+"°C", x, 160, 4);
  //waterlevel
  tft.setTextPadding( tft.textWidth("88888ml", 4) );
  tft.drawString(String(distance)+"ml", x+20, 200, 4);
  
  // Reset text padding to 0 otherwise all future rendered strings will use it!
  tft.setTextPadding(0);
}

void displayMenu(){
  //create display layout
  tft.setTextColor(TFT_WHITE, TFT_BLACK);// for variable values (black font, white background)
  tft.drawString("Menu", 10, 20, 4);
  tft.setTextColor(TFT_BLACK, TFT_WHITE);
  tft.drawString("change Moisture", 10, y-20, 4);
  //Buttons
  tft.setTextPadding( tft.textWidth("8888", 4) );
  tft.setTextColor(TFT_BLACK, TFT_RED);// for variable values (black font, white background)
  tft.drawString("B", 0, 200, 4);
  tft.setTextColor(TFT_BLACK, TFT_WHITE);
  tft.drawString("-", 60, 200, 4);
  tft.drawString("+", 120, 200, 4);
  tft.setTextColor(TFT_BLACK, TFT_GREEN);// for variable values (black font, white background)
  tft.drawString("E", 180, 200, 4);
  tft.setTextPadding(0);
}

void displaySetMoisture(){
  //create display layout
  tft.setTextColor(TFT_WHITE, TFT_BLACK);
  tft.drawString("change Moisture", 5, 20, 4);
  tft.setTextPadding( tft.textWidth("100%", 6) );
  tft.drawString(String(soilMoistureTemp), 10, 80, 4);
  //Buttons
  tft.setTextPadding( tft.textWidth("8888", 4) );
  tft.setTextColor(TFT_BLACK, TFT_RED);// for variable values (black font, white background)
  tft.drawString("B", 0, 200, 4);
  tft.setTextColor(TFT_BLACK, TFT_WHITE);
  tft.drawString("-", 60, 200, 4);
  tft.drawString("+", 120, 200, 4);
  tft.setTextColor(TFT_BLACK, TFT_GREEN);// for variable values (black font, white background)
  tft.drawString("E", 180, 200, 4);
  tft.setTextPadding(0);
}
