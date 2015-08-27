
#include "physImage.h"

physImage::physImage() {
	// questo non fa nulla
	minimum_value = 0;
	maximum_value = 0;
	init_variables();
}

physImage::~physImage() {
	int i;
	//for (i=0; i<height; i++) 
	//	delete img_buffer[i];
	delete img_buffer;
	delete cont_img_buffer;
	delete cont_8bit_img_buffer;
	
}

physImage::physImage(physImage *other)
{
	int i;
	init_variables();
	minimum_value = 0;
	maximum_value = 0;

	std::cerr<<"[physImage] Constructor physImage* called"<<std::endl;

	width = other->width;
	height = other->height;


	img_buffer = new int* [height];

	for (i=0; i<height; i++) {
		assert ( img_buffer[i] = new int[width] );
		memcpy(img_buffer[i], other->imgRow(i), width*sizeof(int));
	}

	bpp = other->bpp;

}

physImage::physImage(physImage &other)
{
	int i;
	init_variables();
	minimum_value = 0;
	maximum_value = 0;

	std::cerr<<"[physImage] Constructor physImage& called"<<std::endl;
	
	width = other.width;
	height = other.height;


	img_buffer = new int* [height];


	for (i=0; i<height; i++) {
		assert ( img_buffer[i] = new int[width] );
		memcpy(img_buffer[i], other.imgRow(i), width*sizeof(int));
	}

	bpp = other.bpp;

}

physImage::physImage(int new_w, int new_h) {
	// create zero image
	init_variables();
	minimum_value = 0;
	maximum_value = 0;

	width = new_w;
	height = new_h;

	matrix_points_aligned();
}

physImage::physImage(int **oth_buffer, int oth_w, int oth_h) {
	int i;
	init_variables();
	minimum_value = 0;
	maximum_value = 0;

	img_buffer = new int* [oth_h];

	for (i=0; i<oth_h; i++) {
		assert ( img_buffer[i] = new int[oth_w] );
		memcpy(img_buffer[i], oth_buffer[i], oth_w*sizeof(int));
	}

	width = oth_w;
	height = oth_h;
	// FIXME: bpp indefinito
	bpp=0;
}

physImage::physImage(int *cont_buffer, int cont_w, int cont_h)
{
	// new version: aligned matrix representation
	init_variables();
	minimum_value = 0;
	maximum_value = 0;
	bpp=0;

	width = cont_w;
	height = cont_h;
	matrix_points_aligned();
	
	//img_buffer = new int* [cont_h];

	for (int i = 0; i < cont_h; i++) {
		//assert ( img_buffer[i] = new int[cont_w] );
		memcpy(img_buffer[i], (cont_buffer + i*cont_w), cont_w*sizeof(int));
	}

	
	
	// FIXME: bpp indefinito
	bpp = 4;
}

bool
physImage::isValid(void)
{
	if (img_buffer != NULL && width > 0 && height > 0) return true;
	else return false;
}

/*physImage::physImage(const char *filename) {
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
	width = swapED(width);
	height = swapED(height);
#endif


	// load data
	ifile->seekg(header_size,ios::beg);
	assert (img_buffer = new int* [height]);
	assert (readb = new char [width*bpp]);
	for (i=0; i<height; i++) {
		
		memset(readb,0,width*bpp);
		rowptr = readb;
		assert (img_buffer[i] = new int [width]);
		ifile->read(readb,width*bpp);

		for (j=0; j<width; j++) {
#if __BYTE_ORDER == __BIG_ENDIAN
			(img_buffer[i])[j] = (int) (unsigned short)swapED( *((short *)&readb[bpp*j]) ); // probabilmente esistono modi piu' intelligenti
#else
			(img_buffer[i])[j] = (int)( *((unsigned short *)&readb[bpp*j]) ); 
#endif
			//cerr<<(int) __swapED(*(short *)&readb[bpp*j])<<endl;
		}
	}
	
	ifile->close();
	delete ptr;
}*/

