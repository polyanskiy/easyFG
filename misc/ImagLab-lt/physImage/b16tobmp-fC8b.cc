
#include <iostream>
#include "b16img2.h"

int main(int argc, char** argv) {

	if ( argc < 2) {
		cout<<"converts to full contrast 8 bit BMP (fuckin' programs not supporting 16bit pgms..)"<<endl;
		cout<<"use "<<argv[0]<<" <ifile> <ofile>"<<endl;
		exit(0);
	}

	b16img2 iimage(argv[1]);
	iimage.fullContrast8bit();
	iimage.write(argv[2],bmp);
}
