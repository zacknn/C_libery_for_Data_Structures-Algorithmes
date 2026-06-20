#include "logic/bit.h"
#include "logic/dff.h"
#include "logic/logic_gates.h"
#include <stdint.h>
#include <stdbool.h>

void Bit_init(Bit_t *bit) {
    bit->out = false;
    DFF_reset();
}

void Bit_clock(Bit_t *bit, int in, int load) {
    // Force inputs to 0 or 1
    in = in ? 1 : 0;
    load = load ? 1 : 0;
    
    // MUX: if load=1, use 'in'; if load=0, use 'out' (feedback)
    int current_out = bit->out ? 1 : 0;
    int mux_out = Mux(current_out, in, load);
    
    // DFF: store the mux output
    int new_out = DFF(mux_out);
    
    // Update the bit's output
    bit->out = new_out ? true : false;
}

bool Bit_read(Bit_t *bit) {
    return bit->out;
}

int Bit_read_int(Bit_t *bit) {
    return bit->out ? 1 : 0;
}