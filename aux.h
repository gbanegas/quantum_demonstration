void oracle(int state, quantum_reg *reg)
{
  int i;

  for(i=0;i<reg->width;i++)
    {
      if(!(state & (1 << i)))
	{
	  quantum_sigma_x(i, reg); // if it is not 011 change to -x
	}
    }

  quantum_toffoli(0, 1, reg->width+1, reg);

  for(i=1;i<reg->width;i++)
    {
      quantum_toffoli(i, reg->width+i, reg->width+i+1, reg);
    }

  quantum_cnot(reg->width+i, reg->width, reg);

  for(i=reg->width-1;i>0;i--)
    {
      quantum_toffoli(i, reg->width+i, reg->width+i+1, reg);
    }

  quantum_toffoli(0, 1, reg->width+1, reg);

  for(i=0;i<reg->width;i++)
    {
      if(!(state & (1 << i)))
	quantum_sigma_x(i, reg);
    }

}
//Diffusion
void inversion(quantum_reg *reg)
{
  int i;
  for(i=0;i<reg->width;i++)
    quantum_sigma_x(i, reg); //NOT every Qubit

  quantum_hadamard(reg->width-1, reg);

  if(reg->width==3)
    quantum_toffoli(0, 1, 2, reg); //(control1, Control2, Target)
    else
      {
        quantum_toffoli(0, 1, reg->width+1, reg);

        for(i=1;i<reg->width-1;i++)
    {
      quantum_toffoli(i, reg->width+i, reg->width+i+1, reg);
    }

        quantum_cnot(reg->width+i, reg->width-1, reg);

        for(i=reg->width-2;i>0;i--)
    {
      quantum_toffoli(i, reg->width+i, reg->width+i+1, reg);
    }

        quantum_toffoli(0, 1, reg->width+1, reg);
      }

  quantum_hadamard(reg->width-1, reg);

  for(i=0;i<reg->width;i++)
    quantum_sigma_x(i, reg);//NOT every Qubit


}

void final_measure(quantum_reg *reg){
  quantum_hadamard(reg->width, reg);

  reg->width++;
  //quantum_print_qureg(reg);

  quantum_bmeasure(reg->width-1, reg);
}
