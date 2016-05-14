//
// Created by esa on 5.5.2016.
//

#include <stdint.h>
#include <ch.h>

#ifndef ARM_ETHERNETBOARD_DMX_H
#define ARM_ETHERNETBOARD_DMX_H

typedef enum {
    MANUAL_RGB,
    MANUAL_RGB2,
    AUTO_FADE
} dmx_mode_t;

void dmx_set_mode(dmx_mode_t mode);

void dmx_set_r(uint8_t r);
void dmx_set_g(uint8_t g);
void dmx_set_b(uint8_t b);

void dmx_set_tilt(uint8_t tilt);
void dmx_set_pan(uint8_t pan);
void dmx_set_color(uint8_t color);
void dmx_set_strobe(uint8_t strobe);
void dmx_set_dim(uint8_t dim);
void dmx_set_gobo(uint8_t gobo);

void dmx_start_thread();

#endif //ARM_ETHERNETBOARD_DMX_H
