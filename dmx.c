//
// Created by esa on 5.5.2016.
//

#include <board/board_uart.h>
#include <board/board_adc.h>
#include "dmx.h"

float fast_sin(float x)
{
    if (x < 0.5f)
    {
        return -16.0f*x*x + 8.0f*x;
    }
    else
    {
        return 16.0f*x*x - 24.0f*x + 8.0f;
    }
};

uint8_t led_sin(float x) {
    float sin = fast_sin(x);
    return (sin + 1) / 2 * 255;
}

dmx_mode_t mode = AUTO_FADE;

void dmx_set_mode(dmx_mode_t m) {
    mode = m;
}

float r = 0.75;
float g = 0.75;
float b = 0.75;

static THD_WORKING_AREA(dmx_thread_wa, 128);
static THD_FUNCTION(dmx_thread, arg) {
    (void)arg;

    chRegSetThreadName("dmx");

    while(1) {
        chThdSleepMilliseconds(20);

        switch (mode) {
            case MANUAL_RGB:
                uart_values[1] = adc_get_value(0);
                uart_values[2] = adc_get_value(1);
                uart_values[3] = adc_get_value(2);
                uart_values[4] = adc_get_value(3);
                uart_values[5] = adc_get_value(4);
                /*dmx_set_r(adc_get_value(0));
                dmx_set_g(adc_get_value(1));
                dmx_set_b(adc_get_value(2));
                dmx_set_pan(adc_get_value(3));
                dmx_set_tilt(adc_get_value(4));*/
                break;
            case AUTO_FADE:
                r += 0.0002;
                g += 0.0005;
                b += 0.0010;
                if (r > 1) r -= 1;
                if (g > 1) g -= 1;
                if (b > 1) b -= 1;
                dmx_set_r(led_sin(r));
                dmx_set_g(led_sin(g));
                dmx_set_b(led_sin(b));
                break;

        }

        uart_send();
    }
}

void dmx_start_thread() {
    chThdCreateStatic(dmx_thread_wa, sizeof(dmx_thread_wa), NORMALPRIO+1, dmx_thread, NULL);
}

void dmx_set_r(uint8_t r) {
    uart_values[3] = r;
}

void dmx_set_g(uint8_t g) {
    uart_values[4] = g;
}

void dmx_set_b(uint8_t b) {
    uart_values[5] = b;
}

void dmx_set_tilt(uint8_t tilt) {
    uart_values[1] = tilt;
}

void dmx_set_pan(uint8_t pan) {
    uart_values[2] = pan;
}