void
physImage::init_variables(void)
{
	img_buffer = NULL;
	cont_img_buffer = NULL;
	cont_8bit_img_buffer = NULL;

	derived_pI = NULL;

	width = -1;
	height = -1;
}

const int *
physImage::imgRow(int rownum)
{
	if (rownum<height) return img_buffer[rownum];
	else return NULL;
}

void *
physImage::aligned_buffer(void)	// to be used for QImage contruction
{

	int *new_img_buffer;
	int *ptr;
	int i,j;

	if (cont_img_buffer == NULL) 
		new_img_buffer = new int[width*height];
	else
		new_img_buffer = cont_img_buffer;

	ptr = new_img_buffer;

	for (i=0; i<height; i++) {
		//memcpy (ptr, (char *)(img_buffer[i]), width*sizeof(int));
		memcpy (ptr, (int *)(img_buffer[i]), width*sizeof(int));
		ptr+=width;
	}

	for (i=0; i<width*height; i++) {
		register int val = new_img_buffer[i];
		val = (int)round(((double)val/maximum_value)*255);
		//new_img_buffer[i] = (val&0xff)*0x00010101;
		new_img_buffer[i] = (val&0xff)*0x00010010;
	}

	// altra prova di colore (minkia, idiotissima e minimamente ottimizzata)
	//for (i=0; i<width*height; i++) {
	//	register int val = new_img_buffer[i];
	//	val = (int)round(((double)val/maximum_value)*765);
	//	if (val>255 && val<510) new_img_buffer[i] = 0x100*(val-255)+0xff;
	//	else if (val>509) new_img_buffer[i]=0x10000*(val-510)+0xffff;
	//}

	return (void *)new_img_buffer;
}

void
physImage::switch_to_aligned(void)
{
	// takes a static copy of the aligned buffer, for compatibility
	// with new version (PCO reads in aligned)
	
	cont_img_buffer = (int *)aligned_buffer();
	cont_8bit_img_buffer = new unsigned char[width*height];
}

void
physImage::matrix_points_aligned(void)
{
	// set ** to point on *[]
	int i;

	std::cerr<<"[physImage::matrix_align] calling with "<<width<<"x"<<height<<std::endl;
	
	if (img_buffer != NULL) delete img_buffer;

	if (cont_img_buffer == NULL && width>0 && height>0) {
		assert( cont_img_buffer = new int[width*height] );
		std::cerr<<"[\t\t|--> ] 32bit contiguous allocated"<<std::endl;
	}

	if (cont_8bit_img_buffer == NULL && width>0 && height>0) {
		assert( cont_8bit_img_buffer = new unsigned char[width*height] );
		std::cerr<<"[\t\t|--> ] 8bit contiguous allocated"<<std::endl;
	} else {
		std::cerr<<"nonno', non ci entro, width: "<<width<<" e height: "<<height<<std::endl;
	}

	if (cont_img_buffer != NULL && width>0 && height>0) {
		img_buffer = new int*[height];
		for (i=0; i<height; i++) {
			img_buffer[i] = cont_img_buffer+i*width;
		}
		std::cerr<<"[\t\t|--> ] matrix translation allocated"<<std::endl;
	}
}


void
physImage::sync_to_8bit(void)
{
	sync_to_8bit(minimum_value, maximum_value);
}

void
physImage::sync_to_8bit(int lower_val, int upper_val)
{
	int i, tval;
	//std::cerr<<"cippa"<<std::endl;

	for (i=0; i<width*height; i++) {
		//cont_8bit_img_buffer[i] = (unsigned char)(cont_img_buffer[i]>>4);
		// might be useful fC8b visualization
		//cont_8bit_img_buffer[i] = (unsigned char) floor(((double)(cont_img_buffer[i]-minimum_value))*(255./(double (maximum_value-minimum_value))));
		tval = (int) floor(((double)(cont_img_buffer[i]-lower_val))*(255./(double (upper_val-lower_val))));
		cont_8bit_img_buffer[i] = (unsigned char) tval;
		if (tval > 255)
			cont_8bit_img_buffer[i] = 255;	// osceno
		if (tval < 0)
			cont_8bit_img_buffer[i] = 0;	// osceno
	}
}

