#include "logic/logic_gates.h"
#include "logic/nand.h"

int Not(int in) { return Nand(in, in); }

int And(int a, int b) { return Not(Nand(a, b)); }

int Or(int a, int b) {
  int not_a = Not(a);
  int not_b = Not(b);

  return Not(And(not_a, not_b));
}

int Mux(int a, int b, int sel) {
  int notSel = Not(sel);
  int out1 = And(a, notSel);
  int out2 = And(b, sel);
  return Or(out1, out2);
}

int Dmux(int in, int sel, int *a, int *b) {
  int selNot = Not(sel);
  *a = And(in, sel);
  *b = And(in, selNot);
}
