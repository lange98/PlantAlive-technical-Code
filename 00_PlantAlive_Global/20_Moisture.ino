//***********************************************All code related to moisture functionality****************************************

//Functions
void calcMoisture(){
  // get Values
  int soilMoistureValue = analogRead(MoistureSensorPin);  //put Sensor insert into soil
  
  soilmoisturePercent = map(soilMoistureValue, AirValue, WaterValue, 0, 100);
  //Debug
  //Serial.println("Analog-Input: " + String(soilMoistureValue));
  //Serial.println("Moisture: " + String(soilmoisturepercent) + "%");
}
