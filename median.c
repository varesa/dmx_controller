//
// Created by esa on 5.5.2016.
//

#include <stdint.h>
#include "median.h"

#define min(a,b) \
   ({ __typeof__ (a) _a = (a); \
       __typeof__ (b) _b = (b); \
     _a > _b ? _b : _a; })

uint16_t  select(uint16_t  *a, uint16_t i, uint16_t n)
// Select the ith element (indexed from 0) from the array of length n
// using the median of medians algorithm
// https://en.wikipedia.org/wiki/Median_of_medians
{
    if(n == 1) {
        return a[0];
    }

    uint16_t n_meds = 0;
    int x;
    for(x = 0; x < n; x += 5) {
        uint16_t l = min(5, n - x);
        insertion_sort(a + x, l);
        uint16_t tmp = a[x/5];
        a[x/5] = a[x + l/2];
        a[x + l/2] = tmp;
        n_meds++;
    }

    uint16_t median_of_medians;
    if(n_meds > 1) {
        median_of_medians = select(a, n_meds/2, n_meds);
    }
    else {
        median_of_medians = a[0];
    }

    uint16_t k = partition(a, n, median_of_medians);

    if(k == i) {
        return median_of_medians;
    }
    else if (i < k) {
        return select(a, i, k);
    }
    else {
        return select(a + k, i - k, n - k);
    }
}


void insertion_sort( uint16_t  *a, uint16_t n)
// Insertion sort array a of length n
{
    int j;
    for(j = 1; j < n; j++) {
        uint16_t key = a[j];
        // insert a[j] in the correct position a[0...(j-1)]
        int i = j - 1;
        while ((i >= 0) && (a[i] > key)) {
            a[i + 1] = a[i];
            i--;
        }
        a[i+1] = key;
    }
}


uint16_t  partition(uint16_t *a, uint16_t n, uint16_t x)
// Partition array a of length n around x;
// Return the number of elements to the left of the pivot.
{
    // First find the pivot and place at the end
    int i;
    for(i = 0; i < n; i++) {
        if(a[i] == x) {
            a[i] = a[n-1];
            a[n-1] = x;
        }
    }

    i = 0;
    int j;
    for(j = 0; j < (n-1); j++) {
        if(a[j] <= x) {
            uint16_t tmp = a[j];
            a[j] = a[i];
            a[i] = tmp;
            i++;
        }
    }

    // Place the pivot in the correct position
    a[n-1] = a[i];
    a[i] = x;

    return i;
}