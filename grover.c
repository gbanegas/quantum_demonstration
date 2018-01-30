#include <quantum.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <aux.h>

#ifdef M_PI
#define pi M_PI
#else
#define pi 3.141592654
#endif


void grover(int target, quantum_reg *reg)
{
  int i;
  //printf("Start of Grover:\n");
  //quantum_print_qureg(*reg);
  oracle(target, reg);

  for(i=0;i<reg->width;i++)
    quantum_hadamard(i, reg);

  inversion(reg);

  for(i=0;i<reg->width;i++)
    quantum_hadamard(i, reg);
}



int main(int argc, char **argv)
{
  quantum_reg reg;
  int i, N, width=0;
  printf("Starting...\n");

  N = 3; // Number to Search
  width = 23; //2^3 qubits

  reg = quantum_new_qureg(0, width);

  for(i=0;i<reg.width;i++)
    quantum_hadamard(i, &reg);

  quantum_print_qureg(reg);

  int number_of_iterations = (int) (pi/4*sqrt(1<<reg.width)); //2.22

  printf("Iterating %i times\n", number_of_iterations); //(pi/4)*sqrt(N)

  for(i=1; i<=number_of_iterations; i++)
    {
      printf("Iteration #%i\n", i);
      grover(N, &reg);
    }

    final_measure(&reg);

  for(i=0; i<reg.size; i++)
    {
      //if(reg.state[i] == N)
	printf("\nFound %lli with a probability of %f\n\n", reg.state[i],
	       quantum_prob(reg.amplitude[i]));
    }


  return 0;
}
