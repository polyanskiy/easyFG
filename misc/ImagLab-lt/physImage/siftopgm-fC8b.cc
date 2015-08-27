
#include <iostream>
#include "sifimg.h"

int main(int argc, char** argv) {

	if ( argc < 2) {
		cout<<"converts to full contrast 8 bit pgm (fuckin' programs not supporting 16bit pgms..)"<<endl;
		cout<<"use "<<argv[0]<<" <ifile> <ofile>"<<endl;
		exit(0);
	}

	sifimg iimage(argv[1]);
	iimage.fullContrast8bit();
	iimage.writePGM5(argv[2]);
}
