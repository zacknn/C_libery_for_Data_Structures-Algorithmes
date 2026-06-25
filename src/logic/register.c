#include "logic/register.h"

void Register_init(Register_t *reg) {
    for (int i = 0; i < 16; i++) {
        Bit_init(&reg->bits[i]);
    }
    reg->out = 0;
}

void Register_clock(Register_t *reg, uint16_t in, int load) {
    load = load ? 1 : 0;
    uint16_t new_out = 0;
    
    for (int i = 0; i < 16; i++) {
        int in_bit = (in >> i) & 1;
        Bit_clock(&reg->bits[i], in_bit, load);
        int out_bit = Bit_read_int(&reg->bits[i]);
        if (out_bit) {
            new_out |= (1 << i);
        }
    }
    
    reg->out = new_out;
}

uint16_t Register_read(Register_t *reg) {
    return reg->out;
}