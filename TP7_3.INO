#include <SoftwareSerial.h>

SoftwareSerial serial(2, 3);  

const int temperaturePin = A0; 
const int updateInterval = 1000;  

unsigned long previousMillis = 0;
float temperature;
float minimumTemp = 100;  
float maximumTemp = -100;
float totalTemp = 0;
int numReadings = 0;

void setup() {
  Serial.begin(9600);  
  serial.begin(9600);  
}

void loop() {
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= updateInterval) {
    previousMillis = currentMillis;

    int sensorValue = analogRead(temperaturePin);
    temperature = map(sensorValue, 0, 1023, -50, 150); 

    if (temperature < minimumTemp) {
      minimumTemp = temperature;
    }
    if (temperature > maximumTemp) {
      maximumTemp = temperature;
    }
    totalTemp += temperature;
    numReadings++;

    if (numReadings == 60) { 
      float averageTemp = totalTemp / numReadings;

      serial.print(minimumTemp);
      serial.print(",");
      serial.print(maximumTemp);
      serial.print(",");
      serial.println(averageTemp);

      minimumTemp = 100;  
      maximumTemp = -100;
      totalTemp = 0;
      numReadings = 0;
    }
  }
}
