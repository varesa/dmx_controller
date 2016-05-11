//
// Created by esa on 5.5.2016.
//

#include "hal.h"

#include "board_uart.h"


static virtual_timer_t vt1, vt2;

static void restart(void *p) {

    (void)p;

    /*chSysLockFromISR();
    uartStartSendI(&UARTD2, 14, "Hello World!\r\n");
    chSysUnlockFromISR();*/
}

static void ledoff(void *p) {

    (void)p;

    //palSetPad(IOPORT3, GPIOC_LED);
}

/*
 * This callback is invoked when a transmission buffer has been completely
 * read by the driver.
 */
static void txend1(UARTDriver *uartp) {

    (void)uartp;

    //palClearPad(IOPORT3, GPIOC_LED);
}

/*
 * This callback is invoked when a transmission has physically completed.
 */
static void txend2(UARTDriver *uartp) {

    (void)uartp;

    /*palSetPad(IOPORT3, GPIOC_LED);
    chSysLockFromISR();
    chVTResetI(&vt1);
    chVTDoSetI(&vt1, MS2ST(5000), restart, NULL);
    chSysUnlockFromISR();*/
}

/*
 * This callback is invoked on a receive error, the errors mask is passed
 * as parameter.
 */
static void rxerr(UARTDriver *uartp, uartflags_t e) {

    (void)uartp;
    (void)e;
}

/*
 * This callback is invoked when a character is received but the application
 * was not ready to receive it, the character is passed as parameter.
 */
static void rxchar(UARTDriver *uartp, uint16_t c) {

    (void)uartp;
    (void)c;

    /* Flashing the LED each time a character is received.*/
    /*palClearPad(IOPORT3, GPIOC_LED);
    chSysLockFromISR();
    chVTResetI(&vt2);
    chVTDoSetI(&vt2, MS2ST(200), ledoff, NULL);
    chSysUnlockFromISR();*/
}

/*
 * This callback is invoked when a receive buffer has been completely written.
 */
static void rxend(UARTDriver *uartp) {

    (void)uartp;
}

/*
 * UART driver configuration structure.
 */
static UARTConfig uart_cfg_1 = {
        txend1,
        txend2,
        rxend,
        rxchar,
        rxerr,
        9600,
        0,
        0,
        0
};

void uart_init() {
    /*
 * Activates the serial driver 2 using the driver default configuration.
 */
    uartStart(&UARTD1, &uart_cfg_1);
}

uint8_t uart_values[12] = {
        1,
        0,
        0,
        0,
        5,
        127,
        0,
        0,
        0,
        0,
        0,
        0,
};

void uart_send() {
    /*
     * Starts the transmission, it will be handled entirely in background.
     */
    uartStartSend(&UARTD1, 12, uart_values);
}