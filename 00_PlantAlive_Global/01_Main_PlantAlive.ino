//***********************************************All logical control code****************************************

void setup(void) { 
  Serial.begin(115200); // For debug
  
  setupDisplay();
  setupButtons();
  setupUltrasonic();


   // set soilMoistureLimit
  soilMoistureLimit = 50;
  soilMoistureTemp = soilMoistureLimit;

  //build up wifi communication
  displayBoot("wifi"); //show "connecting to wifi" on display
  setup_wifi();
  //build up mqtt-server-connection
  setup_MQTT();
  displayBoot("mqtt"); //show "connecting to mqtt" on display
  reconnect();


  bootingDone();
  updateTime = millis(); // Next update time
}
  
void loop() {
  if (updateTime <= millis()) {
    updateTime = millis() + LOOP_PERIOD;

    calcMoisture();
    calcDistance();
    calcTemperature();
    updateDisplay(false, "");

    if (connectedToMQTT){
      cyclicMQTTStuff();
    }

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
