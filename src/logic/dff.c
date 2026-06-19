#include "logic/dff.h"
#include <stdint.h>
#include <stdbool.h>

// Static state - remembers between function calls
static uint16_t dff_state = 0;

void DFF_reset(void) {
    dff_state = 0;
}

int DFF(int in) {
    // Force input to be 0 or 1
    in = in ? 1 : 0;
    
    // Output what was stored (previous state)
    int previous_out = dff_state;
    
    // Store current input for next cycle
    dff_state = in;
    
    return previous_out;
}

int DFF_peek(void) {
    return dff_state;
}

bool DFF_peek_bool(void) {
    return dff_state ? true : false;
}