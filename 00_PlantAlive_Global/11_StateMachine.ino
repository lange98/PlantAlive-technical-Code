//***********************************************Display  state machine - called by doButton function****************************************

String stateMachine(String btn){
  if (currentState == "init"){
    displayBoot("");
    return ("init");
  }
  else if (currentState == "default"){
    if(btn == "enter"){
      changeState();
      displayMenu();
      return("menu");
    }
    else if (btn == "plus"){
      displayDefault();
      return ("default");
    }
    else if (btn == "minus"){
      displayDefault();
      return ("default");
    }
    else if (btn == "back"){
      displayDefault();
      return ("default");
    }
  }
  else if (currentState == "menu"){
    if(btn == "enter"){
      changeState();
      soilMoistureTemp = soilMoistureLimit;
      displaySetMoisture();
      return("setMoisture");
      //toDO
    }
    else if (btn == "plus"){
      return("menu");
      //toDO
    }
    else if (btn == "minus"){
      return("menu");
      //toDO
    }
    else if (btn == "back"){
      changeState();
      displayDefault();
      return ("default");
    }
  }
  else if (currentState == "setMoisture"){
    if(btn == "enter"){
      soilMoistureLimit = soilMoistureTemp;
      publishMQTTMsgTargetMoisture();
      changeState();
      displayMenu();
      return("menu");
    }
    else if (btn == "plus"){
      incSoilMoistureTemp();
      displaySetMoisture();
      return("setMoisture");
    }
    else if (btn == "minus"){
      decSoilMoistureTemp();
      displaySetMoisture();
      return("setMoisture");
    }
    else if (btn == "back"){
      changeState();
      displayMenu();
      return ("menu");
    }
  }
}

void incSoilMoistureTemp(){
  if(soilMoistureTemp<=90){
    soilMoistureTemp += 10;
  }
}

void decSoilMoistureTemp(){
  if(soilMoistureTemp>=10){
    soilMoistureTemp -= 10;
  }
}
