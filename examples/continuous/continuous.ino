#include "7Semi_TMP23x.h"

TMP23x_7semi tempSensor(A0);

void setup() {
  Serial.begin(115200);
  tempSensor.begin(A0);

  // Optional: adjust if using different TMP23x variant
  tempSensor.setOffset(0.5);  // 500mV
  tempSensor.setScale(0.01);  // 10mV per °C
}

void loop() {
  Serial.print("Temperature (C): ");
  Serial.print(tempSensor.readCelsius());

  Serial.print(" | (F): ");
  Serial.println(tempSensor.readFahrenheit());

  delay(1000);
}