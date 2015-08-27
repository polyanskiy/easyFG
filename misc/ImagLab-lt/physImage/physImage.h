/*
 * Generic class for image manipulation
 * (C) Alessandro Flacco 2007-10
 */

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <exception>

#include <cmath>

#include <assert.h>

#include <string.h>

#include <stdlib.h>


#define _RAND_MAX ((pow((float)2,31))-1)

#define abs(x) (int)abs((double)x)

using namespace std;

inline int swapED (int);
inline float swapED (float);
inline short swapED (short);

inline float rand_number();	// random number normalized to 1

void randomInit(void);

// e mo' mi son rotto il cazzo
#define __BYTE_ORDER 1
#define __BIG_ENDIAN 0

#ifndef __physImage_h__
#define __physImage_h__


#ifndef __dmsg
#define __dmsg(X) std::cerr<<"check: "<<X<<std::endl;
#endif

struct imagePoint {
	imagePoint() :x(0), y(0) {};
	imagePoint(int a, int b) : x(a), y(b) {}
	int x;
	int y;
};

enum image_ptr_constructor_mode {copy_buffer_non_cont, copy_buffer_cont, point_buffer_non_cont, point_buffer_cont};
enum image_ptr_buffer_type {contiguous, non_contiguous};
enum write_format {bmp, pgm2, pgm5, raw, asc};
enum subImage_mode {center_size, ulcorner_size, ul_lr_corner};


typedef enum image_ptr_constructor_mode CONSTR_MODE;
typedef enum image_ptr_buffer_type BUF_MODE;
typedef enum subImage_mode SUBIMAGE_MODE;

typedef vector<struct imagePoint> imagePointList;
typedef vector<struct imagePoint>::iterator imagePointList_itr;
typedef vector<imagePointList *> imagePointList_collector;


class physImage {
	
public:
	physImage();
//	physImage(const char *);

	physImage(physImage *);
	physImage(physImage &);
	physImage(int, int);		// create zero image
	physImage(int **, int, int);	// buffer, width, height
	physImage(int *, int, int);	// contiguous buffer, width, height
	~physImage();

	void init_variables(void);

	// status
	bool isValid(void);

	void *aligned_buffer(void);
	void switch_to_aligned(void);
	virtual void matrix_points_aligned(void);

	void getStatus();

	int **img_buffer; // note sulla struttura: gli int* sono righe!

 
	int *cont_img_buffer;
	unsigned char *cont_8bit_img_buffer;

	physImage *derived_pI;

	const char *filename;

	const int *imgRow(int);

	int bpp;
	int height;
	int width;

	void scanBrightness();

	int minimum_value, maximum_value;
	int min_v_x, min_v_y, max_v_x, max_v_y;

	physImage operator-(physImage other);
	physImage operator=(physImage other);
	physImage operator*(physImage other);	// image multiplication
	

	float getNormalizedIntegral();
	float integrateImage(float);			// precision
	float integrateImage(float, float);		// ..., threshold
	float integrateImage(float, float, int);	// ..., zero_level
	float integrateImage_MC(float, float, int);	// Montecarlo integration

	void fullContrast8bit();
	void fullContrast16bit();
	unsigned char *fullContrast8bit_buffer();
	
	void sync_to_8bit(void);	// sync in fc8b
	void sync_to_8bit(int, int);	// sync to 8b from min to max

	void writeASC (const char *);	// formato paccuso matlab (no intestazione, matrice ascii)
	void writePGM (const char *);
	void writePGM2 (const char *);
	void writePGM5 (const char *);
	virtual void writeRAW (const char *);

	void write (const char *, enum write_format); // gli altri saranno alias 


	// math functions
	imagePointList contour_points(int, double);
	void background_subtract(physImage *);
	void addimage(physImage *);		// impariamo le referenze?
	void divide_by_image(physImage *);	// compat
	void divide_by_image(physImage *, float, bool);

	// derived images
	physImage *decimated_image(int);
	physImage *subImage(int, int, int, int);
	physImage *subImage(int, int, int, int, SUBIMAGE_MODE);

	// fichissimo
	physImage *get_last() {	// returns the last image in the hierarchy
		if (derived_pI == NULL)
			return this;
		else return derived_pI->get_last();
	}


	// Fourier Analysis and filtering
	
		

	exception pI_filefail, pI_sizeerror;
	
};



#endif

/* -------------------------------------------------------------------------------------------------*/

#ifndef __pI_definitions
#define __pI_definitions

#if __BYTE_ORDER == __BIG_ENDIAN || __FORCE_ENDIANESS_SWITCH == 1

#ifndef __WINDOG

inline int swapED (int inum) {
	int retval;

// different gas behaviour in osx/linux ppc
#ifdef __linux
	asm ( "mr %%r10,%1\n\
        rlwimi %%r10,%1,16,16,7\n\
        rlwinm %0,%%r10,24,8,31\n\
        rlwinm %%r10,%1,24,0,7\n\
        add %0,%0,%%r10"
        : "=r" (retval)
        : "b" (inum)
        : "r10");
#else

// derivation for MacBook
	retval = ( ((inum&0xff)<<24) + ((inum&0xff00)<<8) + ((inum&0xff0000)>>8) + ((inum&0xff000000)>>24) );

//asm ( "mr r10,%1\n\
        rlwimi r10,%1,16,16,7\n\
        rlwinm %0,r10,24,8,31\n\
        rlwinm r10,%1,24,0,7\n\
        add %0,%0,r10"
//        : "=r" (retval)
//        : "b" (inum)
//        : "r10");
#endif

	return retval;
}


inline short swapED (short inum) {
	short retval;
	//std::cout<<"lo sto chiamando questo cazzo di metodo?"<<std::endl;

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
	// mmm, questo ad occhio e croce e' pure sbagliato
	//retval = (inum>8)+(inum<8);
	retval = ((inum>>8)+(inum<<8));
#endif


	return (retval);
}


inline float swapED(float inum)
{
	int p_num = swapED(*((int *)(&inum)));
	return (*((float *)&p_num));
}

#else

inline short swapED(short inum) 
{ return ((inum>>8)+(inum<<8)); }

inline int swapED(int inum) 
{ return ( ((inum&0xff)<<24) + ((inum&0xff00)<<8) + ((inum&0xff0000)>>8) + ((inum&0xff000000)>>24) ); }

inline float swapED(float inum)
{
	int p_num = swapED(*((int *)(&inum)));
	return (*((float *)&p_num));
}

#endif

#else

inline int swapED (int inum) { return inum; }
inline float swapED (float inum) { return inum; }
inline short swapED (short inum) { 
//	std::cout<<"o sto chiamando questo??"<<std::endl; 
	return inum; 
}

#endif


#endif
