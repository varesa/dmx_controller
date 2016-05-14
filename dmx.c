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

uint8_t x_pos(float x) {
    float sin = (fast_sin(x) + 1) / 2;
    return 125 + sin * 10;
}

uint8_t y_pos(float x) {
    float sin = (fast_sin(x) + 1) / 2;
    return 30 + sin * 18;
}

dmx_mode_t mode = AUTO_FADE;

void dmx_set_mode(dmx_mode_t m) {
    mode = m;
}

float r = 0.75;
float g = 0.75;
float b = 0.75;

float tilt = 30;
int tilt_dir = 1;
float pan = 132;
int pan_dir = 1;

static THD_WORKING_AREA(dmx_thread_wa, 128);
static THD_FUNCTION(dmx_thread, arg) {
    (void)arg;

    chRegSetThreadName("dmx");

    while(1) {
        chThdSleepMilliseconds(100); // 20

        uint8_t speed;

        switch (mode) {
            case MANUAL_RGB:
                dmx_set_r(adc_get_value(0));
                dmx_set_g(adc_get_value(1));
                dmx_set_b(adc_get_value(2));
                break;
            case MANUAL_RGB2:
                dmx_set_pan(adc_get_value(0));
                dmx_set_tilt(adc_get_value(1));
                dmx_set_color(adc_get_value(2));
                dmx_set_strobe(6);
                dmx_set_dim(adc_get_value(3));
                dmx_set_gobo(adc_get_value(4));
                break;
            case AUTO_FADE:
                speed = adc_get_value(0);
                r += 0.0002 * speed;
                g += 0.0005 * speed;
                b += 0.0010 * speed;
                if (r > 1) r -= 1;
                if (g > 1) g -= 1;
                if (b > 1) b -= 1;

                if(pan > 140) pan_dir = -1;
                if(pan < 125) pan_dir = 1;

                if(tilt > 55) tilt_dir = -1;
                if(tilt < 30) tilt_dir = 1;

                tilt += tilt_dir;
                pan += pan_dir;

                dmx_set_r(led_sin(r));
                dmx_set_g(led_sin(g));
                dmx_set_b(led_sin(b));
                
                dmx_set_pan(pan);
                dmx_set_tilt(tilt);

                dmx_set_color(adc_get_value(2));
                dmx_set_strobe(6);
                dmx_set_dim(adc_get_value(3));
                dmx_set_gobo(adc_get_value(4));
                break;

        }

        uart_send();
    }
}

void dmx_start_thread() {
    chThdCreateStatic(dmx_thread_wa, sizeof(dmx_thread_wa), NORMALPRIO+1, dmx_thread, NULL);
}

void dmx_set_r(uint8_t r) {
    uart_values[1] = r;
}

void dmx_set_g(uint8_t g) {
    uart_values[2] = g;
}

void dmx_set_b(uint8_t b) {
    uart_values[3] = b;
}

void dmx_set_tilt(uint8_t tilt) {
    uart_values[5] = tilt;
}

void dmx_set_pan(uint8_t pan) {
    uart_values[4] = pan;
}

void dmx_set_color(uint8_t color) {
    uart_values[6] = color;
}

void dmx_set_strobe(uint8_t strobe) {
    uart_values[7] = strobe;
}

void dmx_set_dim(uint8_t dim) {
    uart_values[8] = dim;
}

void dmx_set_gobo(uint8_t gobo) {
    uart_values[9] = gobo;
}