
#include <iostream>
#include "b16img2.h"

int main(int argc, char** argv) {

	if ( argc < 2) {
		cout<<"converts to ASC file"<<endl;
		cout<<"use "<<argv[0]<<" <ifile> <ofile>"<<endl;
		exit(0);
	}

	b16img2 iimage(argv[1]);
	iimage.writeASC(argv[2]);
}
