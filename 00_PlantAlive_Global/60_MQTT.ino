
//---------------------Initialise
const char* ssid = "Funknetz-blablub"; //Network SSID
const char* password = "987gast654"; //Network PASSWORD
const char* mqtt_server = "192.168.179.37"; //MQTT Broker IP address; EXAMPLE: "192.168.1.144"
const int mqttPort = 1883; //MQTT Port


long lastMsg = 0;
char msg[50];
int value = 0;


//---------------------Wifi connection
void setup_wifi() {
  annoyingTryingToConnectIndicator = true;
  delay(10);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);

  int tempCounter = 0;
  while (WiFi.status() != WL_CONNECTED) {
    if (tempCounter>=30){ //30 attempts = 15 Seconds
      Serial.println("");
      Serial.println("WiFi not connected");
      return;
    }
    delay(500);
    Serial.print(".");
    tempCounter = tempCounter+1;
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void endWifi(){
  WiFi.mode(WIFI_OFF);
  annoyingTryingToConnectIndicator = false;
}

//---------------------set mqtt server adress
void setup_MQTT(){
  Serial.print("set MQTT Server: ");
  client.setServer(mqtt_server, mqttPort); //specify the address and the port of the MQTT server
  client.setCallback(callback);
  Serial.println("done!");
  /*  
   * Use the setCallback method on the same object to specify a handling function.
   * This handling function will be executed when a MQTT message is received on a subscribed topic.
   * We will leave the code of this function for latter.  
   */
}

//---------------------connect to the mgtt server
//If not connected, reconnect in this function
//In the reconnect() function, you can subscribe to MQTT topics.
void connectMQTT() {
  if (WiFi.status() == WL_CONNECTED){
    int tempCounter = 0;
    while (!client.connected()) {// Loop until we're reconnected
      if (tempCounter>=1){ // 3 attempts = 15 Seconds
        break;
      }
      Serial.print("Attempting MQTT connection..."); // Attempt to connect
      if (client.connect("PlantAliveUser")) {
        /*
         * --> boolean connect (clientID, [username, password], [willTopic, willQoS, willRetain, willMessage], [cleanSession])
         * function client.connect seems to only take direct strings but no variables
         * therefore I have to insert a String
         * Plantalive pots should differ in mgtt User name...?
         */
        Serial.println("connected");
  
        //publish serial number
        publishSerialNumber(serialNumber);
  
        //subscribe channels
        client.subscribe(channelMoisture);// Subscribe to the wanted topic to receive messages published on that topic from other clients.
        client.subscribe(channelInfo);// Subscribe to the wanted topic to receive messages published on that topic from other clients.
      } else {
        Serial.print("failed, rc=");
        Serial.print(client.state());
        Serial.println(" try again in 5 seconds");
        tempCounter = tempCounter+1;
        Serial.println("counter: "+String(tempCounter));
        delay(5000);
      }
    }
  }
}

void disconnectMQTT(){
  //client.stop();
}

//---------------------callback function
//In the callback() function, the ESP32 receives the MQTT messages of the subscribed topics. According to the MQTT topic and message, it turns the LED on or off:
//function get automatically called when message arrives
void callback(char* topic, byte* message, unsigned int mLength) {
  Serial.print("Message arrived on topic: ");
  Serial.print(topic);
  Serial.print(". Message: ");
  String messageTemp;
  
  for (int i = 0; i < mLength; i++) {
    Serial.print((char)message[i]);
    messageTemp += (char)message[i];
  }
  Serial.println();

  if(strstr(topic, "target") != NULL){ //if topic contains word "target" --> bidirectional target Moisture topic
    //set new targetMoisture
    //soilMoistureLimit = messageTemp.toInt();
    StaticJsonDocument<256> doc;
    deserializeJson(doc, message, mLength);
    int targetMoisture = doc[TargetMoistureKey];
    soilMoistureLimit = targetMoisture;
    //Serial.println(String(targetMoisture));
    //Serial.println("new target Moisture set to messageTemp");
  }
  // Feel free to add more if statements to control more GPIOs with MQTT
}


//---------------------help functions
void cyclicMQTTStuff(){
  if (!client.connected()) {
    connectMQTT();
  }
  client.loop(); //This should be called regularly to allow the client to process incoming messages and maintain its connection to the server.
  publishMQTTMsgInfo();
}


//---------------------publish
void publishSerialNumber(String serialNumber){
  const char* channel[]={channelNew};
  
  // Length (with one extra character for the null terminator)
  int str_len = serialNumber.length() + 1; 
  
  // Prepare the character array (the buffer) 
  char char_array[str_len];
  
  // Copy it over 
  //serialNumber.toCharArray(char_array, str_len);
  serialNumber.toCharArray(char_array, str_len);
  
  //publish
  client.publish(channel[0], char_array);
}

void publishMQTTMsgTargetMoisture(){ //channel needs to be declared dynamically
  const char* channel[]={channelMoisture};

  StaticJsonDocument<100> testDocument;
  testDocument[TargetMoistureKey] = soilMoistureLimit;

  char MSGBuffer[100];
  serializeJson(testDocument, MSGBuffer);

  client.publish(channel[0], MSGBuffer);
}

void publishMQTTMsgInfo(){ //channel needs to be declared dynamically
  const char* channel[]={channelInfo};

  StaticJsonDocument<100> testDocument;
  testDocument[MoistureKey] = soilmoisturePercent;
  testDocument[TemperatureKey] = temperatureC;
  testDocument[DistanceKey] = distance;

  char MSGBuffer[100];
  serializeJson(testDocument, MSGBuffer);

  client.publish(channel[0], MSGBuffer);
}



////You need to convert the temperature float variable to a char array, so that you can publish the temperature reading in the targethumidity topic:
//char temperatureMSG[8];
//dtostrf(temperatureC, 1, 2, temperatureMSG); //float to char array

////You need to convert the moisture int variable to a char array:
//char moistureMSG[16];
//itoa(soilmoisturePercent, moistureMSG, 10); //10 means decimal
////You need to convert the distance int variable to a char array:
//char distanceMSG[16];
//itoa(distance, distanceMSG, 10); //10 means decimal
