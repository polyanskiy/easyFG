/*
 * derivation of physImage for b16 support
 */

#include <iostream>
#include <fstream>

#include "physImage.h"

#ifndef __FITSimg_h
#define __FITSimg_h

using namespace std;

class FITSimg : public physImage {

public:
	FITSimg(const char *);

	ifstream *ifile;

};

#endif
