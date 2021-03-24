//***********************************************All logical control code****************************************

void setup(void) { 
  Serial.begin(115200); // For debug
  
  setupDisplay();
  setupButtons();
  setupUltrasonic();

  //bild up wifi communication
  // set soilMoistureLimit
  soilMoistureLimit = 50;
  soilMoistureTemp = soilMoistureLimit;

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
    Serial.println(serialNumber);

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


  // Communiation via MQTT
  if (!client.connected()) {
    reconnect();
  }
  client.loop(); //This should be called regularly to allow the client to process incoming messages and maintain its connection to the server.
}
