#include "logic/logic_gates.h"
#include "logic/nand.h"

int Not(int in) { return Nand(in, in); }

int And(int a, int b) { return Not(Nand(a, b)); }

int Or(int a, int b) {
  int not_a = Not(a);
  int not_b = Not(b);

  return Not(And(not_a, not_b));
}
