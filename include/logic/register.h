#ifndef REGISTER_H
#define REGISTER_H

#include <stdint.h>
#include <stdbool.h>
#include "logic/bit.h"

/**
 * 16-Bit Register
 * Stores 16 bits of data
 * 
 * Behavior:
 * - if load = 1: stores the 16-bit input value
 * - if load = 0: keeps the current value
 */

typedef struct {
    Bit_t bits[16];
    uint16_t out;
} Register_t;

// Initialize the register
void Register_init(Register_t *reg);

// Clock the register
// in: 16-bit input value
// load: if 1, store the input; if 0, keep current value
void Register_clock(Register_t *reg, uint16_t in, int load);

// Read the current 16-bit value
uint16_t Register_read(Register_t *reg);

#endif // REGISTER_H