#include "sifimg.h"

sifimg::sifimg(const char *filename) {

	minimum_value = 0;
	maximum_value = 0;
	init_variables();
	char *ptr = new char[5], tempch;
	int i,j, temp;
	char *readb;
	char *rowptr;
	char revision;

	string temp_string;

	cout<<"Open sif: "<<filename<<endl;
	
	ifile = new ifstream(filename);
	//assert(*ifile);

	try { ifile->read(ptr,5); } catch (int e) { throw pI_filefail; }

	//if ( string(ptr) != string("PCO") ) {
	if ( strncmp(ptr,"Andor",5) != 0 ) {
		cerr<<"not an Andor .sif file ["<<ptr<<"]"<<endl;
		throw pI_filefail;
		img_buffer = NULL;
		return;
	}

	bpp = 4;
	std::cerr<<"[sif] fixed bpp: "<<bpp<<std::endl;


//#if __BYTE_ORDER == __BIG_ENDIAN
//	//bpp = __swapED(bpp);
//	width = swapED(width);
//	height = swapED(height);
//#endif

	// matrix informations on line 5
	for (i=0; i<5; i++) 
		std::getline(*ifile, temp_string);
	stringstream ss(temp_string);
	ss>>width;
	ss>>height;

	//width = 1024;
	std::cerr<<"[sif] width: "<<width<<std::endl;
	//height = 1024;
	std::cerr<<"[sif] height: "<<height<<std::endl;

	// At least two versions of .sif have been observed, with 22 or 25 lines before the raw part
	// Last line is usually a single 0 on a terminated line
	ifile->seekg(0, ios::beg);
	for (i=0; i<22; i++) 
		std::getline(*ifile, temp_string);
	std::cerr<<"[sif] raw init @ "<<ifile->tellg()<<std::endl;

	if (strcmp(temp_string.c_str(), "0") != 0) {
		cerr<<"[sifimg] Old Andor format, workaround! (oh, it sucks so much...)"<<endl;
		while (strcmp(temp_string.c_str(), "0") != 0)
			std::getline(*ifile, temp_string);
	}

	// get data
	matrix_points_aligned();
	//matrix_version assert (img_buffer = new int* [height]);
	
	assert (readb = new char [width*bpp]);
	for (i=0; i<height; i++) {
		
		memset(readb,0,width*bpp);
		rowptr = readb;
		//matrix_version assert (img_buffer[i] = new int [width]);
		ifile->read(readb,width*bpp);

		for (j=0; j<width; j++) {
#if __BIG_ENDIAN__ == 1
			temp = ( *((int *)&readb[bpp*j]) ); 
			temp = ((temp&0xff)<<24) + ((temp&0xff00)<<8) + ((temp&0xff0000)>>8) + ((temp&0xff000000)>>24);
			(img_buffer[i])[j] = (int) (*((float *)&temp));
#else
			temp = (int) ( *((float *)&readb[bpp*j]) ); 
			(img_buffer[i])[j] = temp;
#endif
		}
	}

	scanBrightness();

	//matrix_version assert( cont_8bit_img_buffer = new unsigned char[width*height] );
	ifile->close();

	scanBrightness();

	delete ptr;
}

