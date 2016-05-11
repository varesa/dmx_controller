//
// Created by esa on 5.5.2016.
//

#ifndef ARM_ETHERNETBOARD_MEDIAN_H
#define ARM_ETHERNETBOARD_MEDIAN_H

//
// Created by esa on 5.5.2016.
//

#include "median.h"
#include <stdint.h>


uint16_t select(uint16_t *a, uint16_t i, uint16_t n);
void insertion_sort(uint16_t *a, uint16_t n);
uint16_t partition(uint16_t *a, uint16_t n, uint16_t x);

#endif //ARM_ETHERNETBOARD_MEDIAN_H
