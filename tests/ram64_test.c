#include "logic/ram64.h"
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

int tests_passed = 0;
int tests_failed = 0;

#define TEST(name, condition) do { \
    if (condition) { \
        tests_passed++; \
        printf("  [PASS] %s\n", name); \
    } else { \
        tests_failed++; \
        printf("  [FAIL] %s (line %d)\n", name, __LINE__); \
    } \
} while(0)

// Helper: set 6-bit address from integer 0-63
void set_address(uint16_t addr[6], int value) {
    addr[0] = (value >> 0) & 1;
    addr[1] = (value >> 1) & 1;
    addr[2] = (value >> 2) & 1;
    addr[3] = (value >> 3) & 1;
    addr[4] = (value >> 4) & 1;
    addr[5] = (value >> 5) & 1;
}

// ==================== TEST 1: Basic Init ====================
void test_init() {
    printf("=== Test 1: Initialization ===");
    RAM64_t ram;
    RAM64_init(&ram);

    TEST("RAM64 init out=0", RAM64_read(&ram) == 0);

    int all_zero = 1;
    for (int i = 0; i < 64; i++) {
        if (RAM64_read_register(&ram, i) != 0) {
            all_zero = 0;
            break;
        }
    }
    TEST("All 64 registers initialized to 0", all_zero);
}

// ==================== TEST 2: Single Write + Delay ====================
void test_single_write() {
    printf("=== Test 2: Single Write with DFF Delay ===");
    RAM64_t ram;
    RAM64_init(&ram);
    uint16_t address[6];
    
    set_address(address, 0);
    RAM64_clock(&ram, 0xABCD, 1, address);

    // After 1 clock: DFF delay means register out is still 0
    TEST("After write: reg[0] = 0 (delay)", RAM64_read_register(&ram, 0) == 0);
    TEST("After write: output = 0 (delay)", RAM64_read(&ram) == 0);

    // After 2nd clock (keep): value appears
    RAM64_clock(&ram, 0x0000, 0, address);
    TEST("After keep: reg[0] = 0xABCD", RAM64_read_register(&ram, 0) == 0xABCD);
    TEST("After keep: output = 0xABCD", RAM64_read(&ram) == 0xABCD);
}

// ==================== TEST 3: Write to Multiple Addresses ====================
void test_multiple_writes() {
    printf("=== Test 3: Write to Multiple Addresses ===");
    RAM64_t ram;
    RAM64_init(&ram);
    uint16_t address[6];

    // Write to addresses 0, 7, 15, 31, 42, 63
    int test_addrs[] = {0, 7, 15, 31, 42, 63};
    uint16_t test_vals[] = {0x1111, 0x2222, 0x3333, 0x4444, 0x5555, 0x6666};
    int n = 6;

    for (int i = 0; i < n; i++) {
        set_address(address, test_addrs[i]);
        RAM64_clock(&ram, test_vals[i], 1, address);
    }

    // One extra clock to let all DFFs settle
    set_address(address, 0);
    RAM64_clock(&ram, 0x0000, 0, address);

    int all_correct = 1;
    for (int i = 0; i < n; i++) {
        uint16_t val = RAM64_read_register(&ram, test_addrs[i]);
        if (val != test_vals[i]) {
            printf("  [FAIL] Address %d: expected 0x%04X, got 0x%04X",
                   test_addrs[i], test_vals[i], val);
            all_correct = 0;
        }
    }
    TEST("All written values correct", all_correct);

    // Check untouched addresses are still 0
    int untouched_ok = 1;
    for (int i = 0; i < 64; i++) {
        int is_written = 0;
        for (int j = 0; j < n; j++) {
            if (test_addrs[j] == i) is_written = 1;
        }
        if (!is_written && RAM64_read_register(&ram, i) != 0) {
            untouched_ok = 0;
            printf("  [FAIL] Untouched address %d is 0x%04X (should be 0)",
                   i, RAM64_read_register(&ram, i));
            break;
        }
    }
    TEST("Untouched addresses remain 0", untouched_ok);
}

// ==================== TEST 4: Load=0 Preserves Value ====================
void test_load_zero() {
    printf("=== Test 4: load=0 Preserves Value ===");
    RAM64_t ram;
    RAM64_init(&ram);
    uint16_t address[6];

    // Write to address 42
    set_address(address, 42);
    RAM64_clock(&ram, 0x1234, 1, address);
    RAM64_clock(&ram, 0x0000, 0, address); // let it appear

    TEST("Before overwrite attempt: reg[42] = 0x1234",
         RAM64_read_register(&ram, 42) == 0x1234);

    // Try to overwrite with load=0
    RAM64_clock(&ram, 0xFFFF, 0, address);
    TEST("After load=0: reg[42] still 0x1234",
         RAM64_read_register(&ram, 42) == 0x1234);
}

