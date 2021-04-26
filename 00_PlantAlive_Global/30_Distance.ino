//***********************************************All code related to distance functionality****************************************

//Functions
void setupUltrasonic(){
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
}

void calcDistance(){//distance sensor
    // Clears the trigPin
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    
    // Sets the trigPin on HIGH state for 10 micro seconds
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    
    // Reads the echoPin, returns the sound wave travel time in microseconds
    long duration = pulseIn(echoPin, HIGH);
    //Serial.print("Duration: ");
    //Serial.println(duration);
    
    // Calculating the distance
    int realDistance= duration*0.034/2*10;
    Serial.print("Distance: ");
    Serial.println(realDistance);

    //for steps out of real distance (mm)
    if (realDistance >= 100){
      distance = 1;
    }
    else if(realDistance >=80){
      distance = 2;
    }
    else if(realDistance >=60){
      distance = 3;
    }
    else if(realDistance >=20){
      distance = 4;
    }
    else if(realDistance < 20){
      distance = 5;
    }

}
