#include "logic/nand.h"

int Nand(int a, int b) {
  // force input to be 1 or 0
  a = a ? 1 : 0;
  b = b ? 1 : 0;

  // and result
  int and = a & b;

  // Not (and)
  return and ^ 1;
}
