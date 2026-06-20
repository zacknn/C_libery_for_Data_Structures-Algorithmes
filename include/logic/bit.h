#ifndef BIT_H
#define BIT_H

#include <stdint.h>
#include <stdbool.h>

/**
 * 1-Bit Register
 * Stores one bit of data
 * 
 * Behavior:
 * - if load = 1: stores the input value
 * - if load = 0: keeps the current value
 */

typedef struct {
    bool out;  // Current stored value
} Bit_t;

// Initialize the bit register
void Bit_init(Bit_t *bit);

// Clock the bit register
// in: input value (0 or 1)
// load: if 1, store the input; if 0, keep current value
void Bit_clock(Bit_t *bit, int in, int load);

// Read the current value
bool Bit_read(Bit_t *bit);

// Read as int (0 or 1)
int Bit_read_int(Bit_t *bit);

#endif // BIT_H