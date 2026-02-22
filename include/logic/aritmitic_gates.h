#ifndef ARITMITIC_GATES
#define ARITMITIC_GATES
#include <stdint.h>
void HalfAdder(int a, int b, int *sum, int *carry);
void FullAdder(int a, int b, int c_in, int *sum, int *c_out);
void Add16(uint16_t a[16], uint16_t b[16], uint16_t out[16]);
void Inc16(uint16_t in[16], uint16_t out[16]);
#endif // !DEBUG
