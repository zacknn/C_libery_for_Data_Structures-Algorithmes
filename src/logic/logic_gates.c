#include "logic/logic_gates.h"
#include "logic/nand.h"
#include <stdio.h>

int Not(int in) { return Nand(in, in); }

int And(int a, int b) { return Not(Nand(a, b)); }

int Or(int a, int b)
{
  int not_a = Not(a);
  int not_b = Not(b);

  return Not(And(not_a, not_b));
}

int Mux(int a, int b, int sel)
{
  int notSel = Not(sel);
  int out1 = And(a, notSel);
  int out2 = And(b, sel);
  return Or(out1, out2);
}
