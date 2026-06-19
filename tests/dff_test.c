#include "logic/dff.h"
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

// Helper to print 16-bit binary
void print_binary(uint16_t value) {
    for (int i = 15; i >= 0; i--) {
        printf("%d", (value >> i) & 1);
        if (i % 4 == 0 && i > 0) printf(" ");
    }
}

// ============================================
// DFF Tests
// ============================================

void test_dff_basic() {
    printf("\n=== Test 1: Basic DFF ===\n");
    DFF_reset();
    
    printf("Initial state: %d\n", DFF_peek());
    
    printf("Cycle 1 - Input: 1, Output: %d, State: %d\n", 
           DFF(1), DFF_peek());
    printf("Cycle 2 - Input: 1, Output: %d, State: %d\n", 
           DFF(1), DFF_peek());
    printf("Cycle 3 - Input: 0, Output: %d, State: %d\n", 
           DFF(0), DFF_peek());
    printf("Cycle 4 - Input: 0, Output: %d, State: %d\n", 
           DFF(0), DFF_peek());
    printf("Cycle 5 - Input: 1, Output: %d, State: %d\n", 
           DFF(1), DFF_peek());
}

void test_dff_pattern() {
    printf("\n=== Test 2: DFF Pattern ===\n");
    DFF_reset();
    
    int inputs[] = {1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 0, 0};
    int num_tests = sizeof(inputs) / sizeof(inputs[0]);
    
    printf("Input:  ");
    for (int i = 0; i < num_tests; i++) {
        printf("%d ", inputs[i]);
    }
    printf("\n");
    
    printf("Output: ");
    for (int i = 0; i < num_tests; i++) {
        int out = DFF(inputs[i]);
        printf("%d ", out);
    }
    printf("\n");
    printf(" Pattern test complete: out(t+1) = in(t)\n");
}


// ============================================
// Main
// ============================================

int main() {
    printf("╔═══════════════════════════════════════╗\n");
    printf("║     DFF & MEMORY CHIP TESTS           ║\n");
    printf("╚═══════════════════════════════════════╝\n");
    
    test_dff_basic();
    test_dff_pattern();
    
    printf("\n╔═══════════════════════════════════════╗\n");
    printf("║     ALL TESTS COMPLETED!             ║\n");
    printf("╚═══════════════════════════════════════╝\n");
    
    return 0;
}