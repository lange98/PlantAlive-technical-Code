


//---------------------Initialise

const char* ssid = "REPLACE_WITH_YOUR_SSID"; //Network SSID
const char* password = "REPLACE_WITH_YOUR_PASSWORD"; //Network PASSWORD
const char* mqtt_server = "YOUR_MQTT_BROKER_IP_ADDRESS"; //MQTT Broker IP address
//EXAMPLE: const char* mqtt_server = "192.168.1.144";
const int mqttPort = 1883; //MQTT Port


long lastMsg = 0;
char msg[50];
int value = 0;


//---------------------Wifi connection
void setup_wifi() {
  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

//---------------------specify mqtt server adress
void setup_MQTT(){
  client.setServer(mqtt_server, mqttPort); //specify the address and the port of the MQTT server
  client.setCallback(callback);
  /*  
   * Use the setCallback method on the same object to specify a handling function.
   * This handling function will be executed when a MQTT message is received on a subscribed topic.
   * We will leave the code of this function for latter.  
   */
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

  // Feel free to add more if statements to control more GPIOs with MQTT
}


//---------------------connect to the mgtt server
//If not connected, reconnect i this function
//In the reconnect() function, you can subscribe to MQTT topics.
void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect("PlantAliveUser")) {
      /*
       * --> boolean connect (clientID, [username, password], [willTopic, willQoS, willRetain, willMessage], [cleanSession])
       * function client.connect seems to only take direct strings but no variables
       * therefore I have to insert a String
       * Plantalive pots should differ in mgtt User name...?
       */
      Serial.println("connected");
      client.subscribe("esp32/output"); // Subscribe to the wanted topic to receive messages published on that topic from other clients.
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}


//---------------------publish
void publishMQTTMsg(int val){
  //You need to convert the temperature float variable to a char array, so that you can publish the temperature reading in the esp32/temperature topic:
  char msgArray[8];
  float testFloat = 10.2;
  dtostrf(testFloat, 1, 2, msgArray); //float to char array
  client.publish("esp32/humidity", msgArray);

  //int to char array???
  /*
   * int num = 1234;
   * char cstr[16];
   * itoa(num, cstr, 10);
   */
  
}
