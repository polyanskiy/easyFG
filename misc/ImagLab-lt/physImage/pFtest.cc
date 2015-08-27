
#include <iostream>
#include <string>
#include <fstream>

#include "physImage.h"
#include "physImageF.h"

int main()
{
	float matr[9];
	for (int i=0; i<9; i++)
		matr[i] = 0.1*i;

	physImageF<float> my_f(matr, 3, 3);
	my_f.writePGM("cippa.pgm");
}
