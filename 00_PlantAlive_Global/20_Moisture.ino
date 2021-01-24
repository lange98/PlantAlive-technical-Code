//***********************************************All code related to moisture functionality****************************************

//Functions
int calcMoisture(){
  // get Values
  soilMoistureValue = analogRead(MoistureSensorPin);  //put Sensor insert into soil
  
  soilmoisturepercent = map(soilMoistureValue, AirValue, WaterValue, 0, 100);
  //Debug
  //Serial.println("Analog-Input: " + String(soilMoistureValue));
  //Serial.println("Moisture: " + String(soilmoisturepercent) + "%");
  return(soilmoisturepercent);
}
