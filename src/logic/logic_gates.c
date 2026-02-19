#include "logic/logic_gates.h"
#include "logic/nand.h"
#include <stdint.h>
int Not(int in) { return Nand(in, in); }

int And(int a, int b) { return Not(Nand(a, b)); }

int Or(int a, int b) {
  int not_a = Not(a);
  int not_b = Not(b);

  return Not(And(not_a, not_b));
}
int Xor(int a, int b) { return And(Or(a, b), Nand(a, b)); }
int Mux(int a, int b, int sel) {
  int notSel = Not(sel);
  int out1 = And(a, notSel);
  int out2 = And(b, sel);
  return Or(out1, out2);
}

void DMux(int in, int sel, int *a, int *b) {
  int selNot = Not(sel);
  *a = And(in, sel);
  *b = And(in, selNot);
}
// 16-bit gates
void Not16(uint16_t in[16], uint16_t out[16]) {
  for (int i = 0; i < 16; i++) {
    out[i] = Not(in[i]);
  }
}

void And16(uint16_t a[16], uint16_t b[16], uint16_t out[16]) {
  for (int i = 0; i < 16; i++) {
    out[i] = And(a[i], b[i]);
  }
}

void Or16(uint16_t a[16], uint16_t b[16], uint16_t out[16]) {
  for (int i = 0; i < 16; i++) {
    out[i] = Or(a[i], b[i]);
  }
}

void Mux16(uint16_t a[16], uint16_t b[16], int sel, uint16_t out[16]) {
  for (int i = 0; i < 16; i++) {
    out[i] = Mux(a[i], b[i], sel);
  }
}

// Multi-way gates
int Or8Way(uint16_t in[8]) {
  int result = in[0];
  for (int i = 1; i < 8; i++) {
    result = Or(result, in[i]);
  }
  return result;
}

void Mux4Way16(uint16_t a[16], uint16_t b[16], uint16_t c[16], uint16_t d[16],
               uint16_t sel[2], uint16_t out[16]) {
  uint16_t mux_ab[16], mux_cd[16];
  Mux16(a, b, sel[0], mux_ab);
  Mux16(c, d, sel[0], mux_cd);
  Mux16(mux_ab, mux_cd, sel[1], out);
}

void Mux8Way16(uint16_t a[16], uint16_t b[16], uint16_t c[16], uint16_t d[16],
               uint16_t e[16], uint16_t f[16], uint16_t g[16], uint16_t h[16],
               uint16_t sel[3], uint16_t out[16]) {
  uint16_t mux_abcd[16], mux_efgh[16];
  Mux4Way16(a, b, c, d, sel, mux_abcd);
  Mux4Way16(e, f, g, h, sel, mux_efgh);
  Mux16(mux_abcd, mux_efgh, sel[2], out);
}

void DMux4Way(int in, uint16_t sel[2], int *a, int *b, int *c, int *d) {
  int dmux_ab, dmux_cd;
  DMux(in, sel[1], &dmux_ab, &dmux_cd);
  DMux(dmux_ab, sel[0], a, b);
  DMux(dmux_cd, sel[0], c, d);
}

void DMux8Way(int in, uint16_t sel[3], int *a, int *b, int *c, int *d, int *e,
              int *f, int *g, int *h) {
  int dmux_abcd, dmux_efgh;
  DMux(in, sel[2], &dmux_abcd, &dmux_efgh);
  DMux4Way(dmux_abcd, sel, a, b, c, d);
  DMux4Way(dmux_efgh, sel, e, f, g, h);
}
