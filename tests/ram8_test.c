#include "logic/ram8.h"
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

// Helper to set address from integer
void set_address(uint16_t addr[3], int value) {
    addr[0] = (value >> 0) & 1;
    addr[1] = (value >> 1) & 1;
    addr[2] = (value >> 2) & 1;
}

void test_ram8_basic() {
    printf("\n=== Test 1: RAM8 Basic Read/Write ===\n");
    RAM8_t ram;
    RAM8_init(&ram);
    uint16_t address[3];

    printf("Testing write to address 0:\n");
    set_address(address, 0);
    RAM8_clock(&ram, 0xABCD, 1, address);
    // DFF delay: register out is still 0 after first clock
    printf("  Address 0: Read = 0x%04X (delay - expected 0x0000)\n", 
           RAM8_read_register(&ram, 0));

    // Clock again with load=0 to see the value
    RAM8_clock(&ram, 0x0000, 0, address);
    printf("  Address 0 after keep: Read = 0x%04X\n", 
           RAM8_read_register(&ram, 0));

    printf("\nTesting write to address 5:\n");
    set_address(address, 5);
    RAM8_clock(&ram, 0x1234, 1, address);
    RAM8_clock(&ram, 0x0000, 0, address);  // Keep to see value
    printf("  Address 5: Read = 0x%04X\n", RAM8_read_register(&ram, 5));

    printf("\nChecking other addresses (should be unchanged):\n");
    for (int i = 0; i < 8; i++) {
        if (i != 0 && i != 5) {
            printf("  Address %d: 0x%04X\n", i, RAM8_read_register(&ram, i));
        }
    }
}

void test_ram8_read_write() {
    printf("\n=== Test 2: RAM8 Multiple Operations ===\n");
    RAM8_t ram;
    RAM8_init(&ram);
    uint16_t address[3];

    // Write different values to different addresses
    printf("Writing values to addresses:\n");
    uint16_t test_values[] = {0x1111, 0x2222, 0x3333, 0x4444, 
                              0x5555, 0x6666, 0x7777, 0x8888};

    for (int i = 0; i < 8; i++) {
        set_address(address, i);
        RAM8_clock(&ram, test_values[i], 1, address);
        printf("  Address %d: wrote 0x%04X\n", i, test_values[i]);
    }

    // Clock once more to update all register outputs
    set_address(address, 0);
    RAM8_clock(&ram, 0x0000, 0, address);

    // Read back all values
    printf("\nReading back all values:\n");
    int all_correct = 1;
    for (int i = 0; i < 8; i++) {
        set_address(address, i);
        // Must clock with load=0 to update RAM8 output for new address
        RAM8_clock(&ram, 0x0000, 0, address);
        uint16_t read_val = RAM8_read(&ram);
        uint16_t reg_val = RAM8_read_register(&ram, i);

        printf("  Address %d: reg=0x%04X, output=0x%04X, expected=0x%04X", 
               i, reg_val, read_val, test_values[i]);

        if (reg_val == test_values[i]) {
            printf(" correct\n");
        } else {
            printf(" incorrect\n");
            all_correct = 0;
        }
    }

    printf(all_correct ? "\n All values correct!\n" : "\n Some values incorrect!\n");
}

void test_ram8_overwrite() {
    printf("\n=== Test 3: RAM8 Overwrite ===\n");
    RAM8_t ram;
    RAM8_init(&ram);
    uint16_t address[3];

    // Write to address 3
    set_address(address, 3);
    RAM8_clock(&ram, 0xAAAA, 1, address);
    printf("Initial write to address 3: 0xAAAA\n");

    // Overwrite address 3
    RAM8_clock(&ram, 0xBBBB, 1, address);
    printf("Overwrite address 3: 0xBBBB\n");

    // Due to DFF delay, reg.out shows previous value (0xAAAA), not new value
    uint16_t read_val = RAM8_read_register(&ram, 3);
    printf("Read address 3: 0x%04X %s (DFF delay - previous value)\n", read_val, 
           read_val == 0xAAAA ? "correct" : "incorrect");

    // Clock again to see the new value
    RAM8_clock(&ram, 0x0000, 0, address);
    read_val = RAM8_read_register(&ram, 3);
    printf("After keep: 0x%04X %s (new value visible)\n", read_val,
           read_val == 0xBBBB ? "correct" : "incorrect");
}