void
physImage::scanBrightness() {
	int i,j;

	minimum_value = (img_buffer[0])[0];
	maximum_value = (img_buffer[0])[0];
	//cerr<<"[physImage] test val is: "<<minimum_value<<endl;

	for (i=0; i<height; i++) for (j=0; j<width; j++) {
		if ((img_buffer[i])[j] > maximum_value) {
			maximum_value = (img_buffer[i])[j];
			max_v_x = j;
			max_v_y = i;
		} else if ((img_buffer[i])[j] < minimum_value) {
			minimum_value = (img_buffer[i])[j];
			min_v_x = j;
			min_v_y = i;
		}
	}

	//cerr<<"[brightness scan] "<<minimum_value<<" -- "<<maximum_value<<endl;
	//randomInit();
}

void
physImage::fullContrast8bit()
{
	// scan min-max and renormalize for 8bit pgm 
	int i,j;
	scanBrightness();

	for (i=0; i<height; i++) for (j=0; j<width; j++) {
		(img_buffer[i])[j] = (((img_buffer[i])[j])-minimum_value)*255/(maximum_value-minimum_value);
	}

	maximum_value = 255;
	minimum_value = 0;
}

void
physImage::fullContrast16bit()
{
	// scan min-max and renormalize for 16bit pgm 
	int i,j;
	//scanBrightness();

	for (i=0; i<height; i++) for (j=0; j<width; j++) {
		(img_buffer[i])[j] = (((img_buffer[i])[j])-minimum_value)*65535/(maximum_value-minimum_value);
	}

	maximum_value = 65535;
	minimum_value = 0;
}

unsigned char *
physImage::fullContrast8bit_buffer()
{
	// metodo idiota, non ho voglia di sbattermi
	int i,j;
	scanBrightness();
	unsigned char *new_buffer;
	new_buffer = new unsigned char[width*height];

	for (i=0; i<height; i++) for (j=0; j<width; j++) {
		new_buffer[j+(width*i)] = (((img_buffer[i])[j])-minimum_value)*255/(maximum_value-minimum_value);
	}

	return new_buffer;
}

void
physImage::write(const char *filename, enum write_format my_wf)
{
	int i,j,coln;
	ofstream ofile(filename);
	unsigned char *padder;
	int pixvalue;

	struct rgbpixel {
		unsigned char r;
		unsigned char g;
		unsigned char b;
	} rgbpix;
	
	if (my_wf == bmp) {
		// dio che pacco di struttura!
		
		// il bmp padda a 32bit
		padder = new unsigned char [4];

		struct bmpfile_magic {
		      unsigned char magic[2];
		} ofile_magic;

		ofile_magic.magic[0] = 'B';
		ofile_magic.magic[1] = 'M';
 
		struct bmpfile_header {
			uint32_t filesz;
			uint16_t creator1;
			uint16_t creator2;
			uint32_t bmp_offset;
		} ofile_header;
		memset((char*)&ofile_header,0,sizeof(struct bmpfile_header));

		// first writing
		ofile.write((char *) &ofile_magic, 2);
		ofile.write((char *) &ofile_header, sizeof(bmpfile_header));


		struct bmp_dib_header {
			uint32_t header_sz;
			uint32_t width;
			uint32_t height;
			uint16_t nplanes;
			uint16_t bitspp;
			uint32_t compress_type;
			uint32_t bmp_bytesz;
			uint32_t hres;
			uint32_t vres;
			uint32_t ncolors;
			uint32_t nimpcolors;
		} ofile_dib_header;
		memset((char*)&ofile_dib_header,0,sizeof(struct bmp_dib_header));
		ofile_dib_header.header_sz = 40;
		ofile_dib_header.width = width;
		ofile_dib_header.height = height;
		ofile_dib_header.nplanes = 1;
		ofile_dib_header.bitspp = 24;
		ofile_dib_header.compress_type = 0; // RGB
		ofile.write((char *) &ofile_dib_header, sizeof(bmp_dib_header));

		
		ofile_header.bmp_offset = ofile.tellp();
		for (i=height-1; i>-1; i--) {
			for (j=0; j<width; j++) {
				pixvalue = (unsigned char)((img_buffer[i])[j]);
				rgbpix.r = pixvalue;
				rgbpix.g = pixvalue;
				rgbpix.b = pixvalue;
				ofile.write( (char *) &rgbpix, sizeof(struct rgbpixel ));
			}
			// pad
			ofile.write((char *)padder, width%4);

		}

		// second write of the header
		ofile_header.filesz = ofile.tellp();
		ofile.seekp(2,ios::beg);
		ofile.write((char *) &ofile_header, sizeof(bmpfile_header));


	} else if (my_wf == pgm5 || my_wf == raw) {	// raw based formats

		cerr<<"Unimplemented"<<endl;

	}
}


