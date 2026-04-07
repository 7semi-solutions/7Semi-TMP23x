

#ifndef _7SEMI_TMP23x_H_
#define _7SEMI_TMP23x_H_

#include "Arduino.h"
#include "7Semi_Analog_Sensor.h"

enum sensor_type {
  TMP235 = 235,
  TMP236 = 236,
  TMP237 = 237
};
/**
 * TMP23x Analog Temperature Sensor
 */
class TMP23x_7semi {
public:
  /**
   * TMP23x Constructor
   * - type: sensor model selection
   *   • TMP235 → 10mV/°C, 500mV offset
   *   • TMP236 → 19.5mV/°C, 400mV offset
   *
   * Notes:
   * - Initializes sensor-specific calibration parameters
   * - Uses millivolts (mV) internally for better precision
   */
  TMP23x_7semi(sensor_type type = TMP235);

  /**
   * Initialize TMP23x sensor
   * - pin: analog input pin
   * - vref: ADC reference voltage (in volts)
   * - ADC_max: ADC resolution max value
   *   • 1023 → 10-bit
   *   • 4095 → 12-bit
   *
   * Notes:
   * - Must be called before reading temperature
   * - Uses AnalogSensor abstraction internally
   */
  void begin(uint8_t temperature_pin = 255, float reference_voltage = 5.0, int ADC_max = 1023);

  /**
   * Set ADC reference voltage
   * - vref: reference voltage in volts
   *
   * Notes:
   * - Must be > 0 to be valid
   * - Updates both local variable and AnalogSensor configuration
   */
  void setVref(float vref);

  /**
   * Get ADC reference voltage
   * - returns current reference voltage in volts
   */
  float getVref() const;

  /**
   * Set ADC maximum value
   * - max_val: maximum ADC count
   *   • 1023 → 10-bit
   *   • 4095 → 12-bit
   *
   * Notes:
   * - Must be > 0 to be valid
   * - Updates both local variable and AnalogSensor configuration
   */
  void setAdcMax(int max_val);

  /**
   * Get ADC maximum value
   * - returns current ADC resolution max count
   */
  int getAdcMax() const;

  /**
   * Read raw ADC value
   * - returns raw sensor output from ADC
   * - Range: 0 → ADC_max
   */
  void readTemperatureRaw(uint16_t &rawTemperature);

  /**
   * Read sensor voltage
   * - average_samples: number of samples for averaging
   *
   * Returns:
   * - Voltage in millivolts (mV)
   * - Uses AnalogSensor averaging internally
   * - Improves stability for noisy signals
   */
  float readVoltage(uint8_t average_samples = 10);

  /**
   * Set temperature offset correction
   * - offset: temperature offset in °C
   * - Used to compensate sensor/system error
   */
  void setOffset(float offset);

  /**
   * Read temperature in Celsius
   * - averageSamples: number of ADC samples for averaging
   *
   * Returns:
   * - Temperature in °C
   *
   * Notes:
   * - Uses millivolt input from sensor
   * - Applies optional smoothing
   * - Formula:
   *   temperature = (voltage - offset_voltage) / scale
   *   + user offset correction
   */
  float readTemperatureC(uint8_t averageSamples = 10);

  /**
   * Enable or disable smoothing
   * - enable: true → enable EMA filtering
   * - factor: smoothing factor (0.0 → 1.0)
   *
   * Notes:
   * - 0.1 → very smooth (slow response)
   * - 0.5 → balanced 
   * - 0.8 → fast response, less smoothing
   * - 1.0 → no smoothing (raw voltage used directly)
   */
  void setSmoothing(bool enable, float factor = 0.5);

private:

  AnalogSensor analog;

  uint8_t temperature_pin;
  float reference_voltage;
  float offset_temperature;  

  float offset_voltage;  // Voltage at 0°C
  float scale;          // V per °C

  float smooth_temperature = 0;
  bool smoothing = true;
  bool smoothing_initialized = false;
  float smoothing_factor = 0.25; 
};

#endif