#include "FITSimg.h"

FITSimg::FITSimg(const char *filename) {
	minimum_value = 0;
	maximum_value = 0;
	init_variables();
	char *ptr = new char[3], tempch;
	int i,j, temp;
	char *readb;
	char *rowptr;
	char revision;

	unsigned short num;

	int header_size; // cambia con la revision del file

	
	ifile = new ifstream(filename);
	assert(*ifile);

	ifile->read(ptr,3);

	//if ( string(ptr) != string("PCO") ) {
/*	if ( strncmp(ptr,"PCO",3) != 0 ) {
		cerr<<"not a PCO file ["<<ptr<<"]"<<endl;
		img_buffer = NULL;
		return;
	}*/


	// bpp
	bpp=2;

	// width
	width = 1024;
	
	// height
	height = 1024;




	// load data
	ifile->seekg(0xb40,ios::beg);
	assert (img_buffer = new int* [height]);
	assert (readb = new char [width*bpp]);
	for (i=0; i<height; i++) {
		
		memset(readb,0,width*bpp);
		rowptr = readb;
		assert (img_buffer[i] = new int [width]);
		ifile->read(readb,width*bpp);

		for (j=0; j<width; j++) {
			num = ( *((unsigned short *)&readb[bpp*j]) ); 
			(img_buffer[i])[j] = (num&0xff)<<8+(num&0xff00)>>8;
			//cout<<(int) __swapED(*(short *)&readb[bpp*j])<<endl;
		}
	}

	assert( cont_8bit_img_buffer = new unsigned char[width*height] );
	
	ifile->close();
	delete ptr;
}

