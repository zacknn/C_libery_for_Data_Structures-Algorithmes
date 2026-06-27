#include "logic/ram8.h"
#include "logic/logic_gates.h"
#include <stdint.h>
#include <stdbool.h>

void RAM8_init(RAM8_t *ram) {
    for (int i = 0; i < 8; i++) {
        Register_init(&ram->registers[i]);
    }
    ram->out = 0;
}

void RAM8_clock(RAM8_t *ram, uint16_t in, int load, uint16_t address[3]) {
    // Force load to 0 or 1
    load = load ? 1 : 0;
    
    // Convert 3-bit address to integer (0-7)
    int addr = address[0] | (address[1] << 1) | (address[2] << 2);
    
    // DMux8Way: send load signal to ONLY the selected register
    int load_signals[8];
    DMux8Way(load, address, 
             &load_signals[0], &load_signals[1], 
             &load_signals[2], &load_signals[3],
             &load_signals[4], &load_signals[5],
             &load_signals[6], &load_signals[7]);
    
    // Update all registers (only selected one gets load=1)
    for (int i = 0; i < 8; i++) {
        Register_clock(&ram->registers[i], in, load_signals[i]);
    }
    
    // Read the selected register directly using a switch statement
    // This avoids the complexity of Mux8Way16 with arrays
    switch (addr) {
        case 0: ram->out = Register_read(&ram->registers[0]); break;
        case 1: ram->out = Register_read(&ram->registers[1]); break;
        case 2: ram->out = Register_read(&ram->registers[2]); break;
        case 3: ram->out = Register_read(&ram->registers[3]); break;
        case 4: ram->out = Register_read(&ram->registers[4]); break;
        case 5: ram->out = Register_read(&ram->registers[5]); break;
        case 6: ram->out = Register_read(&ram->registers[6]); break;
        case 7: ram->out = Register_read(&ram->registers[7]); break;
        default: ram->out = 0; break;
    }
}

uint16_t RAM8_read(RAM8_t *ram) {
    return ram->out;
}

uint16_t RAM8_read_register(RAM8_t *ram, int index) {
    if (index >= 0 && index < 8) {
        return Register_read(&ram->registers[index]);
    }
    return 0;
}