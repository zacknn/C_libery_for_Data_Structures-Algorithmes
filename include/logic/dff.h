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

// Initialize/reset the DFF state
void DFF_reset(void);

// Clock the DFF: returns previous state, stores input for next cycle
int DFF(int in);

// Get current state without advancing clock
int DFF_peek(void);

// Get current state as boolean
bool DFF_peek_bool(void);

#endif // DFF_H