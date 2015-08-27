#include "IMimg.h"

IMimg::IMimg(const char *filename) {
	minimum_value = 0;
	maximum_value = 0;
	init_variables();

	std::cout<<"[Magick++] Reading "<<filename<<std::endl;
	Magick::Image my_IMimg;
	my_IMimg.read(filename);
	my_IMimg.verbose(true);
	my_IMimg.modifyImage();
	//my_IMimg.type(Magick::GrayscaleType);

	bpp = my_IMimg.depth();
	width = my_IMimg.size().width();
	height = my_IMimg.size().height();


	std::cout<<"[Magick++] read "<<width<<"x"<<height<<"x"<<bpp<<std::endl;

	Magick::PixelPacket *pixel_cache = my_IMimg.getPixels(0,0,width-1,height-1);

	img_buffer = new int *[height];
	for (int i=0; i<height; i++)
		img_buffer[i] = new int[width];

	int row_index=0;
	for (int i=0; i<width*height; i++) {
		img_buffer[row_index][i%width] = (int)pixel_cache[i].red;
		std::cout<<"pixel: "<<pixel_cache[i].red<<std::endl;
		std::cout<<"pixel: "<<pixel_cache[i].green<<std::endl;
		std::cout<<"pixel: "<<pixel_cache[i].blue<<std::endl;
		if (i%width == (width-1)) {
			row_index++;
		}
	}
	

	//assert( cont_8bit_img_buffer = new unsigned char[width*height] );
	
}



