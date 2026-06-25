#include "logic/bit.h"
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

// ============================================
// Bit Tests
// ============================================

void test_bit_basic() {
    printf("\n=== Test 3: 1-Bit Register ===\n");
    Bit_t bit;
    Bit_init(&bit);
    
    printf("Initial value: %d\n", Bit_read_int(&bit));
    
    // DFF-backed bit register is one-cycle delayed.
    Bit_clock(&bit, 1, 1);
    printf("Cycle 1 load 1 -> out: %d (expected: 0)\n", Bit_read_int(&bit));
    
    Bit_clock(&bit, 0, 0);
    printf("Cycle 2 keep 0 -> out: %d (expected: 1)\n", Bit_read_int(&bit));
    
    Bit_clock(&bit, 0, 1);
    printf("Cycle 3 load 0 -> out: %d (expected: 0)\n", Bit_read_int(&bit));
    
    Bit_clock(&bit, 1, 0);
    printf("Cycle 4 keep 1 -> out: %d (expected: 0)\n", Bit_read_int(&bit));
}

void test_bit_sequence() {
    printf("\n=== Test 4: Bit Register Sequence ===\n");
    Bit_t bit;
    Bit_init(&bit);
    
    // Test sequence
    // The bit has a one-cycle delay because of DFF
    int inputs[] = {1, 0, 0, 1, 1, 0, 1, 0};
    int loads[] =  {1, 0, 1, 0, 1, 0, 1, 0};
    // Expected: out(t+1) = in(t) when load=1, else out(t+1) = out(t)
    int expected[] = {0, 1, 0, 0, 0, 1, 0, 1};
    
    printf("Step | In | Load | Out | Expected | Status\n");
    printf("-----|----|------|-----|----------|-------\n");
    
    for (int i = 0; i < 8; i++) {
        Bit_clock(&bit, inputs[i], loads[i]);
        int out = Bit_read_int(&bit);
        
        char *status = (out == expected[i]) ? "yes" : "no";
        
        printf("  %d  | %d  |  %d   |  %d  |    %d    |  %s\n",
               i, inputs[i], loads[i], out, expected[i], status);
    }
}

int main() {
    test_bit_basic();
    test_bit_sequence();
    return 0;
}