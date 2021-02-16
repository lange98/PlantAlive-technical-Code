//***********************************************All code related to temperature functionality****************************************

//Functions
void calcTemperature(){
      //temperature measurement
    sensors.requestTemperatures(); 
    temperatureC = sensors.getTempCByIndex(0);
    //float temperatureF = sensors.getTempFByIndex(0);
}
