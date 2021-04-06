//***********************************************All logical control code****************************************

void setup(void) { 
  Serial.begin(115200); // For debug
  
  setupDisplay();
  setupButtons();
  setupUltrasonic();


   // set soilMoistureLimit
  soilMoistureLimit = 50;
  soilMoistureTemp = soilMoistureLimit;

  //bild up wifi communication
  setup_wifi();
  setup_MQTT();

  updateTime = millis(); // Next update time
}
  
void loop() {
  if (updateTime <= millis()) {
    updateTime = millis() + LOOP_PERIOD;

    calcMoisture();
    calcDistance();
    calcTemperature();
    updateDisplay(false, "");
    cyclicMQTTStuff();
    //Serial.println(serialNumber);

    if (soilmoisturePercent<soilMoistureLimit){
      //pump
      return;
    }
    if (distance<1000){//irgend ein limit
      //alert
      return;
    }
  }

  if (debounceTime <= millis()){
    doButtons(); // display control via buttons
  }
}
