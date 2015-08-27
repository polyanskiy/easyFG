#include "fla7000img.h"

fla7000img::fla7000img(const char *filename) {
	minimum_value = 0;
	maximum_value = 0;
	init_variables();

	int i,j, temp;
	const char *inf_filename;
	char *ptr = new char[5], tempch;
	std::string temp_string;
	unsigned short tempnum;

	char *readb;
	char *rowptr;
	char revision;

#if __BYTE_ORDER == __BIG_ENDIAN
	std::cerr<<"[fla7000img] calling big endian"<<std::endl;
#else
	std::cerr<<"[fla7000img] calling little endian"<<std::endl;
#endif

	ifstream *inf_ifile;

	// get .inf filename
	std::string filename_str(filename);
	inf_filename = (filename_str.substr(0,filename_str.length()-3)+string("inf")).c_str();
	std::cout<<"[fla7000img] looking for .inf file: "<<inf_filename<<std::endl;
	
	inf_ifile = new ifstream(inf_filename);
	assert(*inf_ifile);
	
	// get variables from .inf file
	// 6: bpp, 7: width, 8: height

	for (i=0; i<5; i++)
		std::getline(*inf_ifile, temp_string);

	*inf_ifile>>bpp;
	bpp = (int)round((float)bpp/8);

	*inf_ifile>>width;
	*inf_ifile>>height;


	// read main file
	ifile = new ifstream(filename);
	assert(*ifile);

	//ifile->read(ptr,3);

	//if ( string(ptr) != string("PCO") ) {
	//if ( strncmp(ptr,"PCO",3) != 0 ) {
	//	cerr<<"not a PCO file ["<<ptr<<"]"<<endl;
	//	img_buffer = NULL;
	//	return;
	//}

	std::cout<<"[fla7000] read bpp: "<<bpp<<std::endl;
	std::cout<<"[fla7000] read width: "<<width<<std::endl;
	std::cout<<"[fla7000] read height: "<<height<<std::endl;



	// load data
	ifile->seekg(0,ios::beg);
	assert (img_buffer = new int* [height]);
	assert (readb = new char [width*bpp]);
	for (i=0; i<height; i++) {
		
		memset(readb,0,width*bpp);
		rowptr = readb;
		assert (img_buffer[i] = new int [width]);
		ifile->read(readb,width*bpp);

		for (j=0; j<width; j++) {
#if __BYTE_ORDER == __BIG_ENDIAN
//			(img_buffer[i])[j] = (int) (unsigned short)swapED( *((short *)&readb[bpp*j]) ); // probabilmente esistono modi piu' intelligenti
			(img_buffer[i])[j] = (int)( *((unsigned short *)&readb[bpp*j]) ); 
#else
			tempnum = *((unsigned short *)&readb[bpp*j]); 
			tempnum = ((tempnum&0xff)<<8)+((tempnum&0xff00)>>8);
			(img_buffer[i])[j] = (int)tempnum; 

			//(img_buffer[i])[j] = (int) (unsigned short)swapED( *((short *)&readb[bpp*j]) ); // probabilmente esistono modi piu' intelligenti
#endif
			//cout<<(int) __swapED(*(short *)&readb[bpp*j])<<endl;
		}
	}
	
	scanBrightness();
	assert( cont_8bit_img_buffer = new unsigned char[width*height] );
	
	ifile->close();
	delete ptr;
}



