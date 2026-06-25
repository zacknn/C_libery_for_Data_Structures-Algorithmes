#include "logic/dff.h"
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

// ============================================
// DFF Tests
// ============================================

void test_dff_basic() {
    printf("=== Test 1: Basic DFF ===\n");
    DFF_t dff;
    DFF_init(&dff);

    printf("Initial state: %d\n", DFF_peek(&dff));

    int out1 = DFF_clock(&dff, 1);
    printf("Cycle 1 - Input: 1, Output: %d, State: %d\n", out1, DFF_peek(&dff));

    int out2 = DFF_clock(&dff, 1);
    printf("Cycle 2 - Input: 1, Output: %d, State: %d\n", out2, DFF_peek(&dff));

    int out3 = DFF_clock(&dff, 0);
    printf("Cycle 3 - Input: 0, Output: %d, State: %d\n", out3, DFF_peek(&dff));

    int out4 = DFF_clock(&dff, 0);
    printf("Cycle 4 - Input: 0, Output: %d, State: %d\n", out4, DFF_peek(&dff));

    int out5 = DFF_clock(&dff, 1);
    printf("Cycle 5 - Input: 1, Output: %d, State: %d\n", out5, DFF_peek(&dff));
}

void test_dff_pattern() {
    printf("=== Test 2: DFF Pattern ===\n");
    DFF_t dff;
    DFF_init(&dff);

    int inputs[] = {1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 0, 0};
    int num_tests = sizeof(inputs) / sizeof(inputs[0]);

    printf("Input:  ");
    for (int i = 0; i < num_tests; i++) {
        printf("%d ", inputs[i]);
    }
    printf("\n");

    printf("Output: ");
    for (int i = 0; i < num_tests; i++) {
        int out = DFF_clock(&dff, inputs[i]);
        printf("%d ", out);
    }
    printf("\n");
    printf("Pattern test complete: out(t+1) = in(t)\n");
}

int main() {
    printf("╔═══════════════════════════════════════╗\n");
    printf("║                 DFF                   ║\n");
    printf("╚═══════════════════════════════════════╝\n");

    test_dff_basic();
    test_dff_pattern();
    return 0;
}
