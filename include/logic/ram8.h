#ifndef RAM8_H
#define RAM8_H

#include <stdint.h>
#include <stdbool.h>
#include "logic/register.h"

/**
 * RAM8 - Memory with 8 registers, each 16-bit wide
 * 
 * Behavior:
 * - Read: set address, read from out
 * - Write: set address, set in, set load=1
 * - Only the selected register is written to
 * - All other registers maintain their state
 * 
 * Address size: 3 bits (2³ = 8 registers)
 */

typedef struct {
    Register_t registers[8];
    uint16_t out;
} RAM8_t;

// Initialize the RAM (all registers to 0)
void RAM8_init(RAM8_t *ram);

// Clock the RAM
// in: 16-bit input value
// load: if 1, write to selected register
// address: 3-bit address (0-7)
void RAM8_clock(RAM8_t *ram, uint16_t in, int load, uint16_t address[3]);

// Read the current output (value at selected address)
uint16_t RAM8_read(RAM8_t *ram);

// Helper: Read a specific register (for testing)
uint16_t RAM8_read_register(RAM8_t *ram, int index);

#endif // RAM8_H