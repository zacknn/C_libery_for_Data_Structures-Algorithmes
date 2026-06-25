#include "logic/dff.h"
#include <stdint.h>
#include <stdbool.h>

void DFF_init(DFF_t *dff) {
    dff->state = 0;
}

int DFF_clock(DFF_t *dff, int in) {
    in = in ? 1 : 0;
    int previous_out = dff->state;
    dff->state = in;
    return previous_out;
}

int DFF_peek(DFF_t *dff) {
    return dff->state;
}