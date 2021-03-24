//***********************************************All global code****************************************


//------------------Includes
//#include <SPI.h>
//#include <Wire.h>
#include <WiFi.h> //get wifi mac adress
#include <TFT_eSPI.h> // Hardware-specific library for Display
#include <OneWire.h> // for temperature measurement
#include <DallasTemperature.h> // for temperature measurement
#include <PubSubClient.h> // for MQTT


//------------------Defines
#define LOOP_PERIOD 100 // Display updates every 35 ms
#define CF_OL24 &Orbitron_Light_24 //Display font
#define leftPIN 26 //button-pin defines
#define middleLeftPIN 25 //button-pin defines
#define middleRightPIN 33 //button-pin defines
#define rightPIN 32 //button-pin defines
#define debouncePeriod 10 // im ms


//------------------Declares
//--------------------------control------------------------------
uint32_t updateTime = 0; // time for next update
int soilMoistureLimit;
int soilMoistureTemp;
const String serialNumber = WiFi.macAddress();
const String jo = "jo";
//--------------------------Display------------------------------
TFT_eSPI tft = TFT_eSPI(); // Invoke custom library
uint16_t x = tft.width()/2; // center of the screen horizontal
uint16_t y = tft.height()/2; // center of the screen vertical
String currentState; // for display state-machine
//--------------------------Moisture-----------------------------
const int AirValue = 3583;   //max value measured in air --> needs to be adapted
const int WaterValue = 1550;  //min value measured in water --> needs to be adapted
const int MoistureSensorPin = 15; // GPIO pin with ADC for data connection to sensor
//int soilMoistureValue; //moisture value from sensor
int soilmoisturePercent; //moisture value mapped in percentage

//--------------------------Distance-----------------------------
//long duration;
int distance;
const int trigPin = 13; // GPIO trigger pin
const int echoPin = 14; // GPIO echo pin

//--------------------------Temperature--------------------------
const int oneWireBus = 27;// GPIO where the DS18B20 (temperature sensor) is connected to
OneWire oneWire(oneWireBus);// Setup a oneWire instance to communicate with any OneWire devices
DallasTemperature sensors(&oneWire);// Pass our oneWire reference to Dallas Temperature sensor 
float temperatureC; //temperature-variable

//--------------------------Buttons------------------------------
const int btnPinBack = leftPIN;
const int btnPinMinus = middleLeftPIN;
const int btnPinPlus = middleRightPIN;
const int btnPinEnter = rightPIN;
bool btnBack;
bool btnMinus;
bool btnPlus;
bool btnEnter;
int debounceTime; // for button-debouncing

//--------------------------MQTT------------------------------
WiFiClient espClient; //allows to create a connection to a certain IP and port.
PubSubClient client(espClient); //receives as input of the constructor the previously defined WiFiClient object
