#include "tiffimg.h"


tiffimg::tiffimg(const char *filename) {
	int grays,i,j;
	int **readbuf;

	minimum_value = 0;
	maximum_value = 0;
	init_variables();

	TIFF* tif = TIFFOpen(filename, "r");
	
	if (tif) {
		tdata_t buf;
		tstrip_t strip;
		int size,i;
		int temp;
		int idx=0;
		int sizetot;

		uint32 readnum;

		width = TIFFScanlineSize(tif)>>1;
		buf = _TIFFmalloc(width*2);

		int temp_num;
		TIFFGetField(tif, TIFFTAG_IMAGELENGTH, &readnum);
		height = (int)readnum;
		
		
		std::cerr<<"[tiffimg] image is "<<width<<" "<<height<<std::endl;

		img_buffer = new int* [height];
		
			
		for (int rownum = 0; rownum < height; rownum++) {
			TIFFReadScanline(tif, buf, rownum); // sara' in uint16??
			img_buffer[rownum] = new int[width];
			//sizetot+=size;
			for (i=0; i<width; i++) {
				img_buffer[rownum][i] = ((unsigned short *)buf)[i];
			}
		}
		_TIFFfree(buf);
		TIFFClose(tif);
	}




	assert( cont_8bit_img_buffer = new unsigned char[width*height] );

	//std::cerr<<"[tiffimg] width: "<<width<<", height: "<<height<<", grays: "<<grays<<std::endl;
}


// <clement>
//void tifread(const char *filename,int image[]) {
//  TIFF* tif = TIFFOpen(filename, "r");
//  if (tif) {
//    tdata_t buf;
//    tstrip_t strip;
//    int size,i;
//    int temp;
//    int idx=0;
//    int sizetot;
//    buf = _TIFFmalloc(TIFFStripSize(tif));
//    for (strip = 0; strip < TIFFNumberOfStrips(tif); strip++){
//      size=TIFFReadEncodedStrip(tif, strip, buf, (tsize_t) -1);
//      sizetot+=size;
//      for (i=0;i<size/2;i++){
//    temp=(((unsigned short *)buf)[i]/16);
//    image[idx]=temp;
//    idx++;
//      }
//    }
//    _TIFFfree(buf);
//    TIFFClose(tif);
//  }
//}
// </clement>
