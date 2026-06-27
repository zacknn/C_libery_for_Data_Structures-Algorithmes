#include "logic/bit.h"
#include "logic/logic_gates.h"

void Bit_init(Bit_t *bit) {
    DFF_init(&bit->dff);
    bit->out = false;
}

void Bit_clock(Bit_t *bit, int in, int load) {
    in = in ? 1 : 0;
    load = load ? 1 : 0;
    
    int current_state = DFF_peek(&bit->dff);
    int mux_out = Mux(current_state, in, load);
    int new_out = DFF_clock(&bit->dff, mux_out);
    bit->out = new_out ? true : false;
}

bool Bit_read(Bit_t *bit) {
    return bit->out;
}

int Bit_read_int(Bit_t *bit) {
    return bit->out ? 1 : 0;
}