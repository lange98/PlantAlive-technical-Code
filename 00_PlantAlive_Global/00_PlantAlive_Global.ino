//***********************************************All global code****************************************


//------------------Includes
//--------------------------control------------------------------
//#include <SPI.h>
//#include <Wire.h>

//--------------------------Display------------------------------
#include <TFT_eSPI.h> // Hardware-specific library

//--------------------------Moisture-----------------------------

//--------------------------Distance-----------------------------

//--------------------------Temperature--------------------------
#include <OneWire.h> // for temperature measurement
#include <DallasTemperature.h> // for temperature measurement
//--------------------------Buttons------------------------------



//------------------Defines
//--------------------------control------------------------------
#define LOOP_PERIOD 100 // Display updates every 35 ms

//--------------------------Display------------------------------
#define CF_OL24 &Orbitron_Light_24

//--------------------------Moisture-----------------------------

//--------------------------Distance-----------------------------

//--------------------------Temperature--------------------------

//--------------------------Buttons------------------------------
#define initState 0
#define defaultState 1
#define menuState 2
#define changeMoistureState 3

#define leftPIN 26
#define middleLeftPIN 25
#define middleRightPIN 33
#define rightPIN 32

#define debouncePeriod 10 // im ms

//------------------Declares
//--------------------------control------------------------------
uint32_t updateTime = 0; // time for next update

//--------------------------Display------------------------------
TFT_eSPI tft = TFT_eSPI(); // Invoke custom library
uint16_t x = tft.width()/2; // center of the screen horizontal
uint16_t y = tft.height()/2; // center of the screen vertical
//--------------------------Moisture-----------------------------
const int AirValue = 3583;   //max value measured in air --> needs to be adapted
const int WaterValue = 1550;  //min value measured in water --> needs to be adapted
const int MoistureSensorPin = 15; // GPIO pin with ADC for data connection to sensor
int soilMoistureValue; //moisture value from sensor
int soilmoisturepercent; //moisture value mapped in percentage

//--------------------------Distance-----------------------------
long duration;
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
bool btnBack; //0
bool btnMinus; //1
bool btnPlus; //2
bool btnEnter; //3
int currentState = initState;
int debounceTime;
