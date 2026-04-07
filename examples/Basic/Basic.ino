/**
  * 7Semi TMP23x Temperature Sensor Example
  *
  * CONNECTION (TMP235 / TMP236)
  *
  * TMP23x Sensor Pinout:
  * ---
  * V+   → 5V (or 3.3V depending on board)
  * Vout → A0 (analog input pin)
  * GND  → GND
  *
  * Arduino UNO:
  * ---
  * A0  ← Sensor Vout
  * 5V  → Sensor V+
  * GND → Sensor GND
  *
  * NOTES:
  * * TMP235: ~500mV at 0°C, 10mV/°C
  * * TMP236: ~400mV at 0°C, 19.5mV/°C
  * * Output is analog voltage → must use analog pin
  */

#include <7Semi_TMP23x.h>

TMP23x_7semi sensor(TMP235);  // change to TMP236 if needed

void setup() {
  Serial.begin(115200);

  /**
  * Initialize sensor
  * * A0 → analog pin
  * * 5.0 → reference voltage
  * * 1023 → 10-bit ADC
  */
  sensor.begin(A0, 5.0, 1023);

}

void loop() {

  float tempC = sensor.readTemperatureC(10);  // smoothed temperature

  Serial.print("Temp (C)  : ");
  Serial.print(tempC);
  Serial.println(" °C");

  Serial.println();

  delay(100);
}
