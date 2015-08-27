
#include <iostream>
#include "bmpimg.h"

int main(int argc, char** argv) {

	if ( argc < 2) {
		cout<<"converts to PGM5 file"<<endl;
		cout<<"use "<<argv[0]<<" <ifile> <ofile>"<<endl;
		exit(0);
	}

	bmpimg iimage(argv[1]);
	iimage.fullContrast16bit();
	iimage.writePGM5(argv[2]);
}
