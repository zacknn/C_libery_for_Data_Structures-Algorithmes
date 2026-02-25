#include "logic/alu.h"
#include "logic/aritmitic_gates.h"
#include "logic/logic_gates.h"
#include <stdint.h>

void ALU(uint16_t x[16], uint16_t y[16], int zx, int nx, int zy, int ny, int f,
         int no, uint16_t out[16], int *zr, int *ng) {

  // Step 1: Process x input
  uint16_t x_processed[16];
  uint16_t zero[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

  // If zx, then x = 0
  Mux16(x, zero, zx, x_processed);

  // If nx, then x = NOT x
  uint16_t x_negated[16];
  Not16(x_processed, x_negated);
  Mux16(x_processed, x_negated, nx, x_processed);

  // Step 2: Process y input
  uint16_t y_processed[16];

  // If zy, then y = 0
  Mux16(y, zero, zy, y_processed);

  // If ny, then y = NOT y
  uint16_t y_negated[16];
  Not16(y_processed, y_negated);
  Mux16(y_processed, y_negated, ny, y_processed);

  // Step 3: Compute f function
  uint16_t f_add[16]; // x + y
  uint16_t f_and[16]; // x AND y

  Add16(x_processed, y_processed, f_add);
  And16(x_processed, y_processed, f_and);

  // Select between Add and And based on f
  uint16_t f_out[16];
  Mux16(f_and, f_add, f, f_out);

  // Step 4: Negate output if no
  uint16_t f_negated[16];
  Not16(f_out, f_negated);
  Mux16(f_out, f_negated, no, out);

  // Step 5: Set status flags

  // zr flag: Check if output is zero
  // OR all bits together, if result is 0, then all bits were 0
  uint16_t or_result_low[8];
  for (int i = 0; i < 8; i++) {
    or_result_low[i] = out[i];
  }
  int or_low = Or8Way(or_result_low);

  uint16_t or_result_high[8];
  for (int i = 0; i < 8; i++) {
    or_result_high[i] = out[i + 8];
  }
  int or_high = Or8Way(or_result_high);

  int any_bit_set = Or(or_low, or_high);
  *zr = Not(any_bit_set); // zr = 1 if no bits are set

  // ng flag: Check if output is negative (MSB = 1)
  *ng = out[15]; // Most significant bit
}
