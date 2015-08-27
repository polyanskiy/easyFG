// this is a float extension to physImage class
// standard image buffer is constructed (and possibly kept up to date) 
// by rounding a superstanding float (or double) matrix
//
// well, in reality it would be better to write it as a completely templized class
//
// let's do it...

// NB. only contiguous memory methods (by lines) are being replicated

#include <iostream>
#include <fstream>

#include "physImage.h"

using namespace std;

#ifndef __physImageF_h
#define __physImageF_h

template<class T>
class physImageF : public physImage {
public:
	physImageF();
	physImageF(int, int, T);	// empty image
	physImageF(T *, int, int);
	~physImageF();

	void matrix_points_aligned();

	void sync_round();
	void TscanBrightness(void);
	void reset_matrix_translation(T, T, T, T);

	void writeRAW(const char *);

	T *Timg_buffer;
	T Tmaximum_value;
	T Tminimum_value;

};

template<class T>
physImageF<T>::physImageF()
	: physImage()
{ }

template<class T>
physImageF<T>::physImageF(int w, int h, T val)
{
	width = w;
	height = h;
	matrix_points_aligned();
	for (int i=0; i<width*height; i++)
		Timg_buffer[i] = val;
	sync_round();
}

template<class T>
physImageF<T>::~physImageF()
{
	if (Timg_buffer != NULL)
		delete Timg_buffer;
}

template<class T>
physImageF<T>::physImageF(T *o_buffer, int o_width, int o_height) {
	width = o_width;
	height = o_height;
	matrix_points_aligned();

	// not calling correspondent physImage constructor for matrix_points_aligned
	memcpy(Timg_buffer, o_buffer, width*height*sizeof(T));
	
	// rounding
	sync_round();
}

template<class T> void
physImageF<T>::sync_round() {
	for (int i=0; i<width*height; i++)
		cont_img_buffer[i] = round(Timg_buffer[i]);
}

template<class T> void
physImageF<T>::matrix_points_aligned()
{
	int i;

	std::cerr<<"[physImageF::matrix_align] calling with "<<width<<"x"<<height<<std::endl;
	
	if (img_buffer != NULL) delete img_buffer;

	if (cont_img_buffer == NULL && width>0 && height>0) {
		assert( cont_img_buffer = new int[width*height] );
		std::cerr<<"[\t\t|--> ] 32bit contiguous allocated"<<std::endl;
		assert( Timg_buffer = new T[width*height] );
		std::cerr<<"[\t\t|--> ] template 32bit contiguous allocated"<<std::endl;
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

template<class T> void
physImageF<T>::reset_matrix_translation(T min_cut, T max_cut, T multiplier, T transl) {

	TscanBrightness();
	cout<<"[physImageF::matrix_translation] Tmin: "<<Tminimum_value<<endl;
	cout<<"[physImageF::matrix_translation] Tmax: "<<Tmaximum_value<<endl;
	cout<<"[physImageF::matrix_translation] min: "<<minimum_value<<endl;
	cout<<"[physImageF::matrix_translation] max: "<<maximum_value<<endl;

	for (int i=0; i<width*height; i++) {
		if (Timg_buffer[i] > max_cut) {
			cont_img_buffer[i] = round(transl+multiplier*max_cut);
		} else if (Timg_buffer[i] < min_cut) {
			cont_img_buffer[i] = round(transl+multiplier*min_cut);
		} else {
			cont_img_buffer[i] = round(transl+multiplier*Timg_buffer[i]);
		}
	}
}

template<class T> void
physImageF<T>::TscanBrightness() {
	int i,j;

	Tminimum_value = (Timg_buffer[0]);
	Tmaximum_value = (Timg_buffer[0]);
	//cerr<<"[physImage] test val is: "<<minimum_value<<endl;

	for (i=0; i<width*height; i++) {
		if ((Timg_buffer[i]) > Tmaximum_value) {
			Tmaximum_value = (Timg_buffer[i]);
		} else if ((Timg_buffer[i]) < Tminimum_value) {
			Tminimum_value = (Timg_buffer[i]);
		}
	}

	//cerr<<"[brightness scan] "<<minimum_value<<" -- "<<maximum_value<<endl;
	//randomInit();
}

template<class T> void
physImageF<T>::writeRAW(const char *ofilename) {
	ofstream ofile(ofilename);

	// alla bruttissimo dio
	ofile.write((char *)Timg_buffer, height*width*sizeof(T));
	ofile.close();
}

#endif
