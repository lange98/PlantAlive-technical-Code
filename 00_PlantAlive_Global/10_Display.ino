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