void
physImage::writeRAW(const char *filename) {
	int i,j;
	ofstream ofile(filename);

	cerr<<"[writeRAW] output to raw file"<<endl;

	scanBrightness();

	if (maximum_value < (((unsigned short)(~0))>>1) ) {
		short pixvalue;
		cerr<<"[writeRAW] output to 16bit"<<endl;

		for (i=0; i<height; i++) for (j=0; j<width; j++) {
			pixvalue = (short)((img_buffer[i])[j]);
#if __BYTE_ORDER == __BIG_ENDIAN
			// PGM raw format is always big endian
			ofile.write( (char *) &pixvalue, 2);
#else
			ofile.write( ((char *) &pixvalue)+1, 1);
			ofile.write( (char *) &pixvalue, 1);
#endif
		}
	} else {
		int pixvalue;
		std::cout<<"[physImage::writeRAW] Warning: output is 32bit"<<std::endl;
		for (i=0; i<height; i++) for (j=0; j<width; j++) {
			pixvalue = ((img_buffer[i])[j]);
#if __BYTE_ORDER == __BIG_ENDIAN
			// PGM raw format is always big endian
			ofile.write( (char *) &pixvalue, 4);
#else
			ofile.write( ((char *) &pixvalue)+3, 1);
			ofile.write( ((char *) &pixvalue)+2, 1);
			ofile.write( ((char *) &pixvalue)+1, 1);
			ofile.write( (char *) &pixvalue, 1);
#endif
		}

	}


	ofile.close();

}

void
physImage::writePGM(const char *filename) {
	this->writePGM2(filename);
}

void
physImage::writePGM2(const char *filename) {
	int i,j,coln;
	ofstream ofile(filename);

	cerr<<"[writePGM2] output to pgm2 file"<<endl;
	//cerr<<maximum_value;
	ofile<<"P2\n"<<width<<" "<<height<<" "<<(maximum_value > 0 ? maximum_value : 65535)<<"\n";

	coln = 0;
	for (i=0; i<height; i++) for (j=0; j<width; j++) {
		ofile<<" "<<(img_buffer[i])[j]<<" ";
		coln++;
		if (coln == 70) {
			ofile<<"\n";
			coln = 0;
		}
	}

	ofile.close();
}


void
physImage::writeASC(const char *filename) {
	int i,j, rown = 1;
	ofstream ofile(filename);

	cerr<<"[writeASC] output to asc file"<<endl;
	//cerr<<maximum_value;

	 for (i=0; i<height; i++){
		//ofile<<"  "<<rown<<"  ";
		for (j=0; j<width; j++) {
			ofile<<(img_buffer[i])[j]<<"\t";
		}
		ofile<<"\n";
		//rown++;
	}

	ofile<<flush;
	ofile.close();

}

