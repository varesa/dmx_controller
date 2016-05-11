//
// Created by esa on 4.5.2016.
//

#include <stdint.h>

#include "hal.h"

#ifndef ARM_ETHERNETBOARD_ADC_H
#define ARM_ETHERNETBOARD_ADC_H

void adc_init(void);

uint16_t adc_get_value(uint8_t channel);

#endif //ARM_ETHERNETBOARD_ADC_H
