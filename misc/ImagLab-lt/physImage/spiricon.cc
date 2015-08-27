#include "spiricon.h"

spiricon::spiricon(const char *filename) {

	minimum_value = 0;
	maximum_value = 0;
	init_variables();
	char *ptr = new char[5], tempch;
	int i,j, temp;
	char *readb;
	char *rowptr;
	char revision;

	string temp_string;
	
	ifile = new ifstream(filename);
	assert(*ifile);

	//ifile->read(ptr,5);


	// eh, ci fosse un modo di riconoscerlo...
	//
	//if ( string(ptr) != string("PCO") ) {
	//if ( strncmp(ptr,"Andor",5) != 0 ) {
	//	cerr<<"not an Andor .sif file ["<<ptr<<"]"<<endl;
	//	img_buffer = NULL;
	//	return;
	//}

	// alla camWare succhiano i cazzi
	//ifile->seekg(0x05,ios::beg);
	//ifile->read(&revision,1);
	//if (revision=='a') header_size=384;
	//else if (revision=='b') header_size=512;

	bpp = 2;
	std::cerr<<"[spiricon] fixed bpp: "<<bpp<<std::endl;

	// bpp (idiozia del formato: e' un carattere a 0x09)
	// altra idiozia: non capisco la specificazione di bpp in revision a: fisso a 2
	//if (revision=='b') {
	//	ifile->seekg(0x09,ios::beg);
	//	ifile->read(&tempch,1);
	//	bpp = (int)tempch;
	//} else if (revision=='a') bpp=2;

	// width
	//ifile->seekg(0x0c,ios::beg);
	//ifile->read((char *)&width,4);

	width = 1600;
	std::cerr<<"[spiricon] fixed width: "<<width<<std::endl;
	
	// height
	//ifile->seekg(0x10,ios::beg);
	//ifile->read((char *)&height,4);

	height = 1200;
	std::cerr<<"[spiricon] fixed height: "<<height<<std::endl;

//#if __BYTE_ORDER == __BIG_ENDIAN
//	//bpp = __swapED(bpp);
//	width = swapED(width);
//	height = swapED(height);
//#endif


	// spiricon has 0x4000 bytes of header
	ifile->seekg(0x4000, ios::beg);
	
	// get data
	assert (img_buffer = new int* [height]);
	assert (readb = new char [width*bpp]);
	for (i=0; i<height; i++) {
		
		memset(readb,0,width*bpp);
		rowptr = readb;
		assert (img_buffer[i] = new int [width]);
		ifile->read(readb,width*bpp);

		for (j=0; j<width; j++) {
#if __BYTE_ORDER == __BIG_ENDIAN
			temp = ( *((int *)&readb[bpp*j]) ); 
			temp = ((temp&0xff)<<8) + ((temp&0xff00)>>8);
			(img_buffer[i])[j] = temp;
#else
			(img_buffer[i])[j] = temp;
#endif
		}
	}

	scanBrightness();

	assert( cont_8bit_img_buffer = new unsigned char[width*height] );
	
	ifile->close();

	scanBrightness();

	delete ptr;
}

