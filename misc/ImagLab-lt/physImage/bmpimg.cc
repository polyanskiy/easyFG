#include "bmpimg.h"

bmpimg::bmpimg(const char *filename) {

	minimum_value = 0;
	maximum_value = 0;
	init_variables();
	char *ptr = new char[5], tempch;
	short temp_sh;
	int i,j, temp;
	char *readb;
	char *rowptr;
	char revision;

	string temp_string;
	
	ifile = new ifstream(filename);
	assert(*ifile);

	ifile->read(ptr,2);

	if ( strncmp(ptr,"BM",2) != 0 ) {
		cerr<<"not a bmp file ["<<ptr<<"]"<<endl;
		img_buffer = NULL;
		return;
	}




	// width
	ifile->seekg(0x12,ios::beg);
	ifile->read((char *)&width,4);

	
	// height
	ifile->seekg(0x16,ios::beg);
	ifile->read((char *)&height,4);

	// bpp
	ifile->seekg(0x1a,ios::beg);
	ifile->read((char *)&temp_sh,2);

	//header
	ifile->seekg(0x436,ios::beg);
	


#if __BYTE_ORDER == __BIG_ENDIAN
	bpp = swapED(temp_sh);
	width = swapED(width);
	height = swapED(height);
#else
	bpp = temp_sh;
#endif

	std::cout<<"[bmpimg] width: "<<width<<", height: "<<height<<", bpp: "<<bpp<<std::endl;

	// get data
	// NB. bmp is 32-bit aligned by row (chi e' il pirla?)
	int row_width = ((width*bpp)%4 != 0) ? (width*bpp + 4 - ((width*bpp)%4)) : (width*bpp);
	std::cerr<<"[bmpimg] width: "<<width<<" (padded:"<<row_width<<"), bpp: "<<bpp<<", rowsize: "<<row_width<<std::endl;
	assert (img_buffer = new int* [height]);
	assert (readb = new char [row_width]);
	for (i=0; i<height; i++) {
		
		memset(readb,0,row_width);
		rowptr = readb;
		assert (img_buffer[i] = new int [width]);
		ifile->read(readb,row_width);

		for (j=0; j<width; j++) {
#if __BYTE_ORDER == __BIG_ENDIAN
			// occorrerebbe mettere un puntatore a funzione di scelta per lo swap di endianness; ora fisso a 8bit
			//(img_buffer[i])[j] = (int) (unsigned short)swapED( *((short *)&readb[bpp*j]) ); // probabilmente esistono modi piu' intelligenti
			(img_buffer[i])[j] = (int)( *((unsigned short *)&readb[bpp*j]) ); 
#else
			(img_buffer[i])[j] = (int)( *((unsigned short *)&readb[bpp*j]) ); 
#endif

		}
	}

	assert( cont_8bit_img_buffer = new unsigned char[width*height] );
	
	ifile->close();
	delete ptr;
}

