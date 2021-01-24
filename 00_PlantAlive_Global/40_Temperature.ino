//***********************************************All code related to temperature functionality****************************************

//Functions
float calcTemperature(){
      //temperature measurement
    sensors.requestTemperatures(); 
    float temperatureC = sensors.getTempCByIndex(0);
    float temperatureF = sensors.getTempFByIndex(0);
    return(temperatureC);
}
