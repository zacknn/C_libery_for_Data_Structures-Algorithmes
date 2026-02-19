#include "logic/logic_gates.h"
#include "logic/nand.h"
#include <stdint.h>
#include <stdio.h>

// Helper function to print 16-bit array
void print16(const char *name, uint16_t arr[16]) {
  printf("%s: ", name);
  for (int i = 15; i >= 0; i--) { // Print MSB first
    printf("%d", arr[i]);
  }
  printf("\n");
}

int main() {
  printf("=== Basic Gates Tests ===\n");

  // NAND Test
  int a = 1, b = 1, Result;
  Result = Nand(a, b);
  printf("NAND(1, 1) = %d\n\n", Result);

  // NOT, AND, OR tests
  int some_test_cases[4][2] = {
      {0, 1},
      {0, 0},
      {1, 0},
      {1, 1},
  };

  printf("Truth Table:\n");
  printf("A | B | NOT(A) | AND | OR  | XOR\n");
  printf("--+---+--------+-----+-----+----\n");
  for (int i = 0; i < 4; i++) {
    int value1 = some_test_cases[i][0];
    int value2 = some_test_cases[i][1];
    printf("%d | %d |   %d    |  %d  |  %d  |  %d\n", value1, value2,
           Not(value1), And(value1, value2), Or(value1, value2),
           Xor(value1, value2));
  }
  printf("\n");

  // MUX Test
  printf("=== MUX Tests ===\n");
  printf("SEL | A | B | MUX(A,B,SEL)\n");
  printf("----+---+---+-------------\n");
  for (int sel = 0; sel <= 1; sel++) {
    for (int i = 0; i < 4; i++) {
      int a = some_test_cases[i][0];
      int b = some_test_cases[i][1];
      printf(" %d  | %d | %d |      %d\n", sel, a, b, Mux(a, b, sel));
    }
  }
  printf("\n");

  // DMUX Test
  printf("=== DMUX Tests ===\n");
  printf("IN | SEL | A | B\n");
  printf("---+-----+---+---\n");
  for (int in = 0; in <= 1; in++) {
    for (int sel = 0; sel <= 1; sel++) {
      int outa, outb;
      DMux(in, sel, &outa, &outb);
      printf(" %d |  %d  | %d | %d\n", in, sel, outa, outb);
    }
  }
  printf("\n");

  // 16-bit gates tests
  printf("=== 16-bit Gates Tests ===\n");

  // Initialize test arrays
  uint16_t in16[16] = {1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0};
  uint16_t a16[16] = {1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0};
  uint16_t b16[16] = {1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0};
  uint16_t out16[16];

  // NOT16
  Not16(in16, out16);
  print16("Input ", in16);
  print16("NOT16 ", out16);
  printf("\n");

  // AND16
  print16("A     ", a16);
  print16("B     ", b16);
  And16(a16, b16, out16);
  print16("AND16 ", out16);
  printf("\n");

  // OR16
  Or16(a16, b16, out16);
  print16("OR16  ", out16);
  printf("\n");

  // MUX16
  printf("MUX16 with SEL=0:\n");
  Mux16(a16, b16, 0, out16);
  print16("Result", out16);
  printf("MUX16 with SEL=1:\n");
  Mux16(a16, b16, 1, out16);
  print16("Result", out16);
  printf("\n");

  // OR8WAY
  printf("=== OR8WAY Test ===\n");
  uint16_t test8_1[8] = {0, 0, 0, 0, 0, 0, 0, 0};
  uint16_t test8_2[8] = {0, 0, 0, 1, 0, 0, 0, 0};
  uint16_t test8_3[8] = {1, 1, 1, 1, 1, 1, 1, 1};

  printf("All zeros: %d (expected 0)\n", Or8Way(test8_1));
  printf("One bit set: %d (expected 1)\n", Or8Way(test8_2));
  printf("All ones: %d (expected 1)\n", Or8Way(test8_3));
  printf("\n");

  // MUX4WAY16
  printf("=== MUX4WAY16 Test ===\n");
  uint16_t mux4_a[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  uint16_t mux4_b[16] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
  uint16_t mux4_c[16] = {1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0};
  uint16_t mux4_d[16] = {0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1};

  uint16_t sel2[2];
  for (int s1 = 0; s1 <= 1; s1++) {
    for (int s0 = 0; s0 <= 1; s0++) {
      sel2[0] = s0;
      sel2[1] = s1;
      Mux4Way16(mux4_a, mux4_b, mux4_c, mux4_d, sel2, out16);
      printf("SEL[1:0]=%d%d -> ", s1, s0);
      print16("Output", out16);
    }
  }
  printf("\n");

  // MUX8WAY16
  printf("=== MUX8WAY16 Test ===\n");
  uint16_t mux8_e[16] = {1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0};
  uint16_t mux8_f[16] = {0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1};
  uint16_t mux8_g[16] = {1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1};
  uint16_t mux8_h[16] = {0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0};

  uint16_t sel3[3] = {0, 0, 0};
  Mux8Way16(mux4_a, mux4_b, mux4_c, mux4_d, mux8_e, mux8_f, mux8_g, mux8_h,
            sel3, out16);
  printf("SEL[2:0]=000 -> ");
  print16("Output", out16);

  sel3[0] = 1;
  sel3[1] = 1;
  sel3[2] = 1;
  Mux8Way16(mux4_a, mux4_b, mux4_c, mux4_d, mux8_e, mux8_f, mux8_g, mux8_h,
            sel3, out16);
  printf("SEL[2:0]=111 -> ");
  print16("Output", out16);
  printf("\n");

  // DMUX4WAY
  printf("=== DMUX4WAY Test ===\n");
  printf("IN | SEL[1:0] | A | B | C | D\n");
  printf("---+----------+---+---+---+---\n");
  for (int in = 0; in <= 1; in++) {
    for (int s1 = 0; s1 <= 1; s1++) {
      for (int s0 = 0; s0 <= 1; s0++) {
        int oa, ob, oc, od;
        sel2[0] = s0;
        sel2[1] = s1;
        DMux4Way(in, sel2, &oa, &ob, &oc, &od);
        printf(" %d |    %d%d    | %d | %d | %d | %d\n", in, s1, s0, oa, ob, oc,
               od);
      }
    }
  }
  printf("\n");

  // DMUX8WAY
  printf("=== DMUX8WAY Test ===\n");
  printf("Testing with IN=1:\n");
  printf("SEL[2:0] | A | B | C | D | E | F | G | H\n");
  printf("---------+---+---+---+---+---+---+---+---\n");
  for (int s2 = 0; s2 <= 1; s2++) {
    for (int s1 = 0; s1 <= 1; s1++) {
      for (int s0 = 0; s0 <= 1; s0++) {
        int oa, ob, oc, od, oe, of, og, oh;
        sel3[0] = s0;
        sel3[1] = s1;
        sel3[2] = s2;
        DMux8Way(1, sel3, &oa, &ob, &oc, &od, &oe, &of, &og, &oh);
        printf("   %d%d%d   | %d | %d | %d | %d | %d | %d | %d | %d\n", s2, s1,
               s0, oa, ob, oc, od, oe, of, og, oh);
      }
    }
  }

  return 0;
}