void
physImage::writePGM5(const char *filename) {
	int i,j;
	short pixvalue;
	ofstream ofile(filename);
	scanBrightness();

	cerr<<"[writePGM5] output to pgm5 file"<<endl;


#if __BYTE_ORDER == __BIG_ENDIAN
	std::cerr<<"[pgm::write] Assuming big endian"<<std::endl;
#endif

	//cerr<<maximum_value;
	ofile<<"P5\n"<<width<<" "<<height<<" "<<(maximum_value > 0 ? maximum_value : 65535)<<"\n";

	if (maximum_value > 0x100-1) {	// P5 pix representation is 16bit

		for (i=0; i<height; i++) for (j=0; j<width; j++) {
			pixvalue = (short)((img_buffer[i])[j]);
#if __BYTE_ORDER == __BIG_ENDIAN
			// PGM raw format is always big endian
			ofile.write( (char *) &pixvalue, 2);
#else
			ofile.write( ((char *) &pixvalue)+1, 1);
			ofile.write( (char *) &pixvalue, 1);
#endif
		}

	} else { // P5 pix repr. is 8 bit
		for (i=0; i<height; i++) for (j=0; j<width; j++) {
			pixvalue = (unsigned char)((img_buffer[i])[j]);
			ofile.write( (char *) &pixvalue, 1);
		}
	}

	ofile.close();

}

float
physImage::getNormalizedIntegral() {
	int i,j;
	float integral;
	int integral_norm;
	
	// idea: normalizzo rispetto al numero di pixel e all'intensita' massima misurabile
	integral_norm = width*height*4096; // FIXME: questo valore e' da leggere nell'intestazione
	integral = 0;
	
	for (i=0; i<height; i++) for (j=0; j<width; j++) integral+=(img_buffer[i])[j];

	return (integral/( (float)integral_norm));
}

float
physImage::integrateImage(float precision, float level, int zero_level)
{
	// conto da ricontrollare; errore di fattore .5/.25 su bordi/angoli, ma probabilmente
	// trascurabile
	// (NB: precision unused)
	float integral = 0, check_value = (maximum_value-zero_level)*level+zero_level;
	if (isValid()) {
		for (int i=0; i<height; i++) {
			for (int j=0; j<width; j++) {
				if (img_buffer[i][j] > check_value)
					integral+=(img_buffer[i][j]-zero_level);
			}
		}
		return (integral);
	} else {
		cerr<<"[physImage::integrateImage] Invalid image"<<endl;
		return 0;
	}
}

float
physImage::integrateImage_MC(float precision, float level, int zero_level)
{
	// Montecarlo image integration within precision
	// level is ratio of maximum to be taken in account (lower values are set to zero)
	int i, total_points, in_points, npoints;
	int rand_row, rand_col;
	float rand_val;

	npoints = (int)ceil(1/precision);

	//cerr<<"Current minimum_value is: "<<minimum_value<<endl;
	//cerr<<"new zero level? ";
	//cin>>zero_level;
	
	cerr<<"[physImage::integrateImage] Starting montecarlo integration with "<<npoints<<" punti"<<endl;

	total_points = npoints;
	in_points = 0;
	for (i=0; i<npoints; i++) {
		// sono un pirlaaaaaaaaa!!!!
		rand_row = (int)round(rand_number()*(height-1));
		rand_col = (int)round(rand_number()*(width-1));
		rand_val = (rand_number()*(maximum_value-zero_level)+zero_level);

		// se c'e' un errore, sta qui...
		//if ( (img_buffer[rand_row])[rand_col] > rand_val && (img_buffer[rand_row])[rand_col] > (level*(maximum_value-zero_level))+zero_level) {
		if ( (img_buffer[rand_row])[rand_col] > rand_val && (img_buffer[rand_row])[rand_col] > (level*(maximum_value-zero_level))+zero_level) {
			in_points++;
		}

	}

	cerr<<in_points<<"/"<<total_points<<endl;

	return(width*height*(float)(maximum_value-zero_level)*((float)in_points)/((float)total_points));
}

float
physImage::integrateImage(float precision)
{
	return(integrateImage(precision,0));
}

float
physImage::integrateImage(float precision, float level)
{
	return(integrateImage(precision, level, minimum_value));
}

void
physImage::getStatus() {
	cerr<<"Loaded img is "<<width<<"x"<<height<<"x"<<bpp<<endl;
}

/* -------------------------------------------------------------------------------------------------*/

