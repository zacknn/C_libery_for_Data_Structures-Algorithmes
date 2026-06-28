#include "logic/ram64.h"
#include "logic/logic_gates.h"
#include <stdint.h>
#include <stdbool.h>

void RAM64_init(RAM64_t *ram) {
    for (int i = 0; i < 8; i++) {
        RAM8_init(&ram->ram8s[i]);
    }
    ram->out = 0;
}

void RAM64_clock(RAM64_t *ram, uint16_t in, int load, uint16_t address[6]) {
    load = load ? 1 : 0;

    // Lower 3 bits: address inside each RAM8
    uint16_t addr_low[3] = {address[0], address[1], address[2]};

    // Upper 3 bits: select which RAM8
    uint16_t addr_high[3] = {address[3], address[4], address[5]};

    // DMux8Way: send load signal to ONLY the selected RAM8
    int load_signals[8];
    DMux8Way(load, addr_high,
             &load_signals[0], &load_signals[1],
             &load_signals[2], &load_signals[3],
             &load_signals[4], &load_signals[5],
             &load_signals[6], &load_signals[7]);

    // Clock all 8 RAM8s (only selected one gets load=1)
    for (int i = 0; i < 8; i++) {
        RAM8_clock(&ram->ram8s[i], in, load_signals[i], addr_low);
    }

    // Select output from the addressed RAM8
    int ram8_index = addr_high[0] | (addr_high[1] << 1) | (addr_high[2] << 2);

    switch (ram8_index) {
        case 0: ram->out = RAM8_read(&ram->ram8s[0]); break;
        case 1: ram->out = RAM8_read(&ram->ram8s[1]); break;
        case 2: ram->out = RAM8_read(&ram->ram8s[2]); break;
        case 3: ram->out = RAM8_read(&ram->ram8s[3]); break;
        case 4: ram->out = RAM8_read(&ram->ram8s[4]); break;
        case 5: ram->out = RAM8_read(&ram->ram8s[5]); break;
        case 6: ram->out = RAM8_read(&ram->ram8s[6]); break;
        case 7: ram->out = RAM8_read(&ram->ram8s[7]); break;
        default: ram->out = 0; break;
    }
}

uint16_t RAM64_read(RAM64_t *ram) {
    return ram->out;
}

uint16_t RAM64_read_register(RAM64_t *ram, int index) {
    if (index < 0 || index >= 64) {
        return 0;
    }
    int ram8_index = index / 8;
    int reg_index = index % 8;
    return RAM8_read_register(&ram->ram8s[ram8_index], reg_index);
}
