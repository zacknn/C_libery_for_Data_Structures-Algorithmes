#ifndef LOGIC_GATES_H
#define LOGIC_GATES_H

#include <stdint.h>

// Basic gates (1-bit)
int Not(int a);
int And(int a, int b);
int Or(int a, int b);
int Xor(int a, int b);
int Mux(int a, int b, int sel);
void DMux(int in, int sel, int *a, int *b);

// 16-bit gates
void Not16(uint16_t in[16], uint16_t out[16]);
void And16(uint16_t a[16], uint16_t b[16], uint16_t out[16]);
void Or16(uint16_t a[16], uint16_t b[16], uint16_t out[16]);
void Mux16(uint16_t a[16], uint16_t b[16], int sel, uint16_t out[16]);

// Multi-way gates
int Or8Way(uint16_t in[8]);
void Mux4Way16(uint16_t a[16], uint16_t b[16], uint16_t c[16], uint16_t d[16],
               uint16_t sel[2], uint16_t out[16]);
void Mux8Way16(uint16_t a[16], uint16_t b[16], uint16_t c[16], uint16_t d[16],
               uint16_t e[16], uint16_t f[16], uint16_t g[16], uint16_t h[16],
               uint16_t sel[3], uint16_t out[16]);
void DMux4Way(int in, uint16_t sel[2], int *a, int *b, int *c, int *d);
void DMux8Way(int in, uint16_t sel[3], int *a, int *b, int *c, int *d, int *e,
              int *f, int *g, int *h);

#endif
