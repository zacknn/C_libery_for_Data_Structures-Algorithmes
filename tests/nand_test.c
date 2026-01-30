#include "logic/logic_gates.h"
#include "logic/nand.h"
#include <stdio.h>
int main()
{
  // nand Test
  int a = 1, b = 1, Result;
  Result = Nand(a, b);
  printf("the result of nand is = %d\n", Result);

  // not - and - or
  int some_test_cases[4][2] = {
      {0, 1},
      {0, 0},
      {1, 0},
      {1, 1},
  };
  int selVal[2] = {1, 0};

  for (int i = 0; i < 4; i++)
  {
    int value = some_test_cases[i][0];
    printf("le not est %d :\n", Not(value));

    int value1 = some_test_cases[i][0];
    int value2 = some_test_cases[i][1];

    printf(" the and is %d : \n", And(value1, value2));
    printf(" the or is %d : \n", Or(value1, value2));
  }

  for (int i = 0; i < 4; i++)
  {
    int value1 = selVal[i];
    int value2 = some_test_cases[i][0];
    int value3 = some_test_cases[i][1];
    printf("the Mux of sel = %d , val1 = %d , val2 = %d is : %d \n", value1,
           value2, value3 , Mux(value2, value3, value1));
  }

  return 0;
}
