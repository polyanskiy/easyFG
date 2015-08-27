#include "pgmimg.h"


pgmimg::pgmimg(const char *filename) {
	int grays,i,j;
	int **readbuf;

	minimum_value = 0;
	maximum_value = 0;
	init_variables();

	FILE *ifd;
	ifd = fopen(filename,"rb");
	readbuf = (int **)pgm_readpgm(ifd, &width, &height, (gray *)&grays);

	if (grays<256) bpp = 1;
	else bpp = 2;

	std::cerr<<"[pgm] read width: "<<width<<std::endl;
	std::cerr<<"[pgm] read height: "<<height<<std::endl;
	std::cerr<<"[pgm] read grays: "<<grays<<std::endl;

	// allocate buffers and set translation (MPA)
	matrix_points_aligned();

	// MPA: assert (img_buffer = new int* [height]);
	for (i=0; i<height; i++) {
		// MPA: assert (img_buffer[i] = new int [width]);
		for (j=0; j<width; j++) {
			(img_buffer[i])[j] = (int)((readbuf[i])[j]);
		}
	}
	
	
	// MPA: assert( cont_8bit_img_buffer = new unsigned char[width*height] );

	//std::cerr<<"[pgmimg] width: "<<width<<", height: "<<height<<", grays: "<<grays<<std::endl;
}

/*sifimg::sifimg(const char *filename) {

	char *ptr = new char[5], tempch;
	int i,j, temp;
	char *readb;
	char *rowptr;
	char revision;

	string temp_string;
	
	ifile = new ifstream(filename);
	assert(*ifile);

	ifile->read(ptr,5);

	//if ( string(ptr) != string("PCO") ) {
	if ( strncmp(ptr,"Andor",5) != 0 ) {
		cerr<<"not an Andor .sif file ["<<ptr<<"]"<<endl;
		img_buffer = NULL;
		return;
	}

	// alla camWare succhiano i cazzi
	//ifile->seekg(0x05,ios::beg);
	//ifile->read(&revision,1);
	//if (revision=='a') header_size=384;
	//else if (revision=='b') header_size=512;

	bpp = 4;
	std::cout<<"[sif] fixed bpp: "<<bpp<<std::endl;

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

	width = 1024;
	std::cout<<"[sif] fixed width: "<<width<<std::endl;
	
	// height
	//ifile->seekg(0x10,ios::beg);
	//ifile->read((char *)&height,4);

	height = 1024;
	std::cout<<"[sif] fixed height: "<<height<<std::endl;

//#if __BYTE_ORDER == __BIG_ENDIAN
//	//bpp = __swapED(bpp);
//	width = swapED(width);
//	height = swapED(height);
//#endif


	// Andor .sif file has 22 lines of header
	for (i=0; i<22; i++) 
		std::getline(*ifile, temp_string);
	std::cout<<"[sif] raw init @ "<<ifile->tellg()<<std::endl;

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
			temp = ((temp&0xff)<<24) + ((temp&0xff00)<<8) + ((temp&0xff0000)>>8) + ((temp&0xff000000)>>24);
			(img_buffer[i])[j] = (int) (*((float *)&temp));
#else
			temp = (int) ( *((float *)&readb[bpp*j]) ); 
			(img_buffer[i])[j] = temp;
#endif
		}
	}

	assert( cont_8bit_img_buffer = new unsigned char[width*height] );
	
	ifile->close();
	delete ptr;
}
*/
