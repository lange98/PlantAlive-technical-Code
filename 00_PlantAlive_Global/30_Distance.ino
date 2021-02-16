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
    distance= duration*0.034/2*10;
    //Serial.print("Distance: ");
    //Serial.println(distance);
}
