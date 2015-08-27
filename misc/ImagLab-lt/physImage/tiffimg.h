/*
 * derivation of physImage for tiff
 */

#include <iostream>
#include <fstream>
#include <string>

#include "physImage.h"

#include <tiff.h>
#include <tiffio.h>

#include <stdio.h>

#ifndef __tiffimg_h
#define __tiffimg_h

using namespace std;

class tiffimg : public physImage {

public:
	tiffimg(const char *);

	ifstream *ifile;

};

#endif
