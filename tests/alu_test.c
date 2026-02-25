#include "logic/alu.h"
#include "logic/aritmitic_gates.h"
#include <stdint.h>
#include <stdio.h>

// Helper: Convert decimal to 16-bit array
void decimal_to_array(int num, uint16_t arr[16]) {
  for (int i = 0; i < 16; i++) {
    arr[i] = (num >> i) & 1;
  }
}

// Helper: Convert 16-bit array to decimal
int array_to_decimal(uint16_t arr[16]) {
  int result = 0;
  for (int i = 0; i < 16; i++) {
    if (arr[i]) {
      result += (1 << i);
    }
  }
  // Handle negative numbers (two's complement)
  if (arr[15] == 1) { // If MSB is 1, it's negative
    result = result - 65536;
  }
  return result;
}

// Helper: Print binary
void print_binary(const char *label, uint16_t arr[16]) {
  printf("%s: ", label);
  for (int i = 15; i >= 0; i--) {
    printf("%d", arr[i]);
    if (i % 4 == 0 && i != 0)
      printf(" ");
  }
  printf("\n");
}

// Test a specific ALU operation
void test_alu(const char *operation, int x_val, int y_val, int zx, int nx,
              int zy, int ny, int f, int no, int expected) {

  uint16_t x[16], y[16], out[16];
  int zr, ng;

  decimal_to_array(x_val, x);
  decimal_to_array(y_val, y);

  ALU(x, y, zx, nx, zy, ny, f, no, out, &zr, &ng);

  int result = array_to_decimal(out);

  printf("%-10s | x=%4d, y=%4d | Result=%4d | zr=%d, ng=%d | %s\n", operation,
         x_val, y_val, result, zr, ng,
         (result == expected) ? "✓ PASS" : "✗ FAIL");
}

void print_separator() {
  printf("================================================================\n");
}

int main() {
  printf("\n");
  printf(
      "╔════════════════════════════════════════════════════════════════╗\n");
  printf(
      "║                    ALU - COMPREHENSIVE TESTS                   ║\n");
  printf(
      "╚════════════════════════════════════════════════════════════════╝\n");

  print_separator();
  printf("CONSTANT OPERATIONS\n");
  print_separator();

  // Compute constant 0
  test_alu("0", 10, 20, 1, 0, 1, 0, 1, 0, 0);

  // Compute constant 1
  test_alu("1", 10, 20, 1, 1, 1, 1, 1, 1, 1);

  // Compute constant -1
  test_alu("-1", 10, 20, 1, 1, 1, 0, 1, 0, -1);

  print_separator();
  printf("INPUT OPERATIONS (x=5, y=3)\n");
  print_separator();

  // Output x
  test_alu("x", 5, 3, 0, 0, 1, 1, 0, 0, 5);

  // Output y
  test_alu("y", 5, 3, 1, 1, 0, 0, 0, 0, 3);

  // Output !x (NOT x)
  test_alu("!x", 5, 3, 0, 0, 1, 1, 0, 1, -6);

  // Output !y (NOT y)
  test_alu("!y", 5, 3, 1, 1, 0, 0, 0, 1, -4);

  // Output -x
  test_alu("-x", 5, 3, 0, 0, 1, 1, 1, 1, -5);

  // Output -y
  test_alu("-y", 5, 3, 1, 1, 0, 0, 1, 1, -3);

  print_separator();
  printf("INCREMENT/DECREMENT OPERATIONS (x=5, y=3)\n");
  print_separator();

  // x + 1
  test_alu("x+1", 5, 3, 0, 1, 1, 1, 1, 1, 6);

  // y + 1
  test_alu("y+1", 5, 3, 1, 1, 0, 1, 1, 1, 4);

  // x - 1
  test_alu("x-1", 5, 3, 0, 0, 1, 1, 1, 0, 4);

  // y - 1
  test_alu("y-1", 5, 3, 1, 1, 0, 0, 1, 0, 2);

  print_separator();
  printf("ARITHMETIC OPERATIONS (x=7, y=3)\n");
  print_separator();

  // x + y
  test_alu("x+y", 7, 3, 0, 0, 0, 0, 1, 0, 10);

  // x - y
  test_alu("x-y", 7, 3, 0, 1, 0, 0, 1, 1, 4);

  // y - x
  test_alu("y-x", 7, 3, 0, 0, 0, 1, 1, 1, -4);

  print_separator();
  printf("LOGICAL OPERATIONS (x=12, y=10)\n");
  print_separator();

  // x AND y
  test_alu("x&y", 12, 10, 0, 0, 0, 0, 0, 0, 8);

  // x OR y
  test_alu("x|y", 12, 10, 0, 1, 0, 1, 0, 1, 14);

  print_separator();
  printf("ZERO FLAG TESTS\n");
  print_separator();

  uint16_t x[16], y[16], out[16];
  int zr, ng;

  // Test: 5 - 5 = 0 (should set zr flag)
  decimal_to_array(5, x);
  decimal_to_array(5, y);
  ALU(x, y, 0, 1, 0, 0, 1, 1, out, &zr, &ng);
  printf("x-y where x=5, y=5: Result=%d, zr=%d (expected 1), ng=%d | %s\n",
         array_to_decimal(out), zr, ng, (zr == 1) ? "✓ PASS" : "✗ FAIL");

  print_separator();
  printf("NEGATIVE FLAG TESTS\n");
  print_separator();

  // Test: 3 - 7 = -4 (should set ng flag)
  decimal_to_array(3, x);
  decimal_to_array(7, y);
  ALU(x, y, 0, 1, 0, 0, 1, 1, out, &zr, &ng);
  printf("x-y where x=3, y=7: Result=%d, zr=%d, ng=%d (expected 1) | %s\n",
         array_to_decimal(out), zr, ng, (ng == 1) ? "✓ PASS" : "✗ FAIL");

  print_separator();
  printf("VISUAL EXAMPLE: Computing 15 + 27\n");
  print_separator();

  decimal_to_array(15, x);
  decimal_to_array(27, y);
  ALU(x, y, 0, 0, 0, 0, 1, 0, out, &zr, &ng); // x + y

  print_binary("x (15)      ", x);
  print_binary("y (27)      ", y);
  printf("Control: zx=0, nx=0, zy=0, ny=0, f=1 (Add), no=0\n");
  print_binary("Result (42) ", out);
  printf("Flags: zr=%d, ng=%d\n", zr, ng);
  printf("Decimal: %d\n", array_to_decimal(out));

  print_separator();
  printf("ALL ALU TESTS COMPLETED!\n");
  print_separator();
  printf("\n");

  return 0;
}