// ==================== TEST 5: Overwrite Same Address ====================
void test_overwrite() {
    printf("=== Test 5: Overwrite Same Address ===");
    RAM64_t ram;
    RAM64_init(&ram);
    uint16_t address[6];

    set_address(address, 10);

    // First write
    RAM64_clock(&ram, 0xAAAA, 1, address);
    RAM64_clock(&ram, 0x0000, 0, address); // let it appear
    TEST("First write: reg[10] = 0xAAAA",
         RAM64_read_register(&ram, 10) == 0xAAAA);

    // Second write
    RAM64_clock(&ram, 0xBBBB, 1, address);
    // DFF delay: reg[10].out still shows 0xAAAA
    TEST("After 2nd write (delay): reg[10] = 0xAAAA",
         RAM64_read_register(&ram, 10) == 0xAAAA);

    // Keep to see new value
    RAM64_clock(&ram, 0x0000, 0, address);
    TEST("After keep: reg[10] = 0xBBBB",
         RAM64_read_register(&ram, 10) == 0xBBBB);
}

// ==================== TEST 6: DFF Delay Demonstration ====================
void test_delay() {
    printf("=== Test 6: DFF Delay Demonstration ===");
    RAM64_t ram;
    RAM64_init(&ram);
    uint16_t address[6];

    set_address(address, 0);

    printf("Step 0: Initial state -> output = 0x%04X", RAM64_read(&ram));

    RAM64_clock(&ram, 0xAAAA, 1, address);
    printf("Step 1: Write 0xAAAA -> output = 0x%04X (delay)", RAM64_read(&ram));

    RAM64_clock(&ram, 0x0000, 0, address);
    printf("Step 2: Keep       -> output = 0x%04X (value appears)", RAM64_read(&ram));

    RAM64_clock(&ram, 0xBBBB, 1, address);
    printf("Step 3: Write 0xBBBB -> output = 0x%04X (delay)", RAM64_read(&ram));

    RAM64_clock(&ram, 0x0000, 0, address);
    printf("Step 4: Keep       -> output = 0x%04X (new value appears)", RAM64_read(&ram));

    TEST("Delay pattern correct",
         RAM64_read(&ram) == 0xBBBB);
}

// ==================== TEST 7: All 64 Addresses ====================
void test_all_addresses() {
    printf("=== Test 7: All 64 Addresses ===");
    RAM64_t ram;
    RAM64_init(&ram);
    uint16_t address[6];

    // Write a unique pattern to each address
    printf("Writing to all 64 addresses...");
    for (int i = 0; i < 64; i++) {
        uint16_t pattern = 0x1000 + (i * 0x0100);
        set_address(address, i);
        RAM64_clock(&ram, pattern, 1, address);
    }

    // One extra clock to settle all DFFs
    set_address(address, 0);
    RAM64_clock(&ram, 0x0000, 0, address);

    printf("Reading back all 64 addresses...");
    int all_correct = 1;
    for (int i = 0; i < 64; i++) {
        uint16_t expected = 0x1000 + (i * 0x0100);
        uint16_t val = RAM64_read_register(&ram, i);
        if (val != expected) {
            printf("  [FAIL] Address %d: expected 0x%04X, got 0x%04X",
                   i, expected, val);
            all_correct = 0;
        }
    }
    TEST("All 64 addresses correct", all_correct);
    if (all_correct) {
        printf("  All 64 addresses verified successfully.");
    }
}

// ==================== TEST 8: Cross-RAM8 Boundaries ====================
void test_cross_boundary() {
    printf("=== Test 8: Cross-RAM8 Boundaries ===");
    RAM64_t ram;
    RAM64_init(&ram);
    uint16_t address[6];

    // Addresses 7 and 8 are in different RAM8s (RAM8 #0 and RAM8 #1)
    set_address(address, 7);
    RAM64_clock(&ram, 0x7777, 1, address);

    set_address(address, 8);
    RAM64_clock(&ram, 0x8888, 1, address);

    // Settle
    set_address(address, 0);
    RAM64_clock(&ram, 0x0000, 0, address);

    TEST("Address 7 (end of RAM8 #0) = 0x7777",
         RAM64_read_register(&ram, 7) == 0x7777);
    TEST("Address 8 (start of RAM8 #1) = 0x8888",
         RAM64_read_register(&ram, 8) == 0x8888);

    // Addresses 15 and 16 (RAM8 #1 and #2 boundary)
    set_address(address, 15);
    RAM64_clock(&ram, 0x1111, 1, address);
    set_address(address, 16);
    RAM64_clock(&ram, 0x2222, 1, address);

    set_address(address, 0);
    RAM64_clock(&ram, 0x0000, 0, address);

    TEST("Address 15 (end of RAM8 #1) = 0x1111",
         RAM64_read_register(&ram, 15) == 0x1111);
    TEST("Address 16 (start of RAM8 #2) = 0x2222",
         RAM64_read_register(&ram, 16) == 0x2222);
}

int main() {
    printf("============================================");
    printf("           RAM64 TEST SUITE                 ");
    printf("============================================");

    test_init();
    test_single_write();
    test_multiple_writes();
    test_load_zero();
    test_overwrite();
    test_delay();
    test_all_addresses();
    test_cross_boundary();

    printf("============================================");
    printf("  RESULTS: %d passed, %d failed", tests_passed, tests_failed);
    printf("============================================");

    return tests_failed > 0 ? 1 : 0;
}
