#include <iostream>
#include <fstream>

#include "physImage.h"
#include "sifimg.h"

using namespace std;

int main(int argc, char **argv)
{
	if (argc == 1) {
		cout<<"Use "<<argv[0]<<" sif1 sif2 ... sifn"<<endl;
		return 0;
	}
	sifimg baseimage(argv[1]);
	sifimg *temp_image;
	for (int i=2; i<argc; i++) {
		temp_image = new sifimg(argv[i]);
		baseimage.addimage((physImage *)temp_image);
	}
	baseimage.writeRAW("image_addition.raw");
	return 0;
}
