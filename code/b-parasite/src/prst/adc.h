#ifndef _PRST_ADC_H_
#define _PRST_ADC_H_

#include <stdint.h>

typedef struct prst_adc_batt_val {
    int16_t raw;
    uint16_t millivolts;
    double voltage;
} prst_adc_batt_read_t;

typedef struct prst_adc_soil_moisture {
    int16_t raw;
    // A value from 0 (completely dry) to 2^10 (completely wet).
    uint16_t relative;
    double percentage;
} prst_adc_soil_moisture_t;

typedef struct prst_adc_photo_sensor {
    int16_t raw;
    double voltage;
    // Value in lux.
    uint16_t brightness;
} prst_adc_photo_sensor_t;

void prst_adc_init();

prst_adc_batt_read_t prst_adc_batt_read();

prst_adc_soil_moisture_t prst_adc_soil_read(double battery_voltage);

prst_adc_photo_sensor_t prst_adc_photo_read(double battery_voltage);

#endif // _PRST_ADC_H_