# 7Semi TMP23x Arduino Library

Arduino library for **Texas Instruments TMP23x analog temperature sensors**.

---

## Supported Sensors

* TMP235
* TMP236

---

## Features

* Accurate **voltage → temperature conversion**
* Supports:

  * ADC resolution (10-bit / 12-bit)
  * Reference voltage configuration
* Noise handling:

  * Averaging
  * Smoothing
* Calibration support:

  * Offset correction
* Cross-platform:

  * Arduino UNO / Nano
  * ESP32
  * ESP8266

---

## Hardware Connection

### TMP23x Pinout

| Sensor Pin | Connect To      |
| ---------- | --------------- |
| V+         | 5V / 3.3V       |
| Vout       | Analog Pin (A0) |
| GND        | GND             |

### Example (Arduino UNO)

* A0  ← Vout
* 5V  → V+
* GND → GND

---

## Sensor Characteristics

### TMP235

* 500mV at 0°C
* 10mV / °C

### TMP236

* 400mV at 0°C
* 19.5mV / °C

---

## Installation

### Method 1: Manual

1. Download ZIP
2. Extract into:
   `Documents/Arduino/libraries/`
3. Restart Arduino IDE

---

## Basic Example

```cpp
#include <7Semi_TMP23x.h>

TMP23x_7semi sensor(TMP235);

void setup() {
  Serial.begin(115200);

  sensor.begin(A0, 5.0, 1023);

  // Enable smoothing (recommended)
  sensor.setSmoothing(true, 0.2);
}

void loop() {
  float tempC = sensor.readTemperatureC(5);

  Serial.print("Temperature: ");
  Serial.print(tempC);
  Serial.println(" °C");

  delay(1000);
}
```

---

## Recommended Settings

| Use Case       | Samples | Smoothing |
| -------------- | ------- | --------- |
| Fast response  | 3       | 0.3       |
| Balanced       | 5       | 0.2       |
| High stability | 10      | 0.1       |

---

## API Overview

### Initialization

```cpp
sensor.begin(pin, vref, adc_max);
```

### Reading

```cpp
sensor.readTemperatureC(samples);
sensor.readVoltage(samples);
sensor.readTemperatureRaw(raw);
```

### Configuration

```cpp
sensor.setSmoothing(enable, factor);
sensor.setOffset(offset);
```

---

## Notes

* Ensure correct **reference voltage (Vref)** for accurate readings
* Use averaging + smoothing for stable output
* Avoid long wires → reduces noise

---

## Calibration Tip

If readings are slightly off:

```cpp
sensor.setOffset(+1.5);  // adjust in °C
```

---

## 7Semi Standard

This library follows:

* Clean embedded-friendly API
* Hardware abstraction design
* Production-ready filtering
* Consistent unit handling (mV / °C)

---

## License

MIT License


