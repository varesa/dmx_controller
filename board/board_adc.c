//
// Created by esa on 4.5.2016.
//

#include <median.h>
#include "hal.h"

// Lets configure our ADC first


// ADCConfig structure for stm32 MCUs is empty
static ADCConfig adccfg = {};

// Create buffer to store ADC results. This is
// one-dimensional interleaved array
#define ADC_BUF_DEPTH 32 // depth of buffer
#define ADC_CH_NUM 5    // number of used ADC channels
static adcsample_t samples_buf[ADC_BUF_DEPTH * ADC_CH_NUM]; // results array

// Fill ADCConversionGroup structure fields
static ADCConversionGroup adccg = {
        // this 3 fields are common for all MCUs
        // set to TRUE if need circular buffer, set FALSE otherwise
        TRUE,
        // number of channels
        (uint16_t)(ADC_CH_NUM),
        // callback function, set to NULL for begin
        NULL,
        // error callback function
        NULL,
        // Resent fields are stm32 specific. They contain ADC control registers data.
        // Please, refer to ST manual RM0008.pdf to understand what we do.
        // CR1 register content, set to zero for begin
        0,
        // CR2 register content, set to zero for begin
        0,
        // SMRP1 register content, set to zero for begin
        0,
        // SMRP2 register content, set to zero for begin
        0,
        // SQR1 register content. Set channel sequence length
        ((ADC_CH_NUM - 1) << 20),
        // SQR2 register content, set to zero for begin
        0,
        // SQR3 register content. We must select 2 channels
        // For example 15th and 10th channels. Refer to the
        // pinout of your MCU to select other pins you need.
        // On STM32-P103 board they connected to PC15 and PC0 contacts
        // On STM32-103STK board they connected to EXT2-7 contact and joystick
        ADC_SQR3_SQ1_N(ADC_CHANNEL_IN4) |
        ADC_SQR3_SQ2_N(ADC_CHANNEL_IN0) |
        ADC_SQR3_SQ3_N(ADC_CHANNEL_IN1) |
        ADC_SQR3_SQ4_N(ADC_CHANNEL_IN2) |
        ADC_SQR3_SQ5_N(ADC_CHANNEL_IN3),
};


void adc_init() {
    // Following 3 functions use previously created configuration
    // to initialize ADC block, start ADC block and start conversion.
    // &ADCD1 is pointer to ADC driver structure, defined in the depths of HAL.
    // Other arguments defined ourself earlier.
    adcInit();
    adcStart(&ADCD1, &adccfg);
    adcStartConversion(&ADCD1, &adccg, &samples_buf[0], ADC_BUF_DEPTH);

    // Thats all. Now your conversion run in background without assistance.
}

uint16_t channel_values[ADC_BUF_DEPTH];

uint16_t adc_get_value(uint8_t channel) {
    uint8_t adc_channel = ADC_CH_NUM - channel;

    uint32_t sum = 0;
    int i = 0;
    for(i = 0; i < ADC_BUF_DEPTH; i++) {
        //sum += samples_buf[adc_channel + i*ADC_CH_NUM];
        channel_values[i] = samples_buf[adc_channel + i*ADC_CH_NUM];
    }
    //uint16_t average = sum / ADC_BUF_DEPTH;
    //uint8_t normalized = average / 40;

    //uint16_t median = select(channel_values, ADC_BUF_DEPTH/2, ADC_BUF_DEPTH);
    uint16_t median = channel_values[5];
    uint16_t normalized = median / 16;

    /*if (normalized > 100) {
        return 100;
    } else {*/
        return normalized;
    //}
}