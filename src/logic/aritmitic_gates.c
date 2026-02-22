#include "logic/aritmitic_gates.h"
#include "logic/logic_gates.h"
#include <stdint.h>

void HalfAdder(int a, int b, int *sum, int *carry) {
  *sum = Xor(a, b);
  *carry = And(a, b);
}

void FullAdder(int a, int b, int c_in, int *sum, int *c_out) {
  int sum1, carry1, carry2;
  HalfAdder(a, b, &sum1, &carry1);
  HalfAdder(sum1, c_in, sum, &carry2);
  *c_out = Or(carry1, carry2);
}

void Add16(uint16_t a[16], uint16_t b[16], uint16_t out[16]) {
  int carry = 0; // start with 0 carry
  // add bit by bit from the right to the left
  for (int i = 0; i < 16; i++) {
    int sum;
    FullAdder(a[i], b[i], carry, &sum, &carry);
    out[i] = sum;
  }
  // note : the final carry make overflow so we distracted
};

void Inc16(uint16_t in[16], uint16_t out[16]) {
  uint16_t one[16] = {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  Add16(in, one, out);
}
