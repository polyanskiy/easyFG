
#include <iostream>
#include "pgmimg.h"

int main(int argc, char** argv) {

	if ( argc < 2) {
		cout<<"converts to ASC file"<<endl;
		cout<<"use "<<argv[0]<<" <ifile> <ofile>"<<endl;
		exit(0);
	}

	pgmimg iimage(argv[1]);
	//iimage.fullContrast8bit();
	iimage.writeASC(argv[2]);
}
