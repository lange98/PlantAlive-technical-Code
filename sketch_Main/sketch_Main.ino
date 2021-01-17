//Includes
#include <TFT_eSPI.h> // Hardware-specific library
#include <SPI.h>
#include <Wire.h>

//Defines
#define LOOP_PERIOD 100 // Display updates every 35 ms
#define CF_OL24 &Orbitron_Light_24

//Declares
uint32_t updateTime = 0;       // time for next update
TFT_eSPI tft = TFT_eSPI();       // Invoke custom library
  //moisture sensor
const int AirValue = 3583;   //you need to replace this value with Value_1
const int WaterValue = 1550;  //you need to replace this value with Value_2
const int SensorPin = 15;
int soilMoistureValue = 0;
int soilmoisturepercent = 0;
int highest = 2650;
int lowest = 2650;
int average = 2650;
int counter = 0;
// Find centre of screen
uint16_t x = tft.width()/2;
uint16_t y = tft.height()/2;

// variables for distance sensor
long duration;
int distance;

// pin numbers for distance sensor
const int trigPin = 13;
const int echoPin = 14;



void setup(void) { 
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

  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  
  Serial.begin(115200); // For debug

  updateTime = millis(); // Next update time
}
  
void loop() {

  if (updateTime <= millis()) {
    updateTime = millis() + LOOP_PERIOD;

    // get Values
    soilMoistureValue = analogRead(SensorPin);  //put Sensor insert into soil
    soilmoisturepercent = map(soilMoistureValue, AirValue, WaterValue, 0, 100);
    //Debug
    //Serial.println("Analog-Input: " + String(soilMoistureValue));
    //Serial.println("Moisture: " + String(soilmoisturepercent) + "%");

    //calc min max values
    if (soilMoistureValue > highest){
      highest = soilMoistureValue;
    }
    else if (soilMoistureValue < lowest){
      lowest = soilMoistureValue;
    }

    counter ++;
    if (counter > 100){
      counter = 0;
    }

    //distance sensor
    // Clears the trigPin
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    // Sets the trigPin on HIGH state for 10 micro seconds
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    // Reads the echoPin, returns the sound wave travel time in microseconds
    duration = pulseIn(echoPin, HIGH);
    //Serial.print("Duration: ");
    //Serial.println(duration);
    // Calculating the distance
    distance= duration*0.034/2;
    // Prints the distance on the Serial Monitor
    //Serial.print("Distance: ");
    //Serial.println(distance);
    
    //display
    //tft.fillScreen(TFT_BLACK);
    String valMoi = String(soilmoisturepercent);
    String valWat = String(distance);
    // Set the padding to the maximum width that the digits could occupy in font 4
    // This ensures small numbers obliterate large ones on the screen
    tft.setTextPadding( tft.textWidth("100%", 4) );//setzt einen Raum der länge und Größe des angegebenen Strings (hier: Schriftgröße 4)
    tft.drawString(valMoi+"%", x, 40, 4);
    tft.drawString("100%", x, 80, 4);
    tft.drawString("0%", x, 120, 4);
    tft.drawString("22*C", x, 160, 4);
    tft.setTextPadding( tft.textWidth("8888ml", 4) );//setzt einen Raum der länge und Größe des angegebenen Strings (hier: Schriftgröße 4)
    tft.drawString(valWat+"ml", x+20, 200, 4);
    // Reset text padding to 0 otherwise all future rendered strings will use it!
    tft.setTextPadding(0);
  }
}
