
#include <iostream>
#include "sifimg.h"

int main(int argc, char** argv) {

	if ( argc < 2) {
		cout<<"converts to RAW file"<<endl;
		cout<<"use "<<argv[0]<<" <ifile> <ofile>"<<endl;
		exit(0);
	}

	sifimg iimage(argv[1]);
	//iimage.fullContrast8bit();
	iimage.writeRAW(argv[2]);
}