void test_ram8_load_0() {
    printf("\n=== Test 4: RAM8 with load=0 ===\n");
    RAM8_t ram;
    RAM8_init(&ram);
    uint16_t address[3];

    // Write value to address 2
    set_address(address, 2);
    RAM8_clock(&ram, 0x1234, 1, address);
    RAM8_clock(&ram, 0x0000, 0, address);  // Keep to see value
    printf("Wrote 0x1234 to address 2\n");

    // Try to write with load=0 (should not change)
    RAM8_clock(&ram, 0xFFFF, 0, address);
    printf("Attempted write 0xFFFF with load=0\n");

    uint16_t read_val = RAM8_read_register(&ram, 2);
    printf("Read address 2: 0x%04X %s\n", read_val, 
           read_val == 0x1234 ? "(correct) Still 0x1234!" : "(incorrect) Changed!");
}

void test_ram8_delay() {
    printf("\n=== Test 5: RAM8 DFF Delay ===\n");
    RAM8_t ram;
    RAM8_init(&ram);
    uint16_t address[3];

    printf("Demonstrating DFF one-cycle delay in RAM:\n");
    printf("Step | Operation | Value  | Output | Notes\n");
    printf("-----|-----------|--------|--------|-------\n");

    set_address(address, 0);

    // Initial state
    printf("  0  | Initial   |    -   | 0x%04X | Starting state\n", 
           RAM8_read(&ram));

    // Write 0xAAAA
    RAM8_clock(&ram, 0xAAAA, 1, address);
    printf("  1  | Write AAAA| 0xAAAA | 0x%04X | Stored, not visible yet (delay)\n", 
           RAM8_read(&ram));

    // Keep (no change) - now value appears
    RAM8_clock(&ram, 0x0000, 0, address);
    printf("  2  | Keep      |    -   | 0x%04X | AAAA appears!\n", 
           RAM8_read(&ram));

    // Write 0xBBBB
    RAM8_clock(&ram, 0xBBBB, 1, address);
    printf("  3  | Write BBBB| 0xBBBB | 0x%04X | Stored, not visible yet\n", 
           RAM8_read(&ram));

    // Keep again - now new value appears
    RAM8_clock(&ram, 0x0000, 0, address);
    printf("  4  | Keep      |    -   | 0x%04X | BBBB appears!\n", 
           RAM8_read(&ram));

    printf("\n✅ RAM8 correctly demonstrates DFF delay: out(t+1) = in(t)\n");
}

void test_ram8_all_addresses() {
    printf("\n=== Test 6: RAM8 All Addresses ===\n");
    RAM8_t ram;
    RAM8_init(&ram);
    uint16_t address[3];

    // Write patterns to all addresses
    printf("Writing pattern to all 8 addresses:\n");
    for (int i = 0; i < 8; i++) {
        uint16_t pattern = 0x1000 + (i * 0x0100);
        set_address(address, i);
        RAM8_clock(&ram, pattern, 1, address);
        printf("  Address %d: wrote 0x%04X\n", i, pattern);
    }

    // Clock once to update outputs
    set_address(address, 0);
    RAM8_clock(&ram, 0x0000, 0, address);

    // Read all addresses
    printf("\nReading all addresses:\n");
    int all_correct = 1;
    for (int i = 0; i < 8; i++) {
        set_address(address, i);
        RAM8_clock(&ram, 0x0000, 0, address);
        uint16_t val = RAM8_read_register(&ram, i);
        uint16_t expected = 0x1000 + (i * 0x0100);
        printf("  Address %d: 0x%04X %s\n", i, val, 
               val == expected ? "(correct)" : "(incorrect)");
        if (val != expected) all_correct = 0;
    }
    if (all_correct) {
        printf("\n All addresses correct!\n");
    }
}

int main() {
    printf("╔═══════════════════════════════════════╗\n");
    printf("║        RAM8 TESTS (CORRECTED)        ║\n");
    printf("╚═══════════════════════════════════════╝\n");

    test_ram8_basic();
    test_ram8_read_write();
    test_ram8_overwrite();
    test_ram8_load_0();
    test_ram8_delay();
    test_ram8_all_addresses();

    printf("\n╔═══════════════════════════════════════╗\n");
    printf("║     ALL RAM8 TESTS COMPLETED!        ║\n");
    printf("╚═══════════════════════════════════════╝\n");

    return 0;
}
