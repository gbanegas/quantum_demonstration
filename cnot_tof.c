#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <quantum.h>

int main ()
{
  quantum_reg reg;
  int result;
  reg = quantum_new_qureg(1, 3);
  quantum_print_qureg(reg);
  quantum_cnot(0,1, &reg);
  quantum_print_qureg(reg);
  quantum_toffoli(0,1,2, &reg);
  quantum_print_qureg(reg);

  result = quantum_measure(reg);
  printf("measured %i!\n", result);

  return 0;
}
