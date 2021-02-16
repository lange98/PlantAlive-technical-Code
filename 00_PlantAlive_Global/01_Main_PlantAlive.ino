//***********************************************All logical control code****************************************

void setup(void) { 
  setupDisplay();
  setupButtons();
  setupUltrasonic();

  //bild up wifi communication
  // set soilMoistureLimit
  soilMoistureLimit = 50;
  soilMoistureTemp = soilMoistureLimit;

  
  Serial.begin(115200); // For debug
  updateTime = millis(); // Next update time
}
  
void loop() {
  if (updateTime <= millis()) {
    updateTime = millis() + LOOP_PERIOD;

    calcMoisture();
    calcDistance();
    calcTemperature();
    updateDisplay(false, "");
  }

  if (debounceTime <= millis()){
    doButtons(); // display control via buttons
  }
}
