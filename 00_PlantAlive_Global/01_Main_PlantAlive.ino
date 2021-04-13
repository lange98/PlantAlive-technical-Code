//***********************************************All logical control code****************************************

void setup(void) { 
  Serial.begin(115200); // For debug
  
  setupDisplay();
  setupButtons();
  setupUltrasonic();


   // set soilMoistureLimit
  soilMoistureLimit = 50;
  soilMoistureTemp = soilMoistureLimit;


  setup_MQTT(); //setup MQTT server
  
  displayBoot("wifi"); //show "connecting to wifi" on display
  setup_wifi();//build up wifi communication
  displayBoot("mqtt"); //show "connecting to mqtt" on display
  connectMQTT();//build up mqtt-server-connection
  disconnectMQTT();
  endWifi();

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
  
void loop() { //calculate sensor data; activate pump; check distance
  if (updateTime <= millis()) {
    updateTime = millis() + LOOP_PERIOD;

    if (!annoyingTryingToConnectIndicator){ //wifi module blocks all analog pins in channel 1
      calcMoisture();
    }
    calcDistance();
    calcTemperature();
    updateDisplay(false, "");

    if (debounceTime <= millis()){
      doButtons(); // display control via buttons
    }

    if (soilmoisturePercent<soilMoistureLimit){
      //pump
    }
    if (distance<1000){//irgend ein limit
      //alert
    }
    //Serial.print("stuff running on core ");
    //Serial.println(xPortGetCoreID());
  }
}

void TaskMQTTcode( void * Parameter ){ // task for MQTT publishing --> core 1
  //Serial.print("Task2 running on core ");
  //Serial.println(xPortGetCoreID());
  delay(10000);
  
  for(;;){ // conect to wifi; connect to mqtt server; oublish data
    setup_wifi();//build up wifi communication
    connectMQTT();//build up mqtt-server-connection
    if (client.connected()){
      cyclicMQTTStuff();
    }
    disconnectMQTT();
    endWifi();
    delay(30000);
  }
}
