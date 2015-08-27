/* derivation of physImage, holding two physImage to compose a complex image
 *
 * (C) 2010 Alessandro Flacco
 */

#include <iostream>
#include <fstream>
#include <vector>

#include <fftw3.h>

#include "physImage.h"

#ifndef __complexImage_h
#define __complexImage_h

class complexImage
{
public:
	complexImage()
	: cI(2) { }

	complexImage(physImage &);

	~complexImage();	

private:
	vector<physImage *> cI;
	physImage *origin_pi;

	double *origin_d
	fftw_complex *F_origin_fc;

};

#endif

