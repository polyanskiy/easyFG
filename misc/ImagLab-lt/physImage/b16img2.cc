#include "b16img2.h"

b16img2::b16img2(const char *filename) {
	minimum_value = 0;
	maximum_value = 0;
	init_variables();
	char *ptr = new char[3], tempch;
	int i,j, temp;
	char *readb;
	char *rowptr;
	char revision;

	int header_size; // cambia con la revision del file

	
	ifile = new ifstream(filename);
	assert(*ifile);

	ifile->read(ptr,3);

	//if ( string(ptr) != string("PCO") ) {
	if ( strncmp(ptr,"PCO",3) != 0 ) {
		cerr<<"not a PCO file ["<<ptr<<"]"<<endl;
		img_buffer = NULL;
		return;
	}

	// alla camWare succhiano i cazzi
	ifile->seekg(0x05,ios::beg);
	ifile->read(&revision,1);
	if (revision=='a') header_size=384;
	else if (revision=='b') header_size=512;


	// bpp (idiozia del formato: e' un carattere a 0x09)
	// altra idiozia: non capisco la specificazione di bpp in revision a: fisso a 2
	if (revision=='b') {
		ifile->seekg(0x09,ios::beg);
		ifile->read(&tempch,1);
		bpp = (int)tempch;
	} else if (revision=='a') bpp=2;

	// width
	ifile->seekg(0x0c,ios::beg);
	ifile->read((char *)&width,4);

	
	// height
	ifile->seekg(0x10,ios::beg);
	ifile->read((char *)&height,4);


#if __BYTE_ORDER == __BIG_ENDIAN
	//bpp = __swapED(bpp);
	std::cout<<"big endian!"<<std::endl;
	width = swapED(width);
	height = swapED(height);
#endif

	std::cout<<"[b16] read width: "<<width<<std::endl;
	std::cout<<"[b16] read height: "<<height<<std::endl;

	// load data (matrix align version)
	matrix_points_aligned();
	
	ifile->seekg(header_size,ios::beg);
	//assert (img_buffer = new int* [height]);
	assert (readb = new char [width*bpp]);
	for (i=0; i<height; i++) {
		
		memset(readb,0,width*bpp);
		rowptr = readb;
	//	assert (img_buffer[i] = new int [width]);
		ifile->read(readb,width*bpp);

		for (j=0; j<width; j++) {
#if __BYTE_ORDER == __BIG_ENDIAN
			(img_buffer[i])[j] = (int) (unsigned short)swapED( *((short *)&readb[bpp*j]) ); // probabilmente esistono modi piu' intelligenti
#else
			(img_buffer[i])[j] = (int)( *((unsigned short *)&readb[bpp*j]) ); 
#endif
			//cout<<(int) __swapED(*(short *)&readb[bpp*j])<<endl;
		}
	}

	//assert( cont_8bit_img_buffer = new unsigned char[width*height] );
	
	ifile->close();
	delete ptr;
}



