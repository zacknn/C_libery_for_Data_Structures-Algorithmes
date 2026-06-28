#ifndef RAM64_H
#define RAM64_H

#include <stdint.h>
#include <stdbool.h>
#include "logic/ram8.h"

/**
 * RAM64 - Memory with 64 registers, each 16-bit wide
 * 
 * Built from 8 RAM8 chips
 * Address size: 6 bits (2^6 = 64 registers)
 *   - Lower 3 bits: select register inside RAM8
 *   - Upper 3 bits: select which RAM8
 */

typedef struct {
    RAM8_t ram8s[8];
    uint16_t out;
} RAM64_t;

// Initialize the RAM (all registers to 0)
void RAM64_init(RAM64_t *ram);

// Clock the RAM
// in: 16-bit input value
// load: if 1, write to selected register
// address: 6-bit address (0-63)
void RAM64_clock(RAM64_t *ram, uint16_t in, int load, uint16_t address[6]);

// Read the current output (value at selected address)
uint16_t RAM64_read(RAM64_t *ram);

// Helper: Read a specific register directly (for testing)
// index: 0-63
uint16_t RAM64_read_register(RAM64_t *ram, int index);

#endif // RAM64_H