physImage 
physImage::operator-(physImage other) {

	int i,j;
	physImage new_img;
	new_img.minimum_value = 0;
	new_img.maximum_value = 0;
	
	assert ( width == other.width);
	assert ( height == other.height);

	new_img.img_buffer = new int * [height];
	
	
	for (i=0; i<height; i++) {
		new_img.img_buffer[i] = new int[width];
		for (j=0; j<width; j++) {
			(new_img.img_buffer[i])[j] = img_buffer[i][j]-other.img_buffer[i][j];
			if ((new_img.img_buffer[i])[j] < new_img.minimum_value) new_img.minimum_value = (new_img.img_buffer[i])[j];
			else if ((new_img.img_buffer[i])[j] > new_img.maximum_value) new_img.maximum_value = (new_img.img_buffer[i])[j];
		}
	}

	new_img.width = width;
	new_img.height = height;
	new_img.bpp = bpp;

	// pad brightness
	cerr<<"[pad brightness to zero]"<<endl;

	if (new_img.minimum_value < 0) {
		for (i=0; i<height; i++) for (j=0; j<width; j++) (new_img.img_buffer[i])[j]-=new_img.minimum_value;
		new_img.maximum_value -= new_img.minimum_value;
		new_img.minimum_value = 0;
	}

	
//	new_img.ifile = ifile;
	return(new_img);
}

physImage
physImage::operator* (physImage other) {

	int i,j;
	physImage new_img;
	new_img.minimum_value = 0;
	new_img.maximum_value = 0;
	
	assert ( width == other.width);
	assert ( height == other.height);

	new_img.img_buffer = new int * [height];
	
	
	for (i=0; i<height; i++) {
		new_img.img_buffer[i] = new int[width];
		for (j=0; j<width; j++) {
			(new_img.img_buffer[i])[j] = img_buffer[i][j]*other.img_buffer[i][j];
			if ((new_img.img_buffer[i])[j] < new_img.minimum_value) new_img.minimum_value = (new_img.img_buffer[i])[j];
			else if ((new_img.img_buffer[i])[j] > new_img.maximum_value) new_img.maximum_value = (new_img.img_buffer[i])[j];
		}
	}

	new_img.width = width;
	new_img.height = height;
	new_img.bpp = bpp;

	return(new_img);

}

physImage
physImage::operator= (physImage other) {

	width = other.width;
	height = other.height;
	bpp = other.bpp;

	maximum_value = other.maximum_value;
	minimum_value = other.minimum_value;

	img_buffer = other.img_buffer;

	return *this;
}

/* -------------------------------------------------------------------------------------------------*/


/*#if __BYTE_ORDER == __BIG_ENDIAN

inline int swapED (int inum) {
	int retval;*/

/*
	asm (	"andi. r5,%1,0xff\n\
		slwi r5,r5,0x18\n\
		mr %0,r5\n\
		\n\
		andi. r5,%1,0xff00\n\
		slwi r5,r5,0x8\n\
		add %0,%0,r5\n\
		\n\
		li r7,0xff\n\
		slwi r7,r7,0x10\n\
		and r5,%1,r7\n\
		srwi r5,r5,0x8\n\
		add %0,%0,r5\n\
		\n\
		slwi r7,r7,0x8\n\
		and r5,%1,r7\n\
		srwi r5,r5,0x18\n\
		add %0,%0,r5"
			: "=r" (retval)
			: "b" (inum)
			: "r5");
			*/
