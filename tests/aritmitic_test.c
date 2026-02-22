#include "logic/aritmitic_gates.h"
#include <stdint.h>
#include <stdio.h>

// Convert 16-bit array to decimal number
int array_to_decimal(uint16_t arr[16]) {
  int result = 0;
  for (int i = 0; i < 16; i++) {
    if (arr[i]) {
      result += (1 << i); // 2^i
    }
  }
  return result;
}

// Convert decimal to 16-bit array
void decimal_to_array(int num, uint16_t arr[16]) {
  for (int i = 0; i < 16; i++) {
    arr[i] = (num >> i) & 1;
  }
}

// Print 16-bit array in binary (visual)
void print_binary(const char *label, uint16_t arr[16], int decimal) {
  printf("%s: ", label);
  // Print MSB to LSB (left to right, more natural)
  for (int i = 15; i >= 0; i--) {
    printf("%d", arr[i]);
    if (i % 4 == 0 && i != 0)
      printf(" "); // Group by 4 for readability
  }
  printf(" = %d (decimal)\n", decimal);
}

// Print separator line
void print_separator() {
  printf("================================================================\n");
}

void print_title(const char *title) {
  printf("\n");
  print_separator();
  printf("  %s\n", title);
  print_separator();
}

// ============================================
// TEST FUNCTIONS
// ============================================

void test_half_adder() {
  print_title("HALF ADDER TESTS");

  printf("Half Adder Truth Table:\n");
  printf("  A | B | SUM | CARRY\n");
  printf(" ---+---+-----+-------\n");

  int test_cases[4][2] = {{0, 0}, {0, 1}, {1, 0}, {1, 1}};

  for (int i = 0; i < 4; i++) {
    int a = test_cases[i][0];
    int b = test_cases[i][1];
    int sum, carry;

    HalfAdder(a, b, &sum, &carry);

    printf("  %d | %d |  %d  |   %d\n", a, b, sum, carry);
  }

  printf("\nVisualization:\n");
  printf("  1 + 1 = 10 (binary) → sum=0, carry=1\n");
  printf("  This is like: 1 + 1 = 2, where 2 in binary is '10'\n");
}

void test_full_adder() {
  print_title("FULL ADDER TESTS");

  printf("Full Adder Truth Table:\n");
  printf("  A | B | Cin | SUM | Cout\n");
  printf(" ---+---+-----+-----+------\n");

  int test_cases[8][3] = {{0, 0, 0}, {0, 0, 1}, {0, 1, 0}, {0, 1, 1},
                          {1, 0, 0}, {1, 0, 1}, {1, 1, 0}, {1, 1, 1}};

  for (int i = 0; i < 8; i++) {
    int a = test_cases[i][0];
    int b = test_cases[i][1];
    int cin = test_cases[i][2];
    int sum, cout;

    FullAdder(a, b, cin, &sum, &cout);

    printf("  %d | %d |  %d  |  %d  |  %d\n", a, b, cin, sum, cout);
  }

  printf("\nKey Examples:\n");
  printf("  1 + 1 + 0 = 10 (binary) → sum=0, carry=1\n");
  printf("  1 + 1 + 1 = 11 (binary) → sum=1, carry=1 (this is 3 in decimal)\n");
}

void test_add16() {
  print_title("ADD16 - 16-BIT ADDER TESTS");

  // Test case 1: 7 + 5 = 12
  printf("\n Test 1: Adding 7 + 5\n");
  printf("Expected: 12\n\n");

  uint16_t a1[16], b1[16], result1[16];
  decimal_to_array(7, a1);
  decimal_to_array(5, b1);

  Add16(a1, b1, result1);

  print_binary("     7", a1, 7);
  print_binary("  +  5", b1, 5);
  printf("  ----\n");
  print_binary("    12", result1, array_to_decimal(result1));

  // Test case 2: 15 + 20 = 35
  printf("\n Test 2: Adding 15 + 20\n");
  printf("Expected: 35\n\n");

  uint16_t a2[16], b2[16], result2[16];
  decimal_to_array(15, a2);
  decimal_to_array(20, b2);

  Add16(a2, b2, result2);

  print_binary("    15", a2, 15);
  print_binary("  + 20", b2, 20);
  printf("  ----\n");
  print_binary("    35", result2, array_to_decimal(result2));

  // Test case 3: 100 + 200 = 300
  printf("\n Test 3: Adding 100 + 200\n");
  printf("Expected: 300\n\n");

  uint16_t a3[16], b3[16], result3[16];
  decimal_to_array(100, a3);
  decimal_to_array(200, b3);

  Add16(a3, b3, result3);

  print_binary("   100", a3, 100);
  print_binary(" + 200", b3, 200);
  printf("  ----\n");
  print_binary("   300", result3, array_to_decimal(result3));

  // Test case 4: 255 + 255 = 510
  printf("\n Test 4: Adding 255 + 255\n");
  printf("Expected: 510\n\n");

  uint16_t a4[16], b4[16], result4[16];
  decimal_to_array(255, a4);
  decimal_to_array(255, b4);

  Add16(a4, b4, result4);

  print_binary("   255", a4, 255);
  print_binary(" + 255", b4, 255);
  printf("  ----\n");
  print_binary("   510", result4, array_to_decimal(result4));

  // Test case 5: Edge case - adding 0
  printf("\n Test 5: Adding 42 + 0\n");
  printf("Expected: 42\n\n");

  uint16_t a5[16], b5[16], result5[16];
  decimal_to_array(42, a5);
  decimal_to_array(0, b5);

  Add16(a5, b5, result5);

  print_binary("    42", a5, 42);
  print_binary("  +  0", b5, 0);
  printf("  ----\n");
  print_binary("    42", result5, array_to_decimal(result5));
}

