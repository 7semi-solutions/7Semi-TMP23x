#include "7Semi_TMP23x.h"

TMP23x_7semi::TMP23x_7semi(sensor_type type)
{
  /**
   * Configure calibration based on sensor type
   */
  switch (type)
  {
    case TMP235:
      /**
       * TMP235 characteristics
       * - 500mV at 0°C
       * - 10mV per °C
       */
      offset_voltage = 500.0f;
      scale = 10.0f;
      break;

    case TMP236:
      /**
       * TMP236 characteristics
       * - 400mV at 0°C (corrected comment)
       * - 19.5mV per °C
       */
      offset_voltage = 400.0f;
      scale = 19.50f;
      break;

    default:
      /**
       * Fallback to safe default (TMP235 behavior)
       */
      offset_voltage = 500.0f;
      scale = 10.0f;
      break;
  }
}


void TMP23x_7semi::begin(uint8_t pin, float vref, int ADC_max)
{
  if (pin != 255)
  {
    temperature_pin = pin;
  }
  // Configure reference voltage
  if (vref > 0)
  {
    reference_voltage = vref;
    analog.setVref(vref);
  }

  // Configure ADC resolution
  if (ADC_max > 0)
  {
    analog.setAdcMax(ADC_max);
  }

  /**
   * Initialize underlying analog sensor
   * - ensures hardware is configured correctly
   */
  analog.begin(temperature_pin, reference_voltage, ADC_max);
}

void TMP23x_7semi::setVref(float vref)
{
  if (vref > 0)
  {
    reference_voltage = vref;
    analog.setVref(vref);
  }
}

float TMP23x_7semi::getVref() const
{
  return reference_voltage;
}

void TMP23x_7semi::setAdcMax(int max_val)
{
  if (max_val > 0)
  {
    analog.setAdcMax(max_val);
  }
}

int TMP23x_7semi::getAdcMax() const
{
  return analog.getAdcMax();
}

void TMP23x_7semi::readTemperatureRaw(uint16_t &rawTemperature)
{
  rawTemperature = analog.readRaw();
}

float TMP23x_7semi::readVoltage(uint8_t average_samples)
{
  return analog.readVoltage(average_samples);
}

void TMP23x_7semi::setOffset(float offset)
{
  offset_temperature = offset;
}

float TMP23x_7semi::readTemperatureC(uint8_t averageSamples)
{
  // Read sensor voltage (mV)
  float voltage = analog.readVoltage(averageSamples);


  // Apply smoothing 
  if (smoothing)
  {
    if (!smoothing_initialized)
    {
      smooth_temperature = voltage;
      smoothing_initialized = true;
    }

    smooth_temperature =
      smoothing_factor * voltage +
      (1.0f - smoothing_factor) * smooth_temperature;

    voltage = smooth_temperature;
  }

  // Prevent invalid scale
  if (scale == 0) return 0;

  // Convert voltage (mV) → temperature (°C)
  return ((voltage - offset_voltage) / scale) + offset_temperature;
}

void TMP23x_7semi::setSmoothing(bool enable, float factor)
{
  smoothing = enable;

  /**
   * Validate smoothing factor
   */
  if (factor >= 0.0f && factor <= 1.0f)
  {
    smoothing_factor = factor;
  }
}