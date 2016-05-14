//
// Created by esa on 5.5.2016.
//

#ifndef ARM_ETHERNETBOARD_BOARD_UART_H
#define ARM_ETHERNETBOARD_BOARD_UART_H

#include "stdint.h"

extern uint8_t uart_values[10];

void uart_init();
void uart_send();

#endif //ARM_ETHERNETBOARD_BOARD_UART_H