void test_inc16() {
  print_title("INC16 - 16-BIT INCREMENTER TESTS");

  // Test case 1: Increment 0
  printf("\n Test 1: Incrementing 0\n");
  printf("Expected: 1\n\n");

  uint16_t in1[16], out1[16];
  decimal_to_array(0, in1);
  Inc16(in1, out1);

  print_binary("Input ", in1, 0);
  print_binary("Output", out1, array_to_decimal(out1));

  // Test case 2: Increment 7
  printf("\n Test 2: Incrementing 7\n");
  printf("Expected: 8\n\n");

  uint16_t in2[16], out2[16];
  decimal_to_array(7, in2);
  Inc16(in2, out2);

  print_binary("Input ", in2, 7);
  print_binary("Output", out2, array_to_decimal(out2));

  // Test case 3: Increment 99
  printf("\n Test 3: Incrementing 99\n");
  printf("Expected: 100\n\n");

  uint16_t in3[16], out3[16];
  decimal_to_array(99, in3);
  Inc16(in3, out3);

  print_binary("Input ", in3, 99);
  print_binary("Output", out3, array_to_decimal(out3));

  // Test case 4: Increment 255
  printf("\n Test 4: Incrementing 255\n");
  printf("Expected: 256\n\n");

  uint16_t in4[16], out4[16];
  decimal_to_array(255, in4);
  Inc16(in4, out4);

  print_binary("Input ", in4, 255);
  print_binary("Output", out4, array_to_decimal(out4));

  // Test case 5: Multiple increments
  printf("\n Test 5: Multiple Increments (0 → 1 → 2 → 3)\n\n");

  uint16_t val[16], temp[16];
  decimal_to_array(0, val);

  for (int i = 0; i < 3; i++) {
    int before = array_to_decimal(val);
    Inc16(val, temp);
    for (int j = 0; j < 16; j++)
      val[j] = temp[j]; // Copy result back
    int after = array_to_decimal(val);
    printf("  Step %d: %d → %d\n", i + 1, before, after);
  }
}

void test_visual_addition_walkthrough() {
  print_title("VISUAL WALKTHROUGH: How Add16 Works");

  printf("\nLet's add 5 + 3 step-by-step:\n\n");

  uint16_t a[16], b[16], result[16];
  decimal_to_array(5, a);
  decimal_to_array(3, b);

  print_binary("  5 (binary)", a, 5);
  print_binary("+ 3 (binary)", b, 3);
  printf("\n");

  printf("Bit-by-bit addition (right to left):\n");
  printf("Position | A | B | Carry_in | Sum | Carry_out\n");
  printf("---------+---+---+----------+-----+----------\n");

  int carry = 0;
  for (int i = 0; i < 4; i++) { // Only show first 4 bits
    int sum, cout;
    FullAdder(a[i], b[i], carry, &sum, &cout);
    printf("   %d     | %d | %d |    %d     |  %d  |    %d\n", i, a[i], b[i],
           carry, sum, cout);
    carry = cout;
  }

  Add16(a, b, result);
  printf("\n");
  print_binary("Result", result, array_to_decimal(result));
  printf("\n 5 + 3 = 8 (Correct)\n");
}

// ============================================
// MAIN TEST RUNNER
// ============================================

int main() {
  printf("\n");
  printf(
      "╔════════════════════════════════════════════════════════════════╗\n");
  printf("║         ARITHMETIC LOGIC GATES - COMPREHENSIVE TESTS          ║\n");
  printf(
      "╚════════════════════════════════════════════════════════════════╝\n");

  test_half_adder();
  test_full_adder();
  test_add16();
  test_inc16();
  test_visual_addition_walkthrough();

  print_title("ALL TESTS COMPLETED!");
  return 0;
}
