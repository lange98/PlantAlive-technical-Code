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


  xTaskCreatePinnedToCore( //pin task for MQTT publishing to core1
             TaskMQTTcode,  /* Task function. */
             "TaskMQTT",    /* name of task. */
             10000,      /* Stack size of task */
             NULL,       /* parameter of the task */
             1,          /* priority of the task */
             &TaskMQTT,  /* Task handle to keep track of created task */
             1);         /* pin task to core 1 */

}
  
void loop() {
  if (updateTime <= millis()) {
    updateTime = millis() + LOOP_PERIOD;

    calcMoisture();
    calcDistance();
    calcTemperature();
    updateDisplay(false, "");

    //if (connectedToMQTT){
    //  cyclicMQTTStuff();
    //}

    if (soilmoisturePercent<soilMoistureLimit){
      //pump
      return;
    }
    if (distance<1000){//irgend ein limit
      //alert
      return;
    }
    Serial.print("stuff running on core ");
    Serial.println(xPortGetCoreID());
  }

  if (debounceTime <= millis()){
    doButtons(); // display control via buttons
  }
}

void TaskMQTTcode( void * Parameter ){ // task for MQTT publishing --> core 1
  Serial.print("Task2 running on core ");
  Serial.println(xPortGetCoreID());

  for(;;){
    if (connectedToMQTT){
      cyclicMQTTStuff();
    }
    Serial.println("test MQTT stuff");
    delay(10000);
  }
}
