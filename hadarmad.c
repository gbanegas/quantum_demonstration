#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <quantum.h>

int main ()
{
  quantum_reg reg;
  int result;
  reg = quantum_new_qureg(1, 1);
  printf("Created register\n");
  quantum_print_qureg(reg);

  printf("applying hadamard\n");
  quantum_hadamard(0, &reg);
  quantum_print_qureg(reg);

  printf("applying hadamard\n");
  quantum_hadamard(0, &reg);
  quantum_print_qureg(reg);

  result = quantum_measure(reg);
  printf("measured %i!\n", result);

  return 0;
}
