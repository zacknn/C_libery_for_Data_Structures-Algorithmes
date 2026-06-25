#include "logic/dff.h"
#include "logic/bit.h"
#include "logic/register.h"
#include <stdio.h>
#include <stdint.h>

void print_binary(uint16_t value) {
    for (int i = 15; i >= 0; i--) {
        printf("%d", (value >> i) & 1);
        if (i % 4 == 0 && i > 0) printf(" ");
    }
}

void test_register() {
    printf("\n=== Test: 16-Bit Register ===\n");
    Register_t reg;
    Register_init(&reg);
    
    printf("Initial: %u (0x%04X) - ", Register_read(&reg), Register_read(&reg));
    print_binary(Register_read(&reg));
    printf("\n");
    
    // Load 42
    Register_clock(&reg, 42, 1);
    printf("Load 42:  %u (0x%04X) - ", Register_read(&reg), Register_read(&reg));
    print_binary(Register_read(&reg));
    printf("\n");
    
    // Keep value (load=0)
    Register_clock(&reg, 100, 0);
    printf("Keep:     %u (0x%04X) - ", Register_read(&reg), Register_read(&reg));
    print_binary(Register_read(&reg));
    printf("\n");
    
    // Load 0xABCD
    Register_clock(&reg, 0xABCD, 1);
    printf("Load ABCD: %u (0x%04X) - ", Register_read(&reg), Register_read(&reg));
    print_binary(Register_read(&reg));
    printf("\n");
    
    // Load 0xAAAA
    Register_clock(&reg, 0xAAAA, 1);
    printf("Load AAAA: %u (0x%04X) - ", Register_read(&reg), Register_read(&reg));
    print_binary(Register_read(&reg));
    printf("\n");
    
    // Load 0x5555
    Register_clock(&reg, 0x5555, 1);
    printf("Load 5555: %u (0x%04X) - ", Register_read(&reg), Register_read(&reg));
    print_binary(Register_read(&reg));
    printf("\n");
}

int main() {
    printf("╔═══════════════════════════════════════╗\n");
    printf("║     REGISTER TESTS                   ║\n");
    printf("╚═══════════════════════════════════════╝\n");
    
    test_register();
    
    printf("\n╔═══════════════════════════════════════╗\n");
    printf("║     ALL TESTS COMPLETED!             ║\n");
    printf("╚═══════════════════════════════════════╝\n");
    
    return 0;
}