// different gas behaviour in osx/linux ppc
/*#ifdef __linux
	asm ( "mr %%r10,%1\n\
        rlwimi %%r10,%1,16,16,7\n\
        rlwinm %0,%%r10,24,8,31\n\
        rlwinm %%r10,%1,24,0,7\n\
        add %0,%0,%%r10"
        : "=r" (retval)
        : "b" (inum)
        : "r10");
#else
asm ( "mr r10,%1\n\
        rlwimi r10,%1,16,16,7\n\
        rlwinm %0,r10,24,8,31\n\
        rlwinm r10,%1,24,0,7\n\
        add %0,%0,r10"
        : "=r" (retval)
        : "b" (inum)
        : "r10");
#endif

	return retval;
}


inline short swapED (short inum) {
	short retval;

#ifdef __linux
	asm (	"andi. %%r5,%1,0xff\n\
		slwi %%r5,%%r5,0x8\n\
		mr %0,%%r5\n\
		\n\
		andi. %%r5,%1,0xff00\n\
		srwi %%r5,%%r5,0x8\n\
		add %0,%0,%%r5"
			: "=r" (retval)
			: "b" (inum)
			: "r5");
#else
	asm (	"andi. r5,%1,0xff\n\
		slwi r5,r5,0x8\n\
		mr %0,r5\n\
		\n\
		andi. r5,%1,0xff00\n\
		srwi r5,r5,0x8\n\
		add %0,%0,r5"
			: "=r" (retval)
			: "b" (inum)
			: "r5");
#endif

	return (retval);
}

#else

inline int swapED (int inum) { return inum; }
inline short swapED (short inum) { return inum; }

#endif*/

void
physImage::divide_by_image(physImage *oth) {
	divide_by_image(oth, 1000, false);
}

void
physImage::divide_by_image(physImage *oth, float renorm, bool derive)
{
	
	if ((width != oth->width) || (height != oth->height)) {
		throw pI_sizeerror;
		return;
	}


	if (derive) {
		// generate subimage
		derived_pI = new physImage(width, height);
		for (int i=0; i<width*height; i++)
			derived_pI->cont_img_buffer[i] = (oth->cont_img_buffer[i] == 0) ? 0 : round(renorm*float(cont_img_buffer[i])/float(oth->cont_img_buffer[i]));
			
	} else {
		// act on main image
		for (int i=0; i<width*height; i++)
			cont_img_buffer[i] = (oth->cont_img_buffer[i] == 0) ? 0 : round(renorm*float(cont_img_buffer[i])/float(oth->cont_img_buffer[i]));
	}

	scanBrightness();

}

void
physImage::addimage(physImage *other)
{
	if (other->isValid()) {
		int i,j;
		assert ( width == other->width);
		assert ( height == other->height);

		for (i=0; i<height; i++) {
			for (j=0; j<width; j++) {
				(img_buffer[i])[j] = img_buffer[i][j]+other->img_buffer[i][j];
			}
		}
	}
}

void
physImage::background_subtract(physImage *background)
{
	int i,j;
	
	assert ( width == background->width);
	assert ( height == background->height);

	for (i=0; i<height; i++) {
		for (j=0; j<width; j++) {
			(img_buffer[i])[j] = img_buffer[i][j]-background->img_buffer[i][j];
		}
	}


	// pad brightness
	cerr<<"[pad brightness to zero]"<<endl;

	scanBrightness();


	if (minimum_value < 0) {
		cerr<<"[pad] Warning, there were negative values"<<endl;
		cerr<<"[pad] "<<minimum_value<<endl;
		//for (i=0; i<height; i++) for (j=0; j<width; j++) (img_buffer[i])[j]-=minimum_value;
		//maximum_value -= minimum_value;
		//minimum_value = 0;
	}
}

imagePointList  
physImage::contour_points(int zero_level, double threshold)
{
	// trova il countour del passaggio di livello in un modo oggettivamente stupido
	scanBrightness();

	int level = (int)round(zero_level + threshold*(double)(maximum_value-zero_level));
	int pcounter, *points, *ptr;
	const int *row;
	int i,j;
	bool old_status, new_status;

	imagePointList p_vec(2*height);
	imagePointList_itr itr = p_vec.begin();

	points = new int[2*width];
	ptr = points;

	__dmsg("p1")
	cerr<<"[physImage::countour] check level: "<<level<<endl;
	__dmsg("p2")

	for (i=0; i<height; i++)  {
		row = imgRow(i);
		old_status = (row[0] < level);
		for (j=1; j<height; j++) {
			new_status = (row[j] < level);
			if (new_status != old_status) {
				old_status = new_status;
				p_vec[itr-p_vec.begin()].x = j; 
				p_vec[itr-p_vec.begin()].y = i; 
				itr++;
			}
		}

		if ((p_vec.end()-itr) < width) {
			pcounter = itr-p_vec.begin();
			p_vec.resize(p_vec.size()+width);
			itr = p_vec.begin(); itr+=pcounter;
			cerr<<"vector resize"<<endl;
		}


		
	}

	// restituisci solo il necessario
	p_vec.resize(itr-p_vec.begin());

	// sarebbe interessante fargli fare un fit... (tipo ellittico?)
	// GRANDE IDEA DI TOMMY: parto dal centro e calcolo le distanze da tutti i punti del contour:
	// avuto il profilo calcolo il fit parametrico di un ellisse

	return p_vec;

}


