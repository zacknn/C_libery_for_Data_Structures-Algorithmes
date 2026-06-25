#ifndef DFF_H
#define DFF_H

#include <stdint.h>
#include <stdbool.h>

/**
 * Data Flip-Flop (DFF)
 * Implements: out(t+1) = in(t)
 * 
 * The DFF stores one bit of state and outputs the previously stored value.
 * Each call to DFF() advances the clock by one cycle.
 */

// DFF structure - each instance has its own state
typedef struct {
    uint16_t state;
} DFF_t;

// Initialize a DFF
void DFF_init(DFF_t *dff);

// Clock the DFF: returns previous state, stores input
int DFF_clock(DFF_t *dff, int in);

// Peek at current state
int DFF_peek(DFF_t *dff);

#endif // DFF_H