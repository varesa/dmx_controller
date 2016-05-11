//
// Created by esa on 4.5.2016.
//

#include "board_btn.h"
#include "board.h"
#include "hal.h"


bool get_btn_up() {
    return !palReadPad(BTN_DIR_GPIO, BTN_UP);
}

bool get_btn_left() {
    return !palReadPad(BTN_DIR_GPIO, BTN_LEFT);
}

bool get_btn_right() {
    return !palReadPad(BTN_DIR_GPIO, BTN_RIGHT);
}

bool get_btn_down() {
    return !palReadPad(BTN_DIR_GPIO, BTN_DOWN);
}

bool get_btn_1() {
    return !palReadPad(BTN_123_GPIO, BTN_1);
}

bool get_btn_2() {
    return !palReadPad(BTN_123_GPIO, BTN_2);
}

bool get_btn_3() {
    return !palReadPad(BTN_123_GPIO, BTN_3);
}

bool get_btn_4() {
    return !palReadPad(BTN_45_GPIO, BTN_4);
}

bool get_btn_5() {
    return !palReadPad(BTN_45_GPIO, BTN_5);
}

