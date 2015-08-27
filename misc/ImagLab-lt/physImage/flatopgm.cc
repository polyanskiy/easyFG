
#include <iostream>
#include "fla7000img.h"

int main(int argc, char** argv) {

	if ( argc < 2) {
		cout<<"converts to ASC file"<<endl;
		cout<<"use "<<argv[0]<<" <ifile> <ofile>"<<endl;
		exit(0);
	}

	fla7000img iimage(argv[1]);
	//iimage.fullContrast8bit();
	iimage.writePGM5(argv[2]); // evitare PGM2, le immagini da IP sono gigantesche
}
