//***********************************************All logical control code****************************************

void setup(void) { 
  setupDisplay();
  setupButtons();
  setupUltrasonic();
  
  Serial.begin(115200); // For debug
  updateTime = millis(); // Next update time
}
  
void loop() {

  if (updateTime <= millis()) {
    updateTime = millis() + LOOP_PERIOD;

    soilmoisturepercent = calcMoisture();
    distance = calcDistance();
    temperatureC = calcTemperature();
    updateDisplay(soilmoisturepercent, distance, temperatureC);
  }
  
}
