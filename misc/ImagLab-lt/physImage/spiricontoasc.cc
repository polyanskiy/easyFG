
#include <iostream>
#include "spiricon.h"

int main(int argc, char** argv) {

	if ( argc < 2) {
		cout<<"converts to ASCII file"<<endl;
		cout<<"use "<<argv[0]<<" <ifile> <ofile>"<<endl;
		exit(0);
	}

	spiricon iimage(argv[1]);
	//iimage.fullContrast16bit();
	iimage.writeASC(argv[2]);
}
