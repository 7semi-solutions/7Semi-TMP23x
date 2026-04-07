
#include <Arduino.h>

class AnalogSensor
{
public:

AnalogSensor() {
}

/**
 * Initialize analog sensor hardware
 * - analogPin: input pin connected to sensor
 * - Vref: ADC reference voltage (default 5.0V)
 * - ADC_max_val: maximum ADC value
 *   • 1023 → 10-bit Arduino (UNO, Nano)
 *   • 4095 → 12-bit (ESP32, SAMD)
 *
 * Notes:
 * - Must be called before any read operation
 * - Configures pin as INPUT
 */
void begin(uint8_t analogPin, float Vref = 5.0, int ADC_max_val = 1023)
{
  /**
   * Assign configuration first
   * - ensures correct setup before pin usage
   */
  pin = analogPin;
  reference_voltage = Vref;
  adc_max = ADC_max_val;

  /**
   * Configure pin mode
   * - analog input requires INPUT mode
   */
  pinMode(pin, INPUT);
}

/**
 * Set ADC reference voltage
 * - Vref: reference voltage in volts
 *
 * Notes:
 * - Must be > 0 to be valid
 * - Used for voltage conversion:
 *   voltage = (raw / adc_max) * Vref
 */
void setVref(float Vref)
{
  /**
   * Validate input
   * - ignore invalid (zero or negative) values
   */
  if (Vref > 0)
  {
    reference_voltage = Vref;
  }
}

  /**
 * Get reference voltage
 * - returns configured ADC reference voltage (in volts)
 *
 * Notes:
 * - Used internally for voltage calculations
 * - Typically 5.0V (UNO) or 3.3V (ESP32)
 */
float getVref() const
{
  return reference_voltage;
}

/**
 * Set ADC maximum value
 * - max_val: maximum ADC count
 *   • 1023 → 10-bit ADC
 *   • 4095 → 12-bit ADC
 *
 * Notes:
 * - Must be > 0
 * - Also updates calibration maximum to maintain consistency
 */
void setAdcMax(int max_val)
{
  /**
   * Validate input
   * - ignore invalid values
   */
  if (max_val > 0)
  {
    adc_max = max_val;
    cal_max = max_val;
  }
}

/**
 * Get ADC maximum value
 * - returns current ADC resolution max count
 */
int getAdcMax() const
{
  return adc_max;
}

/**
 * Read raw ADC value
 * - returns direct analogRead() output
 *
 * Notes:
 * - Range: 0 → adc_max
 * - No filtering or scaling applied
 */
int readRaw()
{
  return analogRead(pin);
}

/**
 * Read averaged ADC value
 * - samples: number of readings to average
 *
 * Notes:
 * - Reduces noise and improves stability
 * - Higher samples → smoother but slower response
 * - Recommended: 5–20 samples
 */
int readAverage(uint8_t samples = 10)
{
  /**
   * Prevent invalid sample count
   */
  if (samples == 0) return readRaw();

  long sum = 0;

  for (uint8_t i = 0; i < samples; i++)
  {
    sum += analogRead(pin);
  }

  return sum / samples;
}

/**
 * Read sensor voltage
 * - samples: averaging count (default 1)
 *
 * Returns:
 * - Voltage in millivolts (mV)
 *
 * Formula:
 * - voltage = (raw / adc_max) * Vref
 *
 * Notes:
 * - Uses averaging internally for stable output
 * - Multiply by 1000 → converts volts to millivolts for better precision
 * - Example: 512 (midpoint) → ~2500 mV (for
 */
float readVoltage(uint8_t samples = 1)
{
  /**
   * Get averaged raw value
   */
  float raw = readAverage(samples);

  /**
   * Convert to millivolts
   */
  return (raw / (float)adc_max) * reference_voltage * 1000.0f;
}

protected:
  uint8_t pin;
  float reference_voltage;
  int adc_max;

  int cal_min;
  int cal_max;
};