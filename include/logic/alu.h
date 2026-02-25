#ifndef ALU_H
#define ALU_H

#include <stdint.h>

/**
 * ALU - Arithmetic Logic Unit
 *
 * Computes one of the following functions based on control bits:
 *
 * Control bits: zx, nx, zy, ny, f, no
 *
 * @param x      - 16-bit input x
 * @param y      - 16-bit input y
 * @param zx     - Zero the x input
 * @param nx     - Negate the x input (bitwise NOT)
 * @param zy     - Zero the y input
 * @param ny     - Negate the y input (bitwise NOT)
 * @param f      - Function select: 1 = Add (x+y), 0 = And (x&y)
 * @param no     - Negate the output
 * @param out    - 16-bit output result
 * @param zr     - Output flag: 1 if out == 0, else 0
 * @param ng     - Output flag: 1 if out < 0 (MSB=1), else 0
 */
void ALU(uint16_t x[16], uint16_t y[16], int zx, int nx, int zy, int ny, int f,
         int no, uint16_t out[16], int *zr, int *ng);

#endif
