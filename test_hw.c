//
// Created by esa on 4.5.2016.
//

#include <board/board_btn.h>
#include <board/board_adc.h>
#include <stdlib.h>
#include "test_hw.h"
#include "lcd.h"

void test_buttons() {
    if(get_btn_up()) {
        lcd_putstr("UP");
    }

    if(get_btn_left()) {
        lcd_putstr("LEFT");
    }

    if(get_btn_right()) {
        lcd_putstr("RIGHT");
    }

    if(get_btn_down()) {
        lcd_putstr("DOWN");
    }

    if(get_btn_1()) {
        lcd_putstr("1");
    }

    if(get_btn_2()) {
        lcd_putstr("2");
    }

    if(get_btn_3()) {
        lcd_putstr("3");
    }

    if(get_btn_4()) {
        lcd_putstr("4");
    }

    if(get_btn_5()) {
        lcd_putstr("5");
    }
}

void print_slider(uint8_t sliderN) {
    char buf[10];
    itoa(sliderN+1, buf, 10);
    lcd_putstr("Slider ");
    lcd_putstr(buf);
    lcd_putstr(": ");
    itoa(adc_get_value(sliderN), buf, 10);
    lcd_putstr(buf);
}

void test_sliders() {
    static uint8_t values[5];
    static bool initialized = false;
    static uint8_t lastChanged = 99;
    int i;
    for(i = 0; i < 5; i++) {
        if (!initialized) {
            values[i] = adc_get_value(i);
            if(i == 4) initialized = true;
        } else {
            if(abs(values[i] - adc_get_value(i)) > 3) {
                lastChanged = i;
                values[i] = adc_get_value(i);
            }
        }
    }

    if(lastChanged < 10) {
        print_slider(lastChanged);
    }
}