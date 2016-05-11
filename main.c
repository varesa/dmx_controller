//
// Created by esa on 2/1/16.
//

#include <stdbool.h>
#include <hal.h>
#include <board/board_btn.h>
#include <board/board_adc.h>
#include <stdlib.h>
#include <board/board_uart.h>
#include "lcd.h"
#include "test_hw.h"
#include "dmx.h"

/*
 * Blinker thread #1.
 */
static THD_WORKING_AREA(waThread1, 128);

static THD_FUNCTION(Thread1, arg) {

    (void)arg;

    chRegSetThreadName("blinker");
    while (true) {
        dbg_print("Blink!\n");
        palSetPad(GPIOA, GPIO_LED);
        chThdSleepMilliseconds(1000);
        palClearPad(GPIOA, GPIO_LED);
        chThdSleepMilliseconds(1000);
    }
}


int main() {
    halInit();
    chSysInit();

    chRegSetThreadName("main");

    dbg_init();
    dbg_print("\n\nReboot\n\n");

    lcd_init();
    adc_init();

    uart_init();
    dmx_start_thread();

    chThdCreateStatic(waThread1, sizeof(waThread1), NORMALPRIO+1, Thread1, NULL);

    lcd_goto_rc(0, 0);
    while(1) {
        lcd_clr_display();

        lcd_goto_rc(0, 0);
        test_buttons();

        lcd_goto_rc(1, 0);
        test_sliders();

        chThdSleepMilliseconds(10);
    }

    while(1) {
        chThdSleepSeconds(1);
    }
}



void exit(int a) {
    while(true) {

    }
}