// derived images
physImage *
physImage::decimated_image(int decimation)
{
	int i,j,k,l;
	if (width%decimation != 0 || height%decimation !=0) {
		cerr<<"[decimation] Warning, decimation will discard points!"<<endl;
	}

	physImage *newb16;

	int new_img_width = (int)floor((double)width/decimation);
	int new_img_height = (int)floor((double)height/decimation);

	cerr<<"[physImage::decimation] new_img_width: "<<new_img_width<<", new_img_height: "<<new_img_height<<endl;

	int **new_img, *pixel_buffer, pixel_sum;
	new_img = new int*[new_img_height];
	for (i=0; i<new_img_height; i++) new_img[i] = new int[new_img_width];

	// metodo orribile, da rifare con buffer allineato
	for (i=0; i<new_img_height; i++) 
		for (j=0; j<new_img_width; j++) {
			pixel_sum = 0;
			for (k=decimation*i; k<(decimation*(i+1)); k++)
				for (l=decimation*j; l<(decimation*(j+1)); l++) {
					pixel_sum+=img_buffer[k][l];
				}
			new_img[i][j] = (int)round((double)pixel_sum/(decimation*decimation));

	}

	//cerr<<"fine decimazione"<<endl;
	
	newb16 = new physImage(new_img, new_img_width, new_img_height);
	newb16->scanBrightness();
	return newb16;
}

physImage *
physImage::subImage(int ul_x, int ul_y, int lr_x, int lr_y)
{
	int **subImage_buffer;
	int i, nrows, ncols;
	physImage *newImage;

	nrows = abs(lr_y-ul_y)+1;
	ncols = abs(lr_x-ul_x)+1;

	subImage_buffer = new int *[nrows];
	for (i=0; i<(nrows); i++) {
		subImage_buffer[i] = new int [ncols];
		memcpy(subImage_buffer[i], img_buffer[ul_y+i]+ul_x,ncols*sizeof(int));
	}

	newImage = new physImage(subImage_buffer, ncols, nrows);	// baco schifoso nel costruttore
	newImage->scanBrightness();

	return newImage;
}

physImage *
physImage::subImage(int par1, int par2, int par3, int par4, SUBIMAGE_MODE s_mode)
{
	if (s_mode == center_size) {
		// parameters: center_x, center_y, width, height
		int hs_x, hs_y;
		hs_x = (par3-par3%2)/2;
		hs_y = (par4-par4%2)/2;
		return subImage(par1-hs_x, par2-hs_y, par1+hs_x, par2+hs_y);
	} else if (s_mode == ulcorner_size) {
		// parameters: ul_x, ul_y, width, height
		return subImage(par1, par2, par1+par3-1, par2+par4-1);
	} else if (s_mode == ul_lr_corner) {
		// parameters: ul_x, ul_y, lr_x, lr_y
		return subImage(par1, par2, par3, par4);
	} else 
		return NULL;
}

/************************** UTILs ************************/

void randomInit(void)
{
	FILE *sys_rand_dev;
	int sys_seed;
	sys_rand_dev=fopen("/dev/random","rb");
	if (fread(&sys_seed,sizeof(int),1,sys_rand_dev)) cerr<<"Random number generator seed changed!"<<endl;
	srandom(sys_seed);
}

inline float rand_number(void) {
	return rand()/_RAND_MAX;